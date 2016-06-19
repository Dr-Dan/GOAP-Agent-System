//
//  ActionTree.cpp
//  AgentGOAPActionsTestSimpler
//
//  Created by D J Clarke on 22/04/2015.
//
//

#include "ActionTree.h"
#include "GridAgent.h"

ActionTree::~ActionTree(){
	//        Utility::ClearContainerPointers(nodes);
	ClearMapLevels();
}

PlannerNode* ActionTree::GetNode(int nodeId){
	for(pair<int, vector<PlannerNode*> > tNV : mapTreeLevels){
		for(int i = 0; i < tNV.second.size(); i++){
			if (tNV.second[i]->GetId() == nodeId) {
				return tNV.second[i];
			}
		}
	}
	return NULL;
}

void ActionTree::Update(GridAgent& agent){
	Goal topGoal = agent.motiveModule.GetTopGoal();
	if(GoalIsChanged(topGoal)){
		BuildTree(agent.actionsModule->getPossibleActions(), topGoal);
}
}

void ActionTree::ClearMapLevels(){
	for(pair<int, vector<PlannerNode*> > tNV : mapTreeLevels){
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
	// for each vital condition
	for(pairCond vitalPair : vitalConditions){
		// check for a match with the action
		if(currentAction->GetPostcon(0) == vitalPair){
			// if the current level is not saved
			if(!count(vitalTreeIndex.begin(), vitalTreeIndex.end(), currentLevels)){
				// add level to list and sort
				vitalTreeIndex.push_back(currentLevels);
				sort(vitalTreeIndex.begin(), vitalTreeIndex.end());
				//				reverse(vitalTreeIndex.begin(), vitalTreeIndex.end());
			}
		}
	}
}

/*
 Backwards pass:
 For goal conds:
	link any actions that meet conds
 
 For each level:
	link any actions that have pre->post condition match in next level
	if action has no precond:
 check any required pre-conditions that have not been met in -
 journey up to this point (re-do journey?)
 and add action with matching postcond to lower tree level
 
 Forward Pass:
 Starting from base...
 Ascend tree and store succesful paths
 If any nodes are not in any goal meeting solutions then prune them
 */

// TODO: this is way too long!!! Shorten please
void ActionTree::BuildTree(const deque<TimedAction*>&  actionsIn, Goal goal){
	ResetTree(); // clear currently stored tree for rebuild
	
	int currentLevels = 0;
	int maxLevels = 10;
	bool treeComplete = false;
	
	
	if(goal.HasVitalCondition()){
		vitalConditions = goal.GetVitalConditions();
	}
	
	while(currentLevels < maxLevels && !treeComplete ){
		// stores created ActionPlannerNode(s)
		vector<PlannerNode*> newNodes;
		vector<WorldState> refStates;
		
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
						refStates.push_back(goalState);
						
						newNodes.push_back(new PlannerNode(currentAction, currentId));
						
						// increase assigned node id number
						currentId++;
					}
				}
				// if below top level...
			} else{
				vector<string> actionsOnLevel;
				deque<pairCond> condPriority;
				
				// for all nodes at current level...
				for(int j = 0; j < mapTreeLevels[currentLevels-1].size(); j++) {
					PlannerNode* tNode = mapTreeLevels[currentLevels-1].at(j);
					
					// ----------------------------------------------------------
					// if action has no preconditions, try to add an action that is useful
					if(tNode->action->GetNumPrecons() == 0 &&
					   tNode->linkFromIds.empty()){
						WorldState checkState;
						PlannerNode* checkNode = tNode;
						vector<int> linkToIds = tNode->linkToIds;
						checkNode->action->GetWorldStateEffect(checkState);
						
						TimedAction* highestAc = NULL;
						
						while(!linkToIds.empty()){
							int numPrecons = checkNode->action->GetNumPrecons();
							
							// check if any preconditions can be solved by any actions
							for(int i = 0; i < numPrecons; i++){
								pairCond p = checkNode->action->GetPrecon(i);
								
								for(int j = 0; j < actionsIn.size(); j++){
									if(p == actionsIn[j]->GetPostcon(0) &&
									   !checkState.SharesCondition(actionsIn[j]->GetPostcon(0))){
										highestAc = actionsIn[j];
									}
								}
							}
							
							// retrace back towards goal and check
							// which goal conditions have been met
							linkToIds = checkNode->linkToIds;
							
							// TODO - fix system for Nodes with multiple linkTo's
							for(int i = 0; i < linkToIds.size(); i++){
								checkNode = GetNode(linkToIds[i]);
							}
							
							// update world state for each
							checkNode->action->GetWorldStateEffect(checkState);
						}
						
						
						// check action doesn't already exists on level
						if(highestAc != NULL &&
						   !count(actionsOnLevel.begin(), actionsOnLevel.end(), highestAc->name)){
							
							// add action name to list of those used on this level
							actionsOnLevel.push_back(highestAc->name);
							
							// add action to lists etc
							AddAction(highestAc, newNodes, tNode);
							for(int l = 0; l < highestAc->GetNumPostcons(); l++) {
								goalState.SetCondition(highestAc->GetPostcon(l));
							}
						}
						//						continue;
						break;
					}
					// ----------------------------------------------------------
					
					for(int k = 0; k < tNode->action->GetNumPrecons(); k++) {
						for(int l = 0; l < currentAction->GetNumPostcons(); l++) {
							
							if(currentAction->GetPostcon(l) == tNode->action->GetPrecon(k)){
								UpdateVitalInfo(currentAction, currentLevels);
								
								// Update goal state
								goalState.SetCondition(currentAction->GetPostcon(k));
								
								// check action doesn't already exists on level
								if(!count(actionsOnLevel.begin(), actionsOnLevel.end(), currentAction->name)){
									
									// add action name to list of those used on this level
									actionsOnLevel.push_back(currentAction->name);
									
									// add action to lists etc
									AddAction(currentAction, newNodes, tNode);
								}
								
								
							}
						} // for l
					} // for k
					
				} // for j
			}
		} // for i
		
		
		if(!newNodes.empty()){
			// insert current nodes for this tree level into map
			mapTreeLevels.insert(pair<int, vector<PlannerNode*> >(currentLevels,newNodes));
			currentLevels++;
			
		} else{
			// if no nodes are created the tree is finished/failed
			treeComplete = true;
		}
	} // end while
	  //	goalState.PrintValues();
	
	
	numLevels = currentLevels;
	
	// store goal for checking if later goals are different
	previousGoal = goal;
	
	
	PruneTree(actionsIn);
}

void ActionTree::PruneTree(const deque<TimedAction*>&  actionsIn){
	int numRuns = 1;
	int runsDone = 0;
	
	vector<PlannerNode*> startNodes = mapTreeLevels[mapTreeLevels.size()-1];
	
	vector<int> goodNodes;
	mapCond priorityConds;
	
	// get conditions required for top level
	for(int i = 0; i < mapTreeLevels[0].size(); i++){
		for(pairCond pC:mapTreeLevels[0][i]->action->preConditions){
			priorityConds.insert(pC);
		}
	}
	
	
	while(runsDone < numRuns){
		
		// do a pass whilst updating a stored state
		// at end of pass, check if goal conds met
		// if so add visited GetId()s to a list
		// if enough runs done:
		//		remove all unsuccessful nodes
		
		for(int sNode = 0; sNode < startNodes.size(); sNode++){
			vector<int> visitedNodes;
			
			WorldState checkState;
			PlannerNode* checkNode = startNodes[sNode];
			
			vector<int> linkToIds = checkNode->linkToIds;
			
			// while there are still nodes to traverse
			while(!linkToIds.empty()){
				// store visited node id
				visitedNodes.push_back(checkNode->GetId());
				
				// update world state for each
				checkNode->action->GetWorldStateEffect(checkState);
				
				// TODO - fix system for Nodes with multiple linkTo's
				// move up to next node
				//				for(int i = 0; i < linkToIds.size(); i++){
				checkNode = GetNode(linkToIds[0]);
				
				//				}
				
				// retrace back towards goal
				linkToIds = checkNode->linkToIds;
				
			}
			// store visited node id
			visitedNodes.push_back(checkNode->GetId());
			
			checkNode->action->GetWorldStateEffect(checkState);
			
			if(checkState.ContainsConditions(priorityConds)){
				goodNodes.insert(goodNodes.end(), visitedNodes.begin(), visitedNodes.end());
			}
			//			checkState.PrintValues();
			
		} // end for(sNode...
		
	 runsDone++;
		
	} // end while
	
	// remove all nodes that are of no use
	for(int i = 0; i < mapTreeLevels.size(); i++){
		for(int j = 0; j < mapTreeLevels[i].size(); j++){
			int nodeId = mapTreeLevels[i][j]->GetId();
			// check if GetId() isn't in good nodes list
			if(!count(goodNodes.begin(), goodNodes.end(), nodeId)){
				// remove if necessary
				mapTreeLevels[i].erase(find(mapTreeLevels[i].begin(), mapTreeLevels[i].end(), mapTreeLevels[i][j]));
			}
		}
	}
}

void ActionTree::LinkNodes(PlannerNode* fromNode, PlannerNode* toNode){
	fromNode->linkFromIds.push_back(toNode->GetId());
	toNode->linkToIds.push_back(fromNode->GetId());
}

void ActionTree::AddAction(TimedAction* action, vector<PlannerNode*>& newNodes, PlannerNode* tNode){
	// create node and add to vector of nodes on this level
	newNodes.push_back(new PlannerNode(action, currentId));
	// setup IDs for node links
	LinkNodes(tNode, newNodes.back());
	
	// increase assigned node id number
	currentId++;
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
/*
 TimedAction* ActionTree::GetActionForState(WorldState currentState){
	TimedAction* actionOut = NULL;
	
	if(!goalState.ConditionsMatch(currentState.GetConditionsMap())){
 pairCond refPair;
 int highestLevelMatch = -1, currentLevelMatch = -1;
 
 // finds the highest tree level that matches the supplied state
 // refPair is set to the matching condition pair
 
 FindLevelAndPair(refPair, highestLevelMatch, currentState);
 actionOut = GetBestAction(refPair, highestLevelMatch);
	}
	return actionOut;
 }
 */

TimedAction* ActionTree::GetAction(GridAgent& agent){
	TimedAction* actionOut = NULL;
	WorldState state = *agent.stateModule.GetCurrentState();
	
	if(!goalState.ConditionsMatch(state.GetConditionsMap())){
		pairCond refPair;
		int highestLevelMatch = -1, currentLevelMatch = -1;
		
		FindLevelAndPair(refPair, highestLevelMatch, state, agent);
		
		actionOut = GetBestAction(&agent, refPair, highestLevelMatch);
	}
	return actionOut;
}

// refPair is set to the matching condition pair
// finds the highest tree level that matches the supplied state

// get top level required pre-conditions
// find lowest point at which any of these aren't met in current state
// then find any action below this where its postconditions aren't currently met
// return this level/action (change function?)
void ActionTree:: FindLevelAndPair(pairCond& refPair_, int& level_, const WorldState& currentState, GridAgent& agent){

	mapCond priorityConds;
	
	int level = 0;
	
	level_ = level;
	refPair_ = mapTreeLevels[level_][0]->action->postConditions[0];
	
	if(mapTreeLevels.size() == 1){
		return;
	}
	
	// get conditions required for top level
	for(int i = 0; i < mapTreeLevels[0].size(); i++){
		for(pairCond pC:mapTreeLevels[0][i]->action->preConditions){
			priorityConds.insert(pC);
		}
	}
	
	for(int i = mapTreeLevels.size()-1; i > 0; i--){
		for(PlannerNode* node:mapTreeLevels[i]){
			for(pairCond pC : priorityConds){
				if(node->action->postConditions[0].first == pC.first){
					if(currentState.GetConditionValue(pC.first) != pC.second){
						level = i;
						goto stop; // sorry world
					}
				}
			}
		}
	}
	
stop: ;
//	printf("%s\n", mapTreeLevels[0][0]->action->name.c_str());
	for(int i = level-1; i < mapTreeLevels.size(); i++){
		for(PlannerNode* node:mapTreeLevels[i]){
			pairCond pC = node->action->postConditions[0];
			
			// if condition not met in world state
			if(currentState.GetConditionsMap().count(pC.first) &&
			   pC.second != currentState.GetConditionValue(pC.first)){
				level_ = i;
				refPair_ = pC;
			}
		}
	}
	
}

int ActionTree::GetVitalIndex(const WorldState& currentState){
	bool vitalFound = false;
	int levelOut = 0;
	if(!vitalTreeIndex.empty()){
		for(int i = numLevels-1; i >= 0; i--) {
			// for each node in this level
			for(PlannerNode* tNode : mapTreeLevels[i]){
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
TimedAction* ActionTree::GetBestAction(GridAgent* agent, pairCond& refPair_, int highestLevel){
	TimedAction* actionOut;
	int lowestCost = -1;
	
	if(mapTreeLevels[highestLevel].size() > 1){
		
		if(highestLevel != -1){
			for(PlannerNode* tNode : mapTreeLevels[highestLevel]){
				int num_precons = tNode->action->GetNumPrecons();
				int num_postcons = tNode->action->GetNumPostcons();
				
				// skip action if not valid
				if(!tNode->action->IsValid(agent)){
					continue;
				}
				
				if(tNode->isStartNode()){
					for(int i = 0; i < num_postcons; i++){
						if(refPair_ == tNode->action->GetPostcon(i)
						   && (tNode->action->cost < lowestCost || lowestCost == -1)){
							actionOut = tNode->action;
							lowestCost = tNode->action->cost;
						}
					}
				} else{
					for(int i = 0; i < num_precons; i++){
						if(refPair_ == tNode->action->GetPrecon(i)
						   && (tNode->action->cost < lowestCost || lowestCost == -1)){
							actionOut = tNode->action;
							lowestCost = tNode->action->cost;
						}
					}
				}
			}
		} // if highest_level != 1
		
	} else{
		actionOut = mapTreeLevels[highestLevel].at(0)->action;
	}
	return actionOut;
}


string ActionTree::ToString(){
	string treeOut = "";
	treeOut+="::START::\n";
	
	for(int i = 0; i < numLevels; i++) {
		treeOut += "LEVEL : " + ofToString(i);
		treeOut += "\n";
		
		//		treeOut +="Possible Actions:";
		//		treeOut += "\n";
		
		
		for(PlannerNode* tNode : mapTreeLevels[i]){
			treeOut += "\n";
			
			treeOut +=tNode->action->name;
			treeOut += "\n";
			
			treeOut +="Node ID: " + ofToString(tNode->GetId());
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
 ------------------------------------------------------------
 HOSPICE
 
 
 // should also check actions are still valid here - pass in state
 TimedAction* ActionTree::GetBestAction(pairCond& refPair_, int highestLevel){
	TimedAction* actionOut;
	int lowestCost = -1;
	
	if(mapTreeLevels[highestLevel].size() > 1){
 if(highestLevel != -1){
 for(PlannerNode* tNode : mapTreeLevels[highestLevel]){
 
 if(tNode->isStartNode()){
 
 if(refPair_ == tNode->action->GetPostcon(0)
 && (tNode->action->cost < lowestCost || lowestCost == -1)){
 actionOut = tNode->action;
 lowestCost = tNode->action->cost;
 }
 } else{
 if(refPair_ == tNode->action->GetPrecon(0)
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

 
 void ActionTree::BuildTree(const deque<TimedAction*>&  actionsIn, Goal goal){
	ResetTree(); // clear currently stored tree for rebuild
	
	int currentLevels = 0;
	int maxLevels = 10;
	bool treeComplete = false;
	
	if(goal.HasVitalCondition()){
 vitalConditions = goal.GetVitalConditions();
	}
	
	while(currentLevels < maxLevels && !treeComplete ){
 // stores created ActionPlannerNode(s)
 vector<PlannerNode*> newNodes;
 
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
 newNodes.push_back(new PlannerNode(currentAction, currentId));
 
 // increase assigned node id number
 currentId++;
 }
 }
 // if below top level...
 } else{
 vector<string> actionsOnLevel;
 deque<pairCond> condPriority;
 
 // for all nodes at current level...
 for(int j = 0; j < mapTreeLevels[currentLevels-1].size(); j++) {
 PlannerNode* tNode = mapTreeLevels[currentLevels-1].at(j);
 
 for(int k = 0; k < tNode->action->GetNumPrecons(); k++) {
 for(int l = 0; l < currentAction->GetNumPostcons(); l++) {
 
 if(currentAction->GetPostcon(l) == tNode->action->GetPrecon(k)){
 UpdateVitalInfo(currentAction, currentLevels);
 
 // Update goal state
 goalState.SetCondition(currentAction->GetPostcon(k));
 
 // check action doesn't already exists on level
 if(!count(actionsOnLevel.begin(), actionsOnLevel.end(), currentAction->name)){
 // create node and add to vector of nodes on this level
 newNodes.push_back(new PlannerNode(currentAction, currentId));
 // add action name to list of those used on this level
 actionsOnLevel.push_back(currentAction->name);
 }
 
 // setup IDs for node links
 tNode->linkFromIds.push_back(newNodes.back()->GetId());
 newNodes.back()->linkToIds.push_back(tNode->GetId());
 
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
 mapTreeLevels.insert(pair<int, vector<PlannerNode*> >(currentLevels,newNodes));
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
 
 // ----------------------------------------------------------------------
 void ActionTree:: FindLevelAndPair(pairCond& refPair_, int& level_, const WorldState& currentState, GridAgent& agent){
	
	int vitalLevel = 0;
	vector<PlannerNode*> startNodes = mapTreeLevels[mapTreeLevels.size()-1];
	
	vector<int> goodNodes;
	mapCond priorityConds;
	
	// get conditions required for top level
	for(int i = 0; i < mapTreeLevels[0].size(); i++){
 for(pairCond pC:mapTreeLevels[0][i]->action->preConditions){
 priorityConds.insert(pC);
 }
	}
	
	
	vitalLevel = GetVitalIndex(currentState);
	deque<pairCond> condOrder;
	//	cout<<"----------------"<<endl;
	//	cout<<"----------------"<<endl;
	//	cout<<"----------------"<<endl;
	//	goalState.PrintValues();
	//	cout<<"----------------"<<endl;
	
	//	currentState.PrintValues();
	
	// for each level starting at highest
	//	cout<<"----------------"<<endl;
	for(int i = numLevels-1; i >= vitalLevel; i--) {
 //	for(int i = vitalLevel; i < numLevels ; i++) {
 // for each node in this level
 for(PlannerNode* tNode : mapTreeLevels[i]){
 int num_precons = tNode->action->GetNumPrecons();
 int num_postcons = tNode->action->GetNumPostcons();
 int num_matches = 0;
 
 if(!(tNode->action->IsValid(&agent))){
 continue;
 }
 
 // for each goal and current condition pair
 for(pairCond goalPair : goalState.GetConditionsMap()){
 for(pairCond currentPair : currentState.GetConditionsMap()){
 
 // if current cond found in goal state
 if(goalPair.first == currentPair.first){
 //						for(int i = 0; i < num_precons; i++){
 //							condOrder.push_back(tNode->action->GetPrecon(i));
 //							printf("%s", condOrder[i].first.c_str());
 //						}
 
 // if we are at start of plan
 if(tNode->isStartNode()){
 if(tNode->action->GetPostcon(0) == goalPair){
 level_ = i;
 refPair_ = goalPair;
 }
 } else{
 
 //							if(num_precons <= 1){
 if(tNode->action->GetPrecon(0) == currentPair){
 //								printf("%s \n", tNode->action->name.c_str());
 
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
 }
 } // end: goalPair.first == currentPair.first
 
 }
 
 }
 
 } // end: tNode : mapTreeLevels[i]
	}
 }
 
 ------------------------------------------------------------
 GRAVEYARD
 
 void ActionTree::PrintTree(){
	//        cout<<mapTreeLevels.size()<<endl;
	cout<<endl<<"::START::"<<endl;
	
	for(int i = 0; i < numLevels; i++) {
 cout<<endl<<"LEVEL : "<<i<<endl;
 cout<<"Possible Actions: "<<endl;
 
 for(PlannerNode* tNode : mapTreeLevels[i]){
 //            cout<<endl<<tNode->action->name<<endl;
 cout<<"Node ID: "<<tNode->GetId()<<endl;
 
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
