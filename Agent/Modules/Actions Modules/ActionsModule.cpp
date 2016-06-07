//
//  ActionsModule.cpp
//  AgentGOAPActionsTestSimpler
//
//  Created by D J Clarke on 18/04/2015.
//
//

#include "ActionsModule.h"
#include "GridAgent.h"
ActionsModule::~ActionsModule(){
	Utility::ClearContainerPointers(possibleActions);
	if(actionTree){
		delete actionTree;
	}
}

ActionsModule::ActionsModule(){
	// ACTIONS
	// exploration
	possibleActions.push_back(new ActionWander("Wander", 2));
	
	possibleActions.push_back(new ActionWander("Find Food", 2));
	
	possibleActions.push_back(new ActionWander("Find Wood", 2));
	
	possibleActions.push_back(new ActionWander("Find Home", 2));
	possibleActions.push_back(new ActionWander("Find Home Location", 2));
	
	possibleActions.push_back(new ActionWander("Find Storage Food", 2));
	possibleActions.push_back(new ActionWander("Find Storage Wood", 2));
	
	// FOOD
	possibleActions.push_back(new ActionGoto("Goto Food", 4, WorldTypes::CELL_FOOD, WorldTypes::NEAREST_CELL));
	possibleActions.push_back(new ActionPickupResource("Pickup Food", 4, WorldTypes::CELL_FOOD));
	possibleActions.push_back(new ActionUseCarriedResource("Eat", 4, WorldTypes::CELL_FOOD));
	
	// WOOD
	possibleActions.push_back(new ActionGoto("Goto Wood", 4, WorldTypes::CELL_WOOD, WorldTypes::NEAREST_CELL));
	possibleActions.push_back(new ActionPickupResource("Pickup Wood", 4, WorldTypes::CELL_WOOD));
	
	// STORAGE
	possibleActions.push_back(new ActionGoto("Goto Storage Food", 4, WorldTypes::CELL_STORAGE, WorldTypes::NEAREST_CELL));
possibleActions.push_back(new ActionGoto("Goto Storage Wood", 4, WorldTypes::CELL_STORAGE, WorldTypes::NEAREST_CELL));
	
	possibleActions.push_back(new ActionDropResource("Deposit Food", 4, WorldTypes::CELL_FOOD));
	
	// HOME PLACEMENT
	// this is bad, needs to be less specific. These two should be the same action!!!
	possibleActions.push_back(new ActionGoto("Goto Home Location", 4, WorldTypes::CELL_NEUTRAL, WorldTypes::NEAREST_BUILD_LOC)); // not right
	possibleActions.push_back(new ActionGoto("Goto Owned Home", 4, WorldTypes::CELL_HOME, WorldTypes::NEAREST_OWNED_LOC)); // not right

	possibleActions.push_back(new ActionChangeCell("Place Home", 4, WorldTypes::CELL_HOME));
	possibleActions.push_back(new ActionChangeCell("Destroy Home", 4, WorldTypes::CELL_NEUTRAL));

	
	// SLEEP
	possibleActions.push_back(new ActionUseCell("Sleep", 4, WorldTypes::CELL_HOME));
	possibleActions.push_back(new ActionGoto("Goto Home", 4, WorldTypes::CELL_HOME, WorldTypes::NEAREST_OWNED_LOC));
	
	// ---------------------------------------
	
	actionTree = new ActionTree();
	
	currentAction = NULL;
	//        actionTree->PrintTree();
}


void ActionsModule::BuildTree(GridAgent& agent){
	//        cout<<GetTopGoal().satisfactionCond.first<<endl;
	//                currentState.PrintValues();
	//                actionTree->PrintGoalState();
	//                actionTree->PrintTree();
	Goal topGoal = agent.motiveModule.GetTopGoal();
	if(actionTree->GoalIsChanged(topGoal))
		actionTree->BuildTree(possibleActions, topGoal);
}

Action* ActionsModule::GetNextAction(GridAgent& agent){
	BuildTree(agent);
	
	Action* nextAction = NULL;
	nextAction = actionTree->GetActionForState(*agent.stateModule.GetCurrentState());
	
	return nextAction;
}

void ActionsModule::DoNextAction(GridAgent& agent){
	currentAction = GetNextAction(agent);
	if(currentAction){
		currentAction->Execute(&agent);
	}
}

Action* ActionsModule::GetCurrentAction(){
	if(currentAction){
		return currentAction;
	}
	return NULL;
}


ActionTree* ActionsModule:: GetTree(){
	return actionTree;
}
