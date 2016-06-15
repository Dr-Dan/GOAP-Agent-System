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
bool Action::PostconsInState(WorldState& state) const{
	for(pairCond p : state.GetConditionsMap()) {
		for(int l = 0; l < GetNumPostcons(); l++) {
			
			if(GetPostcon(l) == p){
				return true;
			}
			
		}
	}
	return false;
}

void Action::GetWorldStateEffect(WorldState& state){
		for(int l = 0; l < GetNumPostcons(); l++) {
				state.SetCondition(GetPostcon(l));
		}
}