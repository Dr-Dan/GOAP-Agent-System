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

class GridAgent;

class GOAPPlanner: public AIBase{
//	Goal* currentGoal;
public:
	GOAPPlanner(){}
	TimedAction* GetNextAction(GridAgent& agent);
	void Update(GridAgent& agent);
	std::string ToString();
	
	Goal GetTargetGoal(Goal primaryGoal, WorldState* state, vector<Goal*>& allGoals);
};
#endif /* GOAPPlanner_hpp */
