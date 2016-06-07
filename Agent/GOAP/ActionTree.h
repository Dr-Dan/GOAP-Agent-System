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

using namespace std;

class TreeNode{
public:
    TimedAction* action;
    vector<int> linkToIds, linkFromIds;
    int nodeId = 0;
//    bool isValid = true;
	
//    string name;
//    int cost;
	
    ~TreeNode(){
        action = NULL;
		linkFromIds.clear();
		linkToIds.clear();
    }
	
    TreeNode(TimedAction* actionIn_, int nodeId_){
        action = actionIn_;
        nodeId = nodeId_;
    }
	
	// ---------------------------------------------
    
    bool isEndNode(){
        if(linkToIds.empty()){
            return true;
        }
        return false;
    }
    
    bool isStartNode(){
        if(linkFromIds.empty()){
            return true;
        }
        return false;
    }
    
    bool HasPrecondition(){
        if(action->GetPrecon(0).first.empty()){
            return false;
        }
        return true;
    }
    
    bool HasPostcondition(){
        if(action->GetPostcon(0).first.empty()){
            return false;
        }
        return true;
    }
    
};

class ActionTree{
    // problem somewhere in tree node
    Goal previousGoal;
    bool goalSet = false;
    map<int, vector<TreeNode*> > mapTreeLevels;
    
    int numLevels = 0;
    int firstValidLevel = 0;
    int currentId = 0;
    
    WorldState goalState;
	
	vector<pairCond> vitalConditions;
	vector<int> vitalTreeIndex;
public:
    
    ~ActionTree();

    ActionTree();
	
    void ClearMapLevels();
	void ClearNodes();
    
    void ResetTree();
    void BuildTree(const deque<TimedAction*>&  actionsIn, Goal goal);

	bool GoalIsChanged(Goal goalIn);
	int GetVitalIndex(const WorldState& currentState);
	void UpdateVitalInfo(Action* currentAction, int currentLevels);
	
    // gets first valid node in tree
    TreeNode GetFirstValidNode();
    
//    void PrintTree();
	string GetTreeString();

	void SetLevelAndPair(pairCond& refPair_, int& level_, const WorldState& currentState);

	
    void PrintGoalState();
    
    TimedAction* GetActionForState(WorldState currentState);
	
	
	TimedAction* GetActionLowestCost(pairCond& refPair_, int highestLevel);
};

#endif /* defined(__AgentGOAPActionsTestSimpler__ActionTree__) */
