//
//  GOAPPlanner.cpp
//  AgentGOAPActionsTestSimpler
//
//  Created by D J Clarke on 22/04/2015.
//
//

#include "GOAPPlanner.h"
#include "GridAgent.h"

GOAPPlanner::~GOAPPlanner(){
	//        Utility::ClearContainerPointers(nodes);
	ClearMapLevels();
}

PlannerNode* GOAPPlanner::GetNode(int nodeId){
	for(pair<int, vector<PlannerNode*> > tNV : mapTreeLevels){
		for(int i = 0; i < tNV.second.size(); i++){
			if (tNV.second[i]->GetId() == nodeId) {
				return tNV.second[i];
			}
		}
	}
	return NULL;
}

void GOAPPlanner::Update(GridAgent& agent){
	Goal topGoal = agent.motiveModule.GetTopGoal();
	if(GoalIsChanged(topGoal)){
		BuildTree(agent.actionsModule->getPossibleActions(), topGoal);
	}
}

void GOAPPlanner::ClearMapLevels(){
	for(pair<int, vector<PlannerNode*> > tNV : mapTreeLevels){
		Utility::ClearContainerPointers(tNV.second);
	}
	
	mapTreeLevels.clear();
	numLevels = 0;
}

void GOAPPlanner::ResetTree(){
	ClearMapLevels();
	goalState = WorldState();
	currentId = 0;
	firstValidLevel = 0;
	
}

GOAPPlanner::GOAPPlanner(){}


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
void GOAPPlanner::BuildTree(const deque<TimedAction*>&  actionsIn, Goal goal){
	ResetTree(); // clear currently stored tree for rebuild
	
	int currentLevels = 0;
	int maxLevels = 10;
	bool treeComplete = false;

	while(currentLevels < maxLevels && !treeComplete ){
		// stores created ActionPlannerNode(s)
		vector<PlannerNode*> newNodes;
		vector<WorldState> refStates;
		
		// for all actions
		for(int i = 0; i < actionsIn.size(); i++) {
			TimedAction* currentAction = actionsIn[i];
			
			// firstly get goal (Level 0) relative actions
			if(currentLevels == 0){
				FindGoalLevelActions(currentId, goal, currentAction, newNodes, refStates);
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
							highestAc = GetHighestAction(checkNode, actionsIn, checkState);
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
					} else {
					// ----------------------------------------------------------
					// else if action has preconditions
						AddActionWithPreconds(tNode, currentAction, actionsOnLevel,newNodes);
					
				} // for j
			}
		} // for i
		}
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

TimedAction* GOAPPlanner::GetHighestAction(PlannerNode* checkNode, const deque<TimedAction*>&  actionsIn, WorldState& checkState){
	int numPrecons = checkNode->action->GetNumPrecons();
	TimedAction* highestAc = NULL;

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
	return highestAc;
}

void GOAPPlanner::AddActionWithPreconds(PlannerNode* tNode, TimedAction* currentAction, vector<string>& actionsOnLevel, vector<PlannerNode*>& newNodes){
	for(int k = 0; k < tNode->action->GetNumPrecons(); k++) {
		for(int l = 0; l < currentAction->GetNumPostcons(); l++) {
			
			if(currentAction->GetPostcon(l) == tNode->action->GetPrecon(k)){
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
}

void GOAPPlanner::FindGoalLevelActions(int& currentId, const Goal& goal, TimedAction* currentAction, vector<PlannerNode*>& newNodes, vector<WorldState>& refStates){
	for(int j = 0; j < currentAction->GetNumPostcons(); j++) {
		
		// does action postcondition match goal condition
		if(currentAction->GetPostcon(j) == goal.GetCondition(0)){
			
			//						UpdateVitalInfo(currentAction, currentLevels);
			
			// Update goal state
			goalState.SetCondition(goal.GetCondition(0));
			refStates.push_back(goalState);
			
			newNodes.push_back(new PlannerNode(currentAction, currentId));
			
			// increase assigned node id number
			currentId++;
		}
	}
}

//bool GOAPPlanner::GetHighestSolvingAction(pairCond precon, int i, const TimedAction& action){
////	pairCond p = checkNode->action->GetPrecon(i);
//	
//	for(int j = 0; j < actionsIn.size(); j++){
//		if(precon == action.GetPostcon(0) &&
//		   !checkState.SharesCondition(action.GetPostcon(0))){
//			return true;
//		}
//	}
//	return false;
//}

// get conditions required for top level actions
// do a pass whilst updating a stored state
// at end of pass, check if goal conds met
// if so:
//		add visited GetId()s to a list
// if enough runs done:
//		remove all unsuccessful nodes

void GOAPPlanner::PruneTree(const deque<TimedAction*>&  actionsIn){
	vector<PlannerNode*> startNodes = mapTreeLevels[mapTreeLevels.size()-1];
	
	vector<int> goodNodes;
	mapCond priorityConds;
	
	// get conditions required for top level actions
	for(int i = 0; i < mapTreeLevels[0].size(); i++){
		for(pairCond pC:mapTreeLevels[0][i]->action->preConditions){
			priorityConds.insert(pC);
		}
	}
	
	int numRuns = 1;
	FindGoodNodes(numRuns, goodNodes, startNodes, priorityConds);
	RemoveDeadNodes(goodNodes);
}

void GOAPPlanner::FindGoodNodes(int numRuns, vector<int>& goodNodes, const vector<PlannerNode*>& startNodes, const mapCond& priorityConds){
	int runsDone = 0;
	while(runsDone < numRuns){
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
	
}

void GOAPPlanner::RemoveDeadNodes(const vector<int>& goodNodes){
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

void GOAPPlanner::LinkNodes(PlannerNode* fromNode, PlannerNode* toNode){
	fromNode->linkFromIds.push_back(toNode->GetId());
	toNode->linkToIds.push_back(fromNode->GetId());
}

void GOAPPlanner::AddAction(TimedAction* action, vector<PlannerNode*>& newNodes, PlannerNode* tNode){
	// create node and add to vector of nodes on this level
	newNodes.push_back(new PlannerNode(action, currentId));
	// setup IDs for node links
	LinkNodes(tNode, newNodes.back());
	
	// increase assigned node id number
	currentId++;
}

bool GOAPPlanner::GoalIsChanged(Goal goalIn){
	if(goalIn.GetName() != previousGoal.GetName()){
		return true;
	}
	return false;
}


void GOAPPlanner::PrintGoalState(){
	cout<<endl<<"goalState:"<<endl;
	goalState.PrintValues();
	
}

TimedAction* GOAPPlanner::GetNextAction(GridAgent& agent){
	TimedAction* actionOut = NULL;
	WorldState state = *agent.stateModule.GetCurrentState();
	
	if(!goalState.ConditionsMatch(state.GetConditionsMap())){
		pairCond refPair;
		int highestLevelMatch = -1, currentLevelMatch = -1;
		
		FindLevelAndPair(refPair, highestLevelMatch, state);
		
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
void GOAPPlanner:: FindLevelAndPair(pairCond& refPair_, int& level_, const WorldState& currentState){
	
	mapCond priorityConds;
	
	level_ = 0;
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
	
	int levelPriority = 0;
	levelPriority = CalculateLevelPriority(priorityConds, currentState);
	
	if(levelPriority == -1){
		//		printf("NO LEVEL FOUND\n");
		return;
	}
	
	FindLevelAndPairFinal(levelPriority, level_, refPair_, currentState);
	
}

int GOAPPlanner::CalculateLevelPriority(const mapCond& priorityConds, const WorldState& currentState){
	for(int i = mapTreeLevels.size()-1; i > 0; i--){
		for(PlannerNode* node:mapTreeLevels[i]){
			for(pairCond pC : priorityConds){
				if(node->action->postConditions[0].first == pC.first &&
				   currentState.GetConditionValue(pC.first) != pC.second){
					return i;
				}
			}
		}
	}
	return -1;
}

void GOAPPlanner::FindLevelAndPairFinal(int startLevel, int& level_, pairCond& refPair_, const WorldState& currentState){
	for(int i = startLevel-1; i < mapTreeLevels.size(); i++){
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

// should also check actions are still valid here - pass in state
TimedAction* GOAPPlanner::GetBestAction(GridAgent* agent, pairCond& refPair_, int highestLevel){
	TimedAction* actionOut = nullptr;
	
	if(highestLevel != -1){
		if(mapTreeLevels[highestLevel].size() > 1){
			int lowestCost = -1;
			
			for(PlannerNode* tNode : mapTreeLevels[highestLevel]){
				// skip action if not valid
				if(!tNode->action->IsValid(agent)){
					continue;
				}
				
				if(tNode->isStartNode()){
					FindLowestCostActionForConds(*tNode, refPair_, PostconStrategy(), *actionOut);
				} else{
					FindLowestCostActionForConds(*tNode, refPair_, PreconStrategy(), *actionOut);
				}
			}
		} else{
			actionOut = mapTreeLevels[highestLevel].at(0)->action;
		}
	} // if highest_level != 1
	
	return actionOut;
}

void GOAPPlanner::FindLowestCostActionForConds(const PlannerNode& tNode, pairCond refPair, ConditionStrategy strat, TimedAction& actionOut){
	int lowestCost = 0;
	pairCond condition;
	
	for(int i = 0; i < strat.GetNumConditions(tNode); i++){
		if(refPair == strat.GetCondition(tNode, i)){
			FindLowestCostAction(*tNode.action, lowestCost, actionOut);
		}
	}
}

void GOAPPlanner::FindLowestCostAction(const TimedAction& action, int& lowestCostOut, TimedAction& actionOut){
	if(action.cost < lowestCostOut || lowestCostOut == -1){
		actionOut = action;
		lowestCostOut = action.cost;
	}
}

string GOAPPlanner::ToString(){
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
