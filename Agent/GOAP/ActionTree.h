//
//  ActionTree.h
//  AgentGOAPActionsTestSimpler
//
//  Created by D J Clarke on 22/04/2015.
//
//

#ifndef __AgentGOAPActionsTestSimpler__ActionTree__
#define __AgentGOAPActionsTestSimpler__ActionTree__

#include <stdio.h>
#include "AgentAction.h"
#include "Goal.h"
#include <vector>
#include <deque>
#include "WorldState.h"
#include "Utility.h"
#include "PlannerNode.hpp"
#include "AIBase.hpp"
#include "NodeBase.hpp"

using namespace std;
class GridAgent;

class ActionTree: public AIBase{
    // problem somewhere in tree node
    Goal previousGoal;
    bool goalSet = false;
    map<int, vector<PlannerNode*> > mapTreeLevels;
    
    int numLevels = 0;
    int firstValidLevel = 0;
    int currentId = 0;
    
    WorldState goalState;
	
	vector<pairCond> vitalConditions;
	vector<int> vitalTreeIndex;
public:
    
    ~ActionTree();

    ActionTree();
	
	void Update(GridAgent& agent);
	
	PlannerNode* GetNode(int nodeId);
	
    void ClearMapLevels();
	void ClearNodes();
    
    void ResetTree();
    void BuildTree(const deque<TimedAction*>&  actionsIn, Goal goal);
	void PruneTree(const deque<TimedAction*>&  actionsIn);
	void LinkNodes(PlannerNode* fromNode, PlannerNode* toNode);
	void AddAction(TimedAction* action, vector<PlannerNode*>& newNodes, PlannerNode* tNode);

	bool GoalIsChanged(Goal goalIn);
	int GetVitalIndex(const WorldState& currentState);
	void UpdateVitalInfo(Action* currentAction, int currentLevels);
	
    // gets first valid node in tree
    PlannerNode GetFirstValidNode();
    
//    void PrintTree();
	string ToString();

//	void FindLevelAndPair(pairCond& refPair_, int& level_, const WorldState& currentState);
	void FindLevelAndPair(pairCond& refPair_, int& level_, const WorldState& currentState, GridAgent& agent);
	
    void PrintGoalState();
    
//    TimedAction* GetActionForState(WorldState currentState);
	TimedAction* GetAction(GridAgent& agent);

	
	TimedAction* GetBestAction(pairCond& refPair_, int highestLevel);
	TimedAction* GetBestAction(GridAgent* agent, pairCond& refPair_, int highestLevel);

};

#endif /* defined(__AgentGOAPActionsTestSimpler__ActionTree__) */
