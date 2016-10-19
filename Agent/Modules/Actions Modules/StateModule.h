//
//  StateModule.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 30/06/2015.
//
//

#ifndef __AgentGOBGridTest__StateModule__
#define __AgentGOBGridTest__StateModule__

#include <stdio.h>
#include "WorldState.h"
//class WorldState;
class GridAgent;
class StateModule{
	WorldState currentState;

public:
	StateModule():
	currentState(){
		currentState.SetCondition("athomelocation", false);
		currentState.SetCondition("atownedhome", false);
	}
	
	void UpdateState(GridAgent* agent);
	void SetCurrentState(WorldState stateIn); //  sets currentState from agent->memoryModule
	WorldState* GetCurrentState();
};
#endif /* defined(__AgentGOBGridTest__StateModule__) */
