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

class NodeBase
{
protected:
	std::vector<NodeBase*> nodes;
	int nodeId = -1;
	
public:
	NodeBase() = default;
	NodeBase(int nodeId_);
	std::vector<int> linkToIds, linkFromIds;

	void SetId(int nodeId_);
	int GetId(){return nodeId;}

	virtual void Add(NodeBase* tree);
	void Clear();
	
	bool isEndNode();
	bool isStartNode();
	
	// does this make sense? Should probably be in separate class
	static void LinkNodes(NodeBase* fromNode, NodeBase* toNode);

	
};
#endif /* NodeBase_hpp */
