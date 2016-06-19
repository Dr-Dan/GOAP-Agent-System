//
//  PlanningNode.cpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 19/06/2016.
//
//

#include "PlannerNode.hpp"


PlannerNode::~PlannerNode(){
	action = NULL;
	linkFromIds.clear();
	linkToIds.clear();
}

PlannerNode::PlannerNode(TimedAction* actionIn_, int nodeId_){
	action = actionIn_;
	nodeId = nodeId_;
}

bool PlannerNode::isEndNode(){
	if(linkToIds.empty()){
		return true;
	}
	return false;
}

bool PlannerNode::isStartNode(){
	if(linkFromIds.empty()){
		return true;
	}
	return false;
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