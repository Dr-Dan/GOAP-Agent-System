//
//  astar.hpp
//  GPGOAP_cpp
//
//  Created by D J Clarke on 11/09/2016.
//  Copyright © 2016 D J Clarke. All rights reserved.
//

#ifndef astar_hpp
#define astar_hpp

#include <stdio.h>
#include "goap.hpp"

#define LOGI(...) { printf( __VA_ARGS__ ); printf("\n"); }
#define LOGW(...) { printf( "WRN " __VA_ARGS__ ); printf("\n"); }
#define LOGE(...) { printf( "ERR " __VA_ARGS__ ); printf("\n"); }


//struct astarnode;

//!< A node in our network of world states.
struct astarnode
{
	worldstate_t ws;		//!< The state of the world at this node.
	int g;				//!< The cost so far.
	int h;				//!< The heuristic for remaining cost (don't overestimate!)
	int f;				//!< g+h combined.
	const char* actionname;		//!< How did we get to this node?
	worldstate_t parentws;		//!< Where did we come from?
};


typedef struct astarnode astarnode_t;

class astar{
	static int calc_h( worldstate_t fr, worldstate_t to );
	static int idx_in_opened( worldstate_t ws );
	static int idx_in_closed( worldstate_t ws );
	static void reconstruct_plan( actionplanner_t* ap, astarnode_t* goalnode, const char** plan, worldstate_t* worldstates, int* plansize );
public:
//! Make a plan of actions that will reach desired world state. Returns total cost of the plan.
static int astar_plan
(
 actionplanner_t* ap, 		//!< the goap action planner that holds atoms and action repertoire
 worldstate_t start, 		//!< the current world state
 worldstate_t goal, 		//!< the desired world state
 const char** plan,              //!< for returning all actions that make up plan
 worldstate_t* worldstates,      //!< for returning intermediate world states
 int* plansize                   //!< in: size of plan buffer, out: size of plan (in nr of steps)
);
};
#endif /* astar_hpp */
