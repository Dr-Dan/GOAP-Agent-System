//
//  ActionTree.cpp
//  AgentGOAPActionsTestSimpler
//
//  Created by D J Clarke on 22/04/2015.
//
//

#include "ActionTree.h"

ActionTree::~ActionTree(){
	//        Utility::ClearContainerPointers(nodes);
	ClearMapLevels();
}

void ActionTree::ClearMapLevels(){
	for(pair<int, vector<TreeNode*> > tNV : mapTreeLevels){
		Utility::ClearContainerPointers(tNV.second);
	}
	
	mapTreeLevels.clear();
	numLevels = 0;
}

void ActionTree::ResetTree(){
	ClearMapLevels();
	goalState = WorldState();
	currentId = 0;
	firstValidLevel = 0;
	vitalConditions.clear();
	vitalTreeIndex.clear();
}

ActionTree::ActionTree(){}

void ActionTree::UpdateVitalInfo(Action* currentAction, int currentLevels){
	for(pairCond vitalPair : vitalConditions){
		if(currentAction->GetPostcon(0) == vitalPair){
			if(!count(vitalTreeIndex.begin(), vitalTreeIndex.end(), currentLevels)){
				vitalTreeIndex.push_back(currentLevels);
				sort(vitalTreeIndex.begin(), vitalTreeIndex.end());
				//				reverse(vitalTreeIndex.begin(), vitalTreeIndex.end());
			}
		}
	}
}

void ActionTree::BuildTree(const deque<TimedAction*>&  actionsIn, Goal goal){
	ResetTree(); // clear currently stored tree for rebuild
	
	int currentLevels = 0;
	int maxLevels = 10;
	bool treeComplete = false;
	
	if(goal.HasVitalCondition()){
		vitalConditions = goal.GetVitalConditions();
	}
	
	while(currentLevels < maxLevels && !treeComplete ){
		// stores created ActionTreeNode(s)
		vector<TreeNode*> newNodes;
		
		// for all actions
		for(int i = 0; i < actionsIn.size(); i++) {
			TimedAction* currentAction = actionsIn[i];
			
			// firstly get goal (Level 0) relative actions
			if(currentLevels == 0){
				for(int j = 0; j < currentAction->GetNumPostcons(); j++) {
					
					// does action postcondition match goal condition
					if(currentAction->GetPostcon(j) == goal.GetCondition(0)){
						
						UpdateVitalInfo(currentAction, currentLevels);
						
						// Update goal state
						goalState.SetCondition(goal.GetCondition(0));
						newNodes.push_back(new TreeNode(currentAction, currentId));
						
						// increase assigned node id number
						currentId++;
					}
				}
				// if below top level...
			} else{
				vector<string> actionsOnLevel;
				deque<pairCond> condPriority;
				
				for(int j = 0; j < mapTreeLevels[currentLevels-1].size(); j++) {
					TreeNode* tNode = mapTreeLevels[currentLevels-1].at(j);
					
					for(int l = 0; l < tNode->action->GetNumPrecons(); l++) {
						for(int k = 0; k < currentAction->GetNumPostcons(); k++) {
							
							if(currentAction->GetPostcon(k) == tNode->action->GetPrecon(l)){
								UpdateVitalInfo(currentAction, currentLevels);
								
								// Update goal state
								goalState.SetCondition(currentAction->GetPostcon(k));
								
								// check action doesn't already exists on level
								if(!count(actionsOnLevel.begin(), actionsOnLevel.end(), currentAction->name)){
									// create node and add to vector of nodes on this level
									newNodes.push_back(new TreeNode(currentAction, currentId));
									// add action name to list of those used on this level
									actionsOnLevel.push_back(currentAction->name);
								}
								
								// setup IDs for node links
								tNode->linkFromIds.push_back(newNodes.back()->nodeId);
								newNodes.back()->linkToIds.push_back(tNode->nodeId);
								
								// increase assigned node id number
								currentId++;
							}
						} // for l
					} // for k
					
				} // for j
			}
		} // for i
		
		if(!newNodes.empty()){
			// insert current nodes for this tree level into map
			mapTreeLevels.insert(pair<int, vector<TreeNode*> >(currentLevels,newNodes));
			currentLevels++;
			
		} else{
			// if no nodes are created the tree is finished/failed
			treeComplete = true;
		}
	}
	
	
	numLevels = currentLevels;
	
	// store goal for checking if later goals are different
	previousGoal = goal;
	
}

bool ActionTree::GoalIsChanged(Goal goalIn){
	if(goalIn.GetName() != previousGoal.GetName()){
		return true;
	}
	return false;
}


void ActionTree::PrintGoalState(){
	cout<<endl<<"goalState:"<<endl;
	goalState.PrintValues();
	
}

// TODO
// adapt all this for multiple actions per level
// and vital goal conditions
TimedAction* ActionTree::GetActionForState(WorldState currentState){
	TimedAction* actionOut = NULL;
	
	if(!goalState.ConditionsMatch(currentState.GetConditionsMap())){
		pairCond refPair;
		int highestLevelMatch = -1, currentLevelMatch = -1;
		
		// finds the highest tree level that matches the supplied state
		// refPair is set to the matching condition pair
		
		SetLevelAndPair(refPair, highestLevelMatch, currentState);
		actionOut = GetActionLowestCost(refPair, highestLevelMatch);
	}
	return actionOut;
}


void ActionTree:: SetLevelAndPair(pairCond& refPair_, int& level_, const WorldState& currentState){
	
	int vitalLevel = 0;
	
	vitalLevel = GetVitalIndex(currentState);
	deque<pairCond> condOrder;
//	cout<<"----------------"<<endl;
//	cout<<"----------------"<<endl;
//	cout<<"----------------"<<endl;
//	goalState.PrintValues();
//	cout<<"----------------"<<endl;

	currentState.PrintValues();

	// for each level starting at highest
//	cout<<"----------------"<<endl;
	for(int i = numLevels-1; i >= vitalLevel; i--) {
		//	for(int i = vitalLevel; i < numLevels ; i++) {
		// for each node in this level
		for(TreeNode* tNode : mapTreeLevels[i]){
			int num_precons = tNode->action->GetNumPrecons();
			int num_postcons = tNode->action->GetNumPostcons();
			int num_matches = 0;

			// for each goal and current condition pair
			for(pairCond goalPair : goalState.GetConditionsMap()){
				for(pairCond currentPair : currentState.GetConditionsMap()){
					
					// if current cond found in goal state
					if(goalPair.first == currentPair.first){
//						for(int i = 0; i < num_precons; i++){
//							condOrder.push_back(tNode->action->GetPrecon(i));
//							printf("%s", condOrder[i].first.c_str());
//						}
						
						if(!tNode->isStartNode()){
//							if(num_precons <= 1){
								if(tNode->action->GetPrecon(0) == currentPair){
//									printf("%s \n", tNode->action->name.c_str());

									level_ = i;
									refPair_ = goalPair;
								}
//							} else{
//								for(int i = 0; i < num_precons; i++){
//									if(tNode->action->GetPrecon(i) == currentPair){
//										num_matches++;
//									}
//								}
//								if(num_matches >= num_precons){
//									level_ = i;
//									refPair_ = goalPair;
//								}
//							}
						} else{
							if(tNode->action->GetPostcon(0) == goalPair){
								level_ = i;
								refPair_ = goalPair;
							}
						}
					} // end: goalPair.first == currentPair.first
					
				}

			}
		
		} // end: tNode : mapTreeLevels[i]
	}
}

int ActionTree::GetVitalIndex(const WorldState& currentState){
	bool vitalFound = false;
	int levelOut = 0;
	if(!vitalTreeIndex.empty()){
		for(int i = numLevels-1; i >= 0; i--) {
			// for each node in this level
			for(TreeNode* tNode : mapTreeLevels[i]){
				for(pairCond currentPair : currentState.GetConditionsMap()){
					
					for(pairCond vitalPair : vitalConditions){
						if(tNode->action->GetPostcon(0) == vitalPair &&
						   currentPair.first == vitalPair.first &&
						   currentPair.second != vitalPair.second){
							
							vitalFound = true;
						}
					}
				}
			}
		}
		
		if(vitalFound){
			levelOut = vitalTreeIndex.back();
		}
	}
	
	return levelOut;
}

// should also check actions are still valid here - pass in state
TimedAction* ActionTree::GetActionLowestCost(pairCond& refPair_, int highestLevel){
	TimedAction* actionOut;
	int lowestCost = -1;
	if(mapTreeLevels[highestLevel].size() > 1){
		if(highestLevel != -1){
			for(TreeNode* tNode : mapTreeLevels[highestLevel]){
				if(!tNode->isStartNode()){
					if(refPair_ == tNode->action->GetPrecon(0)
					   && (tNode->action->cost < lowestCost || lowestCost == -1)){
						actionOut = tNode->action;
						lowestCost = tNode->action->cost;
					}
				} else{
					if(refPair_ == tNode->action->GetPostcon(0)
					   && (tNode->action->cost < lowestCost || lowestCost == -1)){
						actionOut = tNode->action;
						lowestCost = tNode->action->cost;
					}
				}
			}
		}
	} else{
		actionOut = mapTreeLevels[highestLevel].at(0)->action;
	}
	return actionOut;
}


string ActionTree::GetTreeString(){
	string treeOut = "";
	treeOut+="::START::\n";
	
	for(int i = 0; i < numLevels; i++) {
		treeOut += "LEVEL : " + ofToString(i);
		treeOut += "\n";
		
		//		treeOut +="Possible Actions:";
		//		treeOut += "\n";
		
		
		for(TreeNode* tNode : mapTreeLevels[i]){
			treeOut += "\n";
			
			treeOut +=tNode->action->name;
			treeOut += "\n";
			
			treeOut +="Node ID: " + ofToString(tNode->nodeId);
			treeOut += "\n";
			
			
			for(int nId : tNode->linkFromIds){
				treeOut +="Linked from: " + ofToString(nId);
				treeOut += "\n";
			}
			
			for(int nId : tNode->linkToIds){
				treeOut+= "Linked to: " + ofToString(nId);
				treeOut += "\n";
				
			}
			
			Action* tNA = tNode->action;
			
			treeOut += "Conditions:";
			treeOut += "\n";
			
			for(int i = 0; i < tNA->GetNumPrecons(); i++) {
				pairCond preCondition = tNA->GetPrecon(i);
				
				treeOut +="Pre: " + ofToString(preCondition.first) + " = " + ofToString(preCondition.second);
				treeOut += "\n";
			}
			
			for(int j = 0; j < tNA->GetNumPostcons(); j++) {
				pairCond postCondition = tNA->GetPostcon(j);
				
				treeOut += "Post: " + ofToString(postCondition.first) + " = " + ofToString(postCondition.second);
				treeOut += "\n";
			}
			
			//            if(tNode->isValid) cout<<"Is Valid"<<endl;
			//                if(tNode->action.IsValid()) cout<<"Is Valid"<<endl;
		}
		treeOut += "----------------------";
		treeOut += "\n";
		
	}
	
	treeOut += "\n";
	treeOut +="::END::";
	treeOut += "\n";
	
	return treeOut;
}


/*
 void ActionTree::PrintTree(){
	//        cout<<mapTreeLevels.size()<<endl;
	cout<<endl<<"::START::"<<endl;
	
	for(int i = 0; i < numLevels; i++) {
 cout<<endl<<"LEVEL : "<<i<<endl;
 cout<<"Possible Actions: "<<endl;
 
 for(TreeNode* tNode : mapTreeLevels[i]){
 //            cout<<endl<<tNode->action->name<<endl;
 cout<<"Node ID: "<<tNode->nodeId<<endl;
 
 for(int nId : tNode->linkFromIds){
 cout<<"Linked from: "<<nId<<endl;
 }
 
 for(int nId : tNode->linkToIds){
 cout<<"Linked to: "<<nId<<endl;
 }
 
 Action* tNA = tNode->action;
 cout<<"Conditions:"<<endl;
 pairCond preCondition = tNA->GetPrecon(0);
 pairCond postCondition = tNA->GetPostcon(0);
 cout<<"Pre: "<<preCondition.first<<" = "<<preCondition.second<<endl;
 cout<<"Post: "<<postCondition.first<<" = "<<postCondition.second<<endl;
 
 //            if(tNode->isValid) cout<<"Is Valid"<<endl;
 //                if(tNode->action.IsValid()) cout<<"Is Valid"<<endl;
 }
 cout<<"----------------------"<<endl;
	}
	cout<<endl<<"::END::"<<endl;
	
 }
 */
