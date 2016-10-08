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
	ActionGoto(pairCond effect, ItemType gotoType_, GotoSpec gotoSpec_):
	TimedAction(effect),
	gotoType(gotoType_),
	gotoSpec(gotoSpec_)
	{
		//SetConditions(name);
	}
	
//	ActionGoto(float expiryTime_, float cost_, ItemType gotoType_, GotoSpec gotoSpec_):
//	TimedAction( expiryTime_, cost_),
//	gotoType(gotoType_),
//	gotoSpec(gotoSpec_)
//	{
//		//SetConditions(name);
//	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);

	void GetWorldStateEffect(WorldState& state);
};

class ActionGotoStorage: public TimedAction{
protected:
	WorldTypes::GotoSpec gotoSpec;
	
public:
	ActionGotoStorage(pairCond effect, GotoSpec gotoSpec_):
	TimedAction(effect),
	gotoSpec(gotoSpec_)
	{
		//SetConditions(name);
	}
	
//	ActionGotoStorage(float expiryTime_, float cost_, ItemType gotoType_, GotoSpec gotoSpec_):
//	TimedAction( expiryTime_, cost_),
//	gotoSpec(gotoSpec_)
//	{
//		//SetConditions(name);
//	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
	
	bool IsValid(GridAgent* agent);
	
	void GetWorldStateEffect(WorldState& state);

};

#endif /* AgentActionGoto_hpp */
