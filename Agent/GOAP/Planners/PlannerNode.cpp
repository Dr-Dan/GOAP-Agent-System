//
//  PlanningNode.cpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 19/06/2016.
//
//

#include "PlannerNode.hpp"


PlannerNode::~PlannerNode(){
}

PlannerNode::PlannerNode():
NodeBase()
{}

PlannerNode::PlannerNode(TimedAction* actionIn_, int nodeId_):
NodeBase(nodeId_)
{
	action = actionIn_;
}

bool PlannerNode::HasPrecondition(){
	if(action->GetPrecon(0).first.empty()){
		return false;
	}
	return true;
}

bool PlannerNode::HasPostcondition(){
	if(action->GetPostcon(0).first.empty()){
		return false;
	}
	return true;
}