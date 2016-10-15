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
	ActionPickupResource(string name, ItemType resType_):
	TimedAction(name),
	resType(resType_)
	{
		//SetConditions(name);
	}
	
//	ActionPickupResource(float expiryTime_, float cost_, ItemType resType_):
//	TimedAction(expiryTime_, cost_),
//	resType(resType_)
//	{
//		//SetConditions(name);
//	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
	
	bool IsValid(GridAgent* agent);
	
};

class ActionUseCarriedResource: public TimedAction{
protected:
	WorldTypes::ItemType resType;
	
public:
	ActionUseCarriedResource(string name, ItemType resType_):
	TimedAction(name),
	resType(resType_)
	{
		//SetConditions(name);
	}
	
//	ActionUseCarriedResource(float expiryTime_, float cost_, ItemType resType_):
//	TimedAction(expiryTime_, cost_),
//	resType(resType_)
//	{
//		//SetConditions(name);
//	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
	
	bool IsValid(GridAgent* agent);
};

class ActionDropResource: public TimedAction{
protected:
	WorldTypes::ItemType resType;
	
public:
	ActionDropResource(string name, ItemType resType_):
	TimedAction(name),
	resType(resType_)
	{
		//SetConditions(name);
	}
	
//	ActionDropResource(float expiryTime_, float cost_, ItemType resType_):
//	TimedAction(expiryTime_, cost_),
//	resType(resType_)
//	{
//		//SetConditions(name);
//	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
	
	bool IsValid(GridAgent* agent);
	
};

#endif /* AgentActionResource_hpp */
