//
//  NodeBase.cpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 19/06/2016.
//
//

#include "NodeBase.hpp"
#include "PlannerNode.hpp"
void NodeBase::SetId(int nodeId_){
	nodeId = nodeId_;
}
void NodeBase::LinkNodes(PlannerNode* fromNode, PlannerNode* toNode){
	fromNode->linkFromIds.push_back(toNode->nodeId);
	toNode->linkToIds.push_back(fromNode->nodeId);
}

void NodeBase::Add(NodeBase* tree){
	nodes.push_back(tree);
}

void NodeBase::Clear(){
	nodes.clear();
}

bool NodeBase::isEndNode(){
	if(linkToIds.empty()){
		return true;
	}
	return false;
}

bool NodeBase::isStartNode(){
	if(linkFromIds.empty()){
		return true;
	}
	return false;
}