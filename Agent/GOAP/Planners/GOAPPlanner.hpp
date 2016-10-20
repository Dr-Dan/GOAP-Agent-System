//
//  GOAPPlanner.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 09/09/2016.
//
//

#ifndef GOAPPlanner_hpp
#define GOAPPlanner_hpp

#include <stdio.h>
#include "AIBase.hpp"
#include "Goal.h"
#include "goap.hpp"	// for planner interface.
#include "astar.hpp"	// for A* search over worldstate space.
#include "WorldState.h"

class GridAgent;

class GOAPPlanner: public AIBase{
//	Goal* currentGoal;
public:
	GOAPPlanner(){}
	TimedAction* GetNextAction(GridAgent& agent);
	void Update(GridAgent& agent);
	std::string ToString();
//	vector<vector<char>> action_names;
//	vector<vector<char>> precon_names;

	void setupActionNames();
	
	// interfacing with stolk
	worldstate_t setup_goal(actionplanner_t* ap, worldstate_t* fr, char* desc, int desc_sz);
	// setting action planner
	// TODO: make individual versions of these, can then be used in group functions
	void action_conditions_to_ap(deque<TimedAction*> actions, actionplanner_t* ap);
	// TODO: cut worldstate_t or WorldState out of equation...Should adapt worldstate
	// or access function to interface with actionplanner
	void state_conditions_to_ap(WorldState state, worldstate_t* fr, actionplanner_t* ap);
	
//	Goal GetTargetGoal(Goal primaryGoal, WorldState* state, vector<Goal*>& allGoals);
	
};
#endif /* GOAPPlanner_hpp */
