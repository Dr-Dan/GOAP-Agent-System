//
//  NodeBase.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 19/06/2016.
//
//

/*
 A composite style class, used for nesting and tree like structures.
 */

#ifndef NodeBase_hpp
#define NodeBase_hpp

#include <stdio.h>
#include <vector>
class PlannerNode;
class NodeBase
{
protected:
	std::vector<NodeBase*> nodes;
	int nodeId = 0;
	
public:
	std::vector<int> linkToIds, linkFromIds;

	void SetId(int nodeId_);
	virtual void Add(NodeBase* tree);
	void Clear();

	static void LinkNodes(PlannerNode* fromNode, PlannerNode* toNode);
	
	bool isEndNode();
	bool isStartNode();
	
	int GetId(){return nodeId;}
};
#endif /* NodeBase_hpp */
