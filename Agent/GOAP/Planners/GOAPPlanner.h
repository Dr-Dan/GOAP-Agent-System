//
//  GOAPPlanner.h
//  AgentGOAPActionsTestSimpler
//
//  Created by D J Clarke on 22/04/2015.
//
//

#ifndef __AgentGOAPActionsTestSimpler__GOAPPlanner__
#define __AgentGOAPActionsTestSimpler__GOAPPlanner__

#include <stdio.h>
#include <vector>
#include <deque>

#include "AgentAction.h"
#include "Goal.h"
#include "WorldState.h"
#include "Utility.h"
#include "PlannerNode.hpp"
#include "AIBase.hpp"
#include "NodeBase.hpp"

using namespace std;
class GridAgent;

class ConditionStrategy{
public:
	virtual int GetNumConditions(const PlannerNode& tNode){};
	virtual pairCond GetCondition(const PlannerNode& tNode, int i){};
};

class PreconStrategy: public ConditionStrategy{
public:
	 int GetNumConditions(const PlannerNode& tNode){
		return tNode.action->GetNumPrecons();
	}
	 pairCond GetCondition(const PlannerNode& tNode, int i){
		tNode.action->GetPrecon(i);
	}
};

class PostconStrategy: public ConditionStrategy{
public:
	 int GetNumConditions(const PlannerNode& tNode){
		return tNode.action->GetNumPostcons();
	}
	 pairCond GetCondition(const PlannerNode& tNode, int i){
		tNode.action->GetPostcon(i);
	}
};

class GOAPPlanner: public AIBase{
    // problem somewhere in tree node
    Goal previousGoal;
    bool goalSet = false;
    map<int, vector<PlannerNode*> > mapTreeLevels;
    
    int numLevels = 0;
    int firstValidLevel = 0;
    int currentId = 0;
    
    WorldState goalState;
	
//	vector<pairCond> vitalConditions;
//	vector<int> vitalTreeIndex;
public:
    
    ~GOAPPlanner();

    GOAPPlanner();
	
	void Update(GridAgent& agent);
	
	PlannerNode* GetNode(int nodeId);
	
    void ClearMapLevels();
	void ClearNodes();
    
    void ResetTree();
    void BuildTree(const deque<TimedAction*>&  actionsIn, Goal goal);
	TimedAction* GetHighestAction(PlannerNode* checkNode, const deque<TimedAction*>&  actionsIn, WorldState& checkState);
	void AddActionWithPreconds(PlannerNode* tNode, TimedAction* currentAction, vector<string>& actionsOnLevel, vector<PlannerNode*>& newNodes);
	
	void FindGoalLevelActions(int& currentId, const Goal& goal, TimedAction* currentAction, vector<PlannerNode*>& newNodes, vector<WorldState>& refStates);
	
	void PruneTree(const deque<TimedAction*>&  actionsIn);
	void FindGoodNodes(int numRuns, vector<int>& goodNodes, const vector<PlannerNode*>& startNodes, const mapCond& priorityConds);
	void RemoveDeadNodes(const vector<int>& goodNodes);
	
	void LinkNodes(PlannerNode* fromNode, PlannerNode* toNode);
	void AddAction(TimedAction* action, vector<PlannerNode*>& newNodes, PlannerNode* tNode);

	bool GoalIsChanged(Goal goalIn);

    // gets first valid node in tree
    PlannerNode GetFirstValidNode();
    
//    void PrintTree();
	string ToString();

	void FindLevelAndPair(pairCond& refPair_, int& level_, const WorldState& currentState);
	
	int CalculateLevelPriority(const mapCond& priorityConds, const WorldState& currentState);
	void FindLevelAndPairFinal(int startLevel, int& level_, pairCond& refPair_, const WorldState& currentState);
	
    void PrintGoalState();
    
//    TimedAction* GetActionForState(WorldState currentState);
	TimedAction* GetNextAction(GridAgent& agent);

	
	TimedAction* GetBestAction(pairCond& refPair_, int highestLevel);
	TimedAction* GetBestAction(GridAgent* agent, pairCond& refPair_, int highestLevel);

	void FindLowestCostActionForConds(const PlannerNode& tNode, pairCond refPair, ConditionStrategy strat, TimedAction& actionOut);
	void FindLowestCostAction(const TimedAction& action, int& lowestCostOut, TimedAction& actionOut);

};



#endif /* defined(__AgentGOAPActionsTestSimpler__GOAPPlanner__) */
