//
//  AgentAction.cpp
//  AgentGridActions
//
//  Created by D J Clarke on 03/03/2015.
//
//

#include "AgentAction.h"
//#include "GridAgent.h"
#include "WorldState.h"

// are any postcons found in state
bool TimedAction::PostconsInState(WorldState& state) const{
	for(pairCond p : state.GetConditionsMap()) {
		for(int l = 0; l < GetNumPostcons(); l++) {
			
			if(GetPostcon(l) == p){
				return true;
			}
			
		}
	}
	return false;
}

void TimedAction::GetWorldStateEffect(WorldState& state){
		for(int l = 0; l < GetNumPostcons(); l++) {
				state.SetCondition(GetPostcon(l));
		}
}

void TimedAction::AddEffect(pairCond effect){
	postConditions.push_back(effect);
}