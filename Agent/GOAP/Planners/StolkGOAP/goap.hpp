//
//  goap.hpp
//  GPGOAP_cpp
//

// from Abraham T. Stolk's excellent GOAP repo: https://github.com/stolk/GPGOAP
// Under the Apache 2.0 license: http://www.apache.org/licenses/LICENSE-2.0

#ifndef goap_hpp
#define goap_hpp

#include <stdio.h>

#include <cstdbool>
#include <cstdint>
//#else
//#include <stdbool.h>
//#include <stdint.h>
//#endif

#define MAXATOMS 64
#define MAXACTIONS 64

typedef int64_t bfield_t;

//!< Describes the world state by listing values (t/f) for all known atoms.
struct worldstate_t
{
	bfield_t values;	//!< Values for atoms.
	bfield_t dontcare;	//!< Mask for atoms that do not matter.
};


//!< Action planner that keeps track of world state atoms and its action repertoire.
struct actionplanner_t
{
	const char* atm_names[ MAXATOMS ];	//!< Names associated with all world state atoms.
	int numatoms;				//!< Number of world state atoms.
	
	const char* act_names[ MAXACTIONS ];	//!< Names of all actions in repertoire.
	worldstate_t act_pre[ MAXACTIONS ];	//!< Preconditions for all actions.
	worldstate_t act_pst[ MAXACTIONS ];	//!< Postconditions for all actions (action effects).
	int act_costs[ MAXACTIONS ];		//!< Cost for all actions.
	int numactions;				//!< The number of actions in out repertoire.
	
};

class goap{
	static worldstate_t goap_do_action( actionplanner_t* ap, int actionnr, worldstate_t fr );

public:
	//!< Initialize an action planner. It will clear all information on actions and state.
	static void goap_actionplanner_clear( actionplanner_t* ap );
	
	//!< Initialize a worldstate to 'dontcare' for all state atoms.
	static void goap_worldstate_clear( worldstate_t* ws );
	
	//!< Set an atom of worldstate to specified value.
	static bool goap_worldstate_set( actionplanner_t* ap, worldstate_t* ws, const char* atomname, bool value );
	
	//!< Add a precondition for named action.
	static bool goap_set_pre( actionplanner_t* ap, const char* actionname, const char* atomname, bool value );
	
	//!< Add a postcondition for named action.
	static bool goap_set_pst( actionplanner_t* ap, const char* actionname, const char* atomname, bool value );
	
	//!< Set the cost for named action.
	static bool goap_set_cost( actionplanner_t* ap, const char* actionname, int cost );
	
	//!< Describe the action planner by listing all actions with pre and post conditions. For debugging purpose.
	static void goap_description( actionplanner_t* ap, char* buf, int sz );
	
	//!< Describe the worldstate by listing atoms that matter, in lowercase for false-valued, and uppercase for true-valued atoms.
	static void goap_worldstate_description( const actionplanner_t* ap, const worldstate_t* ws, char* buf, int sz );
	
	//!< Given the specified 'from' state, list all possible 'to' states along with the action required, and the action cost. For internal use.
	static int goap_get_possible_state_transitions( actionplanner_t* ap, worldstate_t fr, worldstate_t* to, const char** actionnames, int* actioncosts, int cnt );
	
};
#endif /* goap_hpp */
