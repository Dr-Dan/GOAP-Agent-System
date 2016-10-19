//
//  goap.cpp
//  GPGOAP_cpp
//

// from Abraham T. Stolk's excellent GOAP repo: https://github.com/stolk/GPGOAP
// Under the Apache 2.0 license: http://www.apache.org/licenses/LICENSE-2.0

#include "goap.hpp"
#include "astar.hpp"

#include <string.h>
#include <stdio.h>

// search for atom, will create one if it doesn't exist
static int idx_for_atomname( actionplanner_t* ap, const char* atomname )
{
	int idx;
	for ( idx=0; idx < ap->numatoms; ++idx )
		if ( !strcmp( ap->atm_names[ idx ], atomname ) ) return idx;
	
	// if an id was not found and there are not too many add to the list
	if ( idx < MAXATOMS )
	{
		ap->atm_names[ idx ] = atomname;
		ap->numatoms++;
		return idx;
	}
	
	return -1;
}


static int idx_for_actionname( actionplanner_t* ap, const char* actionname )
{
	int idx;
	for ( idx=0; idx < ap->numactions; ++idx )
		if ( !strcmp( ap->act_names[ idx ], actionname ) ) return idx;
	
	if ( idx < MAXACTIONS )
	{
		ap->act_names[ idx ] = actionname;
		ap->act_costs[ idx ] = 1; // default cost is 1
		ap->numactions++;
		return idx;
	}
	
	return -1;
}


void goap::goap_actionplanner_clear( actionplanner_t* ap )
{
	ap->numatoms = 0;
	ap->numactions = 0;
	for ( int i=0; i<MAXATOMS; ++i )
	{
		ap->atm_names[ i ] = 0;
	}
	for ( int i=0; i<MAXACTIONS; ++i )
	{
		ap->act_names[ i ] = 0;
		ap->act_costs[ i ] = 0;
		goap_worldstate_clear( ap->act_pre+i );
		goap_worldstate_clear( ap->act_pst+i );
	}
}


void goap::goap_worldstate_clear( worldstate_t* ws )
{
	ws->values = 0LL;
	ws->dontcare = -1LL; // set dontcare to 1111 1111
}


bool goap::goap_worldstate_set( actionplanner_t* ap, worldstate_t* ws, const char* atomname, bool value )
{
	// get the state atom id, will create an atom if none is found
	const int idx = idx_for_atomname( ap, atomname );
	if ( idx == -1 ) return false; // if state cannot be found or created: return
	
	// if setting state atom/bit to true:
	// ( ws->values | ( 1LL << idx ) ) -> just combines states, keeps 1s, changes any 0s if necessary
	// e.g. world state value: 0111, change bit:1000 ---> 0111 | 1000 = 1111

	// else if setting to false:
   // ( ws->values & ~( 1LL << idx ) -> changes any bits that need it to false
   // e.g. world state value: 0111, change bit:~0010 = 1101 ---> 0111 & 1101 = 0101
	
//	printf("%s:(%lld | (1LL << %d)) = %lld\n",atomname, ws->values, idx, ( ws->values | ( 1LL << idx )));
	ws->values = value ? ( ws->values | ( 1LL << idx ) ) : ( ws->values & ~( 1LL << idx ) );
	
	// store any bits that are already not important and not set in the current atom
	// e.g. dontcare->1111, idx=0->~0001=1110 ::: 1111 & 1110 = (1111)1110 = -2
	ws->dontcare &= ~( 1LL << idx );
	return true;
}


bool goap::goap_set_pre( actionplanner_t* ap, const char* actionname, const char* atomname, bool value )
{
	const int actidx = idx_for_actionname( ap, actionname );
	const int atmidx = idx_for_atomname( ap, atomname );
	if ( actidx == -1 || atmidx == -1 ) return false;
	goap_worldstate_set( ap, ap->act_pre+actidx, atomname, value );
	return true;
}


bool goap::goap_set_pst( actionplanner_t* ap, const char* actionname, const char* atomname, bool value )
{
	const int actidx = idx_for_actionname( ap, actionname );
	const int atmidx = idx_for_atomname( ap, atomname );
	if ( actidx == -1 || atmidx == -1 ) return false;
	goap_worldstate_set( ap, ap->act_pst+actidx, atomname, value );
	return true;
}


bool goap::goap_set_cost( actionplanner_t* ap, const char* actionname, int cost )
{
	const int actidx = idx_for_actionname( ap, actionname );
	if ( actidx == -1 ) return false;
	ap->act_costs[ actidx ] = cost;
	return true;
}


void goap::goap_worldstate_description( const actionplanner_t* ap, const worldstate_t* ws, char* buf, int sz )
{
	int added=0;
	for ( int i=0; i<MAXATOMS; ++i )
	{
		if ( ( ws->dontcare & ( 1LL << i ) ) == 0LL )
		{
			const char* val = ap->atm_names[ i ];
			char upval[ 128 ];
			size_t j;
			for ( j=0; j<strlen( val ); ++j )
				upval[ j ] = ( val[ j ] - 32 );
			upval[ j++ ] = 0;
			const bool set = ( ( ws->values & ( 1LL << i ) ) != 0LL );
			added = snprintf( buf, sz, "%s,", set?upval:val );
			buf += added; sz -= added;
		}
	}
}


void goap::goap_description( actionplanner_t* ap, char* buf, int sz )
{
	int added=0;
	for ( int a=0; a<ap->numactions; ++a )
	{
		added=snprintf( buf, sz, "%s:\n", ap->act_names[ a ] );
		sz -= added; buf += added;
		
		worldstate_t pre = ap->act_pre[ a ];
		worldstate_t pst = ap->act_pst[ a ];
		for ( int i=0; i<MAXATOMS; ++i )
			if ( ( pre.dontcare & ( 1LL << i ) ) == 0LL )
			{
				bool v = ( pre.values & ( 1LL << i ) ) != 0LL;
				added = snprintf( buf, sz, "  %s==%d\n", ap->atm_names[ i ], v );
				sz -= added; buf+= added;
			}
		for ( int i=0; i<MAXATOMS; ++i )
			if ( ( pst.dontcare & ( 1LL << i ) ) == 0LL )
			{
				bool v = ( pst.values & ( 1LL << i ) ) != 0LL;
				added = snprintf( buf, sz, "  %s:=%d\n", ap->atm_names[ i ], v );
				sz -= added; buf+= added;
			}
	}
}


worldstate_t goap::goap_do_action( actionplanner_t* ap, int actionnr, worldstate_t fr )
{
	// get state effects for action with index actionnr
	const worldstate_t pst = ap->act_pst[ actionnr ];
	const bfield_t unaffected = pst.dontcare;
	// flip dontcare bits to get those that matter
	const bfield_t affected   = ( unaffected ^ -1LL );
	
	// ( fr.values & unaffected ):
	// any state values that are also action effects that don't matter
	// ( pst.values & affected ):
	// any action effects that do matter
	// keep any atoms from either or both
	// (0011 & 1011) -> 0011, (0100 & 0100)-> 0100
	// 0011 | 0100 = 0111
	// basically just change any bits that are affected by the action
	fr.values = ( fr.values & unaffected ) | ( pst.values & affected );
	// keep any atoms that are irrelevant to both
	fr.dontcare &= pst.dontcare;
	return fr;
}


int goap::goap_get_possible_state_transitions( actionplanner_t* ap, worldstate_t fr, worldstate_t* to, const char** actionnames, int* actioncosts, int cnt )
{
	int writer=0;
	for ( int i=0; i<ap->numactions && writer<cnt; ++i )
	{
		// see if precondition is met
		const worldstate_t pre = ap->act_pre[ i ]; // get precondition
		const bfield_t care = ( pre.dontcare ^ -1LL ); // flip dontcare to get care bits
	   // met is true if relevant values from precondition and from state match
		const bool met = ( ( pre.values & care ) == ( fr.values & care ) );
		if ( met )
		{
			// write names and costs to supplied arrays
			actionnames[ writer ] = ap->act_names[ i ];
			actioncosts[ writer ] = ap->act_costs[ i ];
			// set the final state with the effects of the action 
			to[ writer ] = goap_do_action( ap, i, fr );
			++writer;
		}
	}
	return writer;
}