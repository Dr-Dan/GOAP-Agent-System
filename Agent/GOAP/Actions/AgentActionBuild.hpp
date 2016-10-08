//
//  AgentActionBuild.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 10/06/2016.
//
//

#ifndef AgentActionBuild_hpp
#define AgentActionBuild_hpp

#include <stdio.h>
#include "AgentAction.h"
#include "WorldTypes.h"

class GridAgent;

class ActionChangeCell: public TimedAction{
protected:
	WorldTypes::ItemType targetType;
	
public:
	ActionChangeCell(pairCond effect, ItemType targetType_):
	TimedAction(effect),
	targetType(targetType_)
	{
	}
	
//	ActionChangeCell(float expiryTime_, float cost_, ItemType targetType_):
//	TimedAction(expiryTime_, cost_),
//	targetType(targetType_)
//	{
//	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
};

class ActionBuildHome: public TimedAction{
public:
	ActionBuildHome(pairCond effect):
	TimedAction(effect)
	{
	}
	
//	ActionBuildHome(float expiryTime_, float cost_):
//	TimedAction(expiryTime_, cost_)
//	{
//	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
	
	bool IsValid(GridAgent* agent);
};

class ActionDestroyHome: public TimedAction{
public:
	ActionDestroyHome(pairCond effect):
	TimedAction(effect)
	{
	}
	
//	ActionDestroyHome(float expiryTime_, float cost_):
//	TimedAction(expiryTime_, cost_)
//	{
//	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
	
	bool IsValid(GridAgent* agent);
};

#endif /* AgentActionBuild_hpp */
