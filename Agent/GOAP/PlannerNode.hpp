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

// should extend NodeBase really
class TimedAction;
class PlannerNode{
public:
	TimedAction* action;
	vector<int> linkToIds, linkFromIds;
	int nodeId = 0;
	//    bool isValid = true;
	
	//    string name;
	//    int cost;
	
	~PlannerNode();
	PlannerNode(TimedAction* actionIn_, int nodeId_);
	
	// ---------------------------------------------
	
	bool isEndNode();
	bool isStartNode();
	bool HasPrecondition();
	bool HasPostcondition();
	
	int GetId(){return nodeId;}
	
};

#endif /* PlanningNode_hpp */
