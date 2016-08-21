//
//  GridActions.h
//  AgentGridActions
//
//  Created by D J Clarke on 03/03/2015.
//
//

#ifndef __AgentGridActions__GridAgentActions__
#define __AgentGridActions__GridAgentActions__

#include <stdio.h>
#include "AgentAction.h"
//#include "ofMain.h"
#include "WorldTypes.h"
#include "AgentActionGoto.hpp"
#include "AgentActionBuild.hpp"
#include "AgentActionResource.hpp"

class GridAgent;


class ActionSleep: public TimedAction{
public:
	ActionSleep(string name_, float expiryTime_):
	TimedAction(name_, expiryTime_)
	{
		//SetConditions(name);
	}
	
	ActionSleep(string name_, float expiryTime_, float cost_):
	TimedAction(name_, expiryTime_, cost_)
	{
		//SetConditions(name);
	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
	
	bool IsValid(GridAgent* agent);
};


class ActionWander:public TimedAction{
	
public:
	ActionWander()
	:TimedAction("Wander", 2){
		
	}
	
	ActionWander(int cost_)
	:TimedAction("Wander", 2,cost_){
		
	}
	
	ActionWander(string name_,int cost_)
	:TimedAction(name_, 2,cost_){
		
	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
};

#endif /* defined(__AgentGridActions__GridAgentActions__) */

/*
GRAVEYARD
 */