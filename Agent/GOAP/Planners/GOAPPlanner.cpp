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
#include <vector>

void GOAPPlanner::setupActionNames(){
	
}

void GOAPPlanner::action_conditions_to_ap(deque<TimedAction*> actions, actionplanner_t* ap){
	for(int i = 0; i < actions.size(); ++i){
		
		for(int j = 0; j < actions[i]->preConditions.size(); ++j){
			goap::goap_set_pre( ap, actions[i]->name.c_str(),
							   actions[i]->preConditions[j].first.c_str(),
							   (bool)actions[i]->preConditions[j].second);
		}
		
		for(int j = 0; j < actions[i]->postConditions.size(); ++j){
			goap::goap_set_pst( ap, actions[i]->name.c_str(),
							   actions[i]->postConditions[j].first.c_str(),
							   (bool)actions[i]->postConditions[j].second);
		}
	}
}

void GOAPPlanner::state_conditions_to_ap(WorldState state, worldstate_t* fr,actionplanner_t* ap){
	for(int i = 0; i < state.GetNumConditions(); ++i){
		pairCond cond = state.GetConditionPair(i);
		goap::goap_worldstate_set( ap, fr, state.GetConditionPair(i).first.c_str(), cond.second);
	}
}

TimedAction* GOAPPlanner::GetNextAction(GridAgent& agent){
	
	actionplanner_t ap;
	goap::goap_actionplanner_clear( &ap );
	
	worldstate_t fr;
	char desc[ 4096 ];
	deque<TimedAction*> actions = agent.actionsModule->getPossibleActions();
	
	action_conditions_to_ap(actions, &ap);
	
	
	goap::goap_description( &ap, desc, sizeof( desc )  );
//	LOGI( "%s", desc );
	
	
	goap::goap_worldstate_clear( &fr );
	WorldState currentState = *agent.stateModule.GetCurrentState();
	state_conditions_to_ap(currentState, &fr, &ap);
	
	worldstate_t goal;
	goap::goap_worldstate_clear( &goal );
	Goal g = agent.motiveModule.GetTopGoal();

	WorldState state;
	for(int i = 0; i < g.GetNumCons(); ++i){
		state.SetCondition(g.GetCondition(i));
	}
	state_conditions_to_ap(state, &goal, &ap);
	
	worldstate_t states[16];
	const char* plan[16];
	int plansz=16;
	const int plancost = astar::astar_plan( &ap, fr, goal, plan, states, &plansz );
//	LOGI( "plancost = %d", plancost );
	goap::goap_worldstate_description( &ap, &fr, desc, sizeof( desc ) );
//	LOGI( "%-23s%s", "initial state", desc );
	
//	printf("\nPLAN:\n");
	for ( int i=0; i<plansz; ++i )
	{
		goap::goap_worldstate_description( &ap, states+i, desc, sizeof( desc ) );
//		LOGI( "%d: %-20s%s", i, plan[i], desc );
		//		LOGI( "%-20s", plan[i] );
	}
	
	if(plancost > 0){
	string s = "";
	s.append(plan[0]);
	return agent.actionsModule->FindAction(s);
	}
	return agent.actionsModule->getPossibleActions()[0];
	
	//	return nullptr;
}

void GOAPPlanner::Update(GridAgent& agent){
	
}

std::string GOAPPlanner::ToString(){
	return "";
}