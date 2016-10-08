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
	/*
	 get current goal -> cg
	 while(goal has preconditions):
		for each goal in all_goals:
	 if goal satisfies cg:
	 add to list(/level)(will need change for multiple goals)
	 cg = goal
	 break (or return from some other function)
	 
	 find all actions that fulfill cg
	 choose the most eligible action and return it
	 */
	
	deque<TimedAction*> a = agent.actionsModule->getPossibleActions();
	WorldState* state = agent.stateModule.GetCurrentState();
	Goal topGoal = agent.motiveModule.GetTopGoal();
	//	printf("goal state: %s\n", topGoal.effects[0].first.c_str());
	
	if(state->ConditionsContainPairMatch(topGoal.effects[0])){
		printf("chosen goal effect (%s) is already met in state, no actions to be done\n",
			   topGoal.effects[0].first.c_str());
		return a[0];
	}
	
	Goal targetGoal = GetTargetGoal(topGoal, state, agent.motiveModule.goals);
	
	printf("next goal does: %s\n", targetGoal.effects[0].first.c_str());
	if(!targetGoal.preconditions.empty()){
		printf("next goal needs: %s\n", targetGoal.preconditions[0].first.c_str());
	}
	
	for(int i = 0; i < a.size(); ++i){
		if(targetGoal.CanBeSolvedBy(*a[i])){
			printf("solved by: %s\n", a[i]->postConditions[0].first.c_str());
			return a[i];
		}
	}
	
	return nullptr;
}

/*
 store goal in goalList if its effect satisfies nextGoal
 for each in goalList, check against world state
 if it solves world state
 choose the goal that would follow it
 */
Goal GOAPPlanner::GetTargetGoal(Goal primaryGoal, WorldState* state, vector<Goal*>& allGoals){
	bool stateMatch = false;
	vector<Goal> goalList;
	printf("------\n-");
	
	while(!primaryGoal.preconditions.empty()){
		
		for(int i = 0; i < allGoals.size(); ++i){
			Goal goal = *allGoals[i];
			if(primaryGoal.CanBeSolvedBy(goal)){
				goalList.push_back(goal);
				primaryGoal = goal;
				printf("%s\n", goal.effects[0].first.c_str());
			}
		}
	}
	
	printf("-------\n");
	for(int i = 0; i < goalList.size()-1; ++i){
		if(!goalList[i].preconditions.empty()){
			if(state->ConditionsContainPairMatch(goalList[i+1].effects[0])){
				return goalList[i];
			}
		}
	}
	
	// if the previous loop does not return,
	// the lowest item in the list is the best option
	return goalList.back();
}

void GOAPPlanner::Update(GridAgent& agent){
	
}

std::string GOAPPlanner::ToString(){
	return "";
}