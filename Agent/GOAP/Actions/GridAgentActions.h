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
	ActionSleep(pairCond effect):
	TimedAction(effect)
	{
		//SetConditions(name);
	}
	
//	ActionSleep(float expiryTime_, float cost_):
//	TimedAction(expiryTime_, cost_)
//	{
//		//SetConditions(name);
//	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
	
	bool IsValid(GridAgent* agent);
};


class ActionWander:public TimedAction{
	
public:
	ActionWander(pairCond effect)
	:TimedAction(effect){
		
	}
	
//	ActionWander(int cost_)
//	:TimedAction(2,cost_){
//		
//	}

	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
};

class ActionIdle:public TimedAction{
	
public:
	ActionIdle(pairCond effect)
	:TimedAction(effect){
		
	}
	
	//	ActionWander(int cost_)
	//	:TimedAction(2,cost_){
	//
	//	}
	
	void Execute(GridAgent* agent);
	bool TaskComplete(GridAgent* agent){
		return true;
	}
};




#endif /* defined(__AgentGridActions__GridAgentActions__) */

/*
GRAVEYARD
 */