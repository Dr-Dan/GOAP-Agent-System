//
//  PlanningNode.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 19/06/2016.
//
//

#ifndef PlanningNode_hpp
#define PlanningNode_hpp

#include <stdio.h>
#include <vector>

#include "AgentAction.h"
#include "PlannerNode.hpp"
#include "NodeBase.hpp"

// should extend NodeBase really
class TimedAction;
class PlannerNode: public NodeBase{
public:
	TimedAction* action = nullptr;

	~PlannerNode();
	PlannerNode();
	PlannerNode(TimedAction* actionIn_, int nodeId_);
	
	// ---------------------------------------------

//	bool HasPrecondition();
	bool HasPostcondition();
		
};

#endif /* PlanningNode_hpp */
