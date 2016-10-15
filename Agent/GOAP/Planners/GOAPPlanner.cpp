//
//  GOAPPlanner.cpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 09/09/2016.
//
//

#include "GOAPPlanner.hpp"
#include "GridAgent.h"
#include "GridAgentActions.h"

TimedAction* GOAPPlanner::GetNextAction(GridAgent& agent){
	return agent.actionsModule->getPossibleActions()[0];
//	return nullptr;
}

/*
 store goal in goalList if its effect satisfies nextGoal
 for each in goalList, check against world state
 if it solves world state
 choose the goal that would follow it
 */
Goal GOAPPlanner::GetTargetGoal(Goal primaryGoal, WorldState* state, vector<Goal*>& allGoals){

	return *allGoals[0];
}

void GOAPPlanner::Update(GridAgent& agent){
	
}

std::string GOAPPlanner::ToString(){
	return "";
}