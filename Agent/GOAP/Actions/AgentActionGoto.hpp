//
//  AgentActionGoto.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 10/06/2016.
//
//

#ifndef AgentActionGoto_hpp
#define AgentActionGoto_hpp

#include <stdio.h>
#include "AgentAction.h"
#include "WorldTypes.h"

class ActionGoto: public TimedAction{
protected:
	WorldTypes::ItemType gotoType;
	WorldTypes::GotoSpec gotoSpec;
	
public:
	ActionGoto(string name_, float expiryTime_, ItemType gotoType_, GotoSpec gotoSpec_):
	TimedAction(name_, expiryTime_),
	gotoType(gotoType_),
	gotoSpec(gotoSpec_)
	{
		//SetConditions(name);
	}
	
	ActionGoto(string name_, float expiryTime_, float cost_, ItemType gotoType_, GotoSpec gotoSpec_):
	TimedAction(name_, expiryTime_, cost_),
	gotoType(gotoType_),
	gotoSpec(gotoSpec_)
	{
		//SetConditions(name);
	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);

	void GetWorldStateEffect(WorldState& state);
};

class ActionGotoStorage: public TimedAction{
protected:
	WorldTypes::GotoSpec gotoSpec;
	
public:
	ActionGotoStorage(string name_, float expiryTime_, GotoSpec gotoSpec_):
	TimedAction(name_, expiryTime_),
	gotoSpec(gotoSpec_)
	{
		//SetConditions(name);
	}
	
	ActionGotoStorage(string name_, float expiryTime_, float cost_, ItemType gotoType_, GotoSpec gotoSpec_):
	TimedAction(name_, expiryTime_, cost_),
	gotoSpec(gotoSpec_)
	{
		//SetConditions(name);
	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
	
	bool IsValid(GridAgent* agent);
	
	void GetWorldStateEffect(WorldState& state);

};

#endif /* AgentActionGoto_hpp */
