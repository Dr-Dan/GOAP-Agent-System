//
//  AgentActionResource.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 10/06/2016.
//
//

#ifndef AgentActionResource_hpp
#define AgentActionResource_hpp

#include <stdio.h>
#include "AgentAction.h"
#include "WorldTypes.h"

class GridAgent;

class ActionPickupResource: public TimedAction{
protected:
	WorldTypes::ItemType resType;
	
public:
	ActionPickupResource(string name_, float expiryTime_, ItemType resType_):
	TimedAction(name_, expiryTime_),
	resType(resType_)
	{
		//SetConditions(name);
	}
	
	ActionPickupResource(string name_, float expiryTime_, float cost_, ItemType resType_):
	TimedAction(name_, expiryTime_, cost_),
	resType(resType_)
	{
		//SetConditions(name);
	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
	
	bool IsValid(GridAgent* agent);
	
};

class ActionUseCarriedResource: public TimedAction{
protected:
	WorldTypes::ItemType resType;
	
public:
	ActionUseCarriedResource(string name_, float expiryTime_, ItemType resType_):
	TimedAction(name_, expiryTime_),
	resType(resType_)
	{
		//SetConditions(name);
	}
	
	ActionUseCarriedResource(string name_, float expiryTime_, float cost_, ItemType resType_):
	TimedAction(name_, expiryTime_, cost_),
	resType(resType_)
	{
		//SetConditions(name);
	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
	
	bool IsValid(GridAgent* agent);
};

class ActionDropResource: public TimedAction{
protected:
	WorldTypes::ItemType resType;
	
public:
	ActionDropResource(string name_, float expiryTime_, ItemType resType_):
	TimedAction(name_, expiryTime_),
	resType(resType_)
	{
		//SetConditions(name);
	}
	
	ActionDropResource(string name_, float expiryTime_, float cost_, ItemType resType_):
	TimedAction(name_, expiryTime_, cost_),
	resType(resType_)
	{
		//SetConditions(name);
	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
	
	bool IsValid(GridAgent* agent);
	
};

#endif /* AgentActionResource_hpp */
