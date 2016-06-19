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
	// for each in WanderActions:
	possibleActions.push_back(new ActionWander("Wander", 2));
	
	possibleActions.push_back(new ActionWander("Find Food", 2));
	possibleActions.push_back(new ActionWander("Find Wood", 2));
	
	possibleActions.push_back(new ActionWander("Find Home", 2));
	possibleActions.push_back(new ActionWander("Find Home Location", 2));
	
	possibleActions.push_back(new ActionWander("Find Storage Food", 2));
	possibleActions.push_back(new ActionWander("Find Storage Wood", 2));
	
	// GOTO
	possibleActions.push_back(new ActionGoto("Goto Food", 4, WorldTypes::CELL_FOOD, WorldTypes::NEAREST_CELL));
	possibleActions.push_back(new ActionGoto("Goto Wood", 4, WorldTypes::CELL_WOOD, WorldTypes::NEAREST_CELL));
	possibleActions.push_back(new ActionGoto("Goto Home", 4, WorldTypes::CELL_HOME, WorldTypes::NEAREST_OWNED_LOC));
	possibleActions.push_back(new ActionGotoStorage("Goto Storage Food", 4,  WorldTypes::NEAREST_CELL));
	possibleActions.push_back(new ActionGotoStorage("Goto Storage Wood", 4,  WorldTypes::NEAREST_CELL));
	possibleActions.push_back(new ActionGoto("Goto Home Location", 4, WorldTypes::CELL_NEUTRAL, WorldTypes::NEAREST_BUILD_LOC)); // not right
	possibleActions.push_back(new ActionGoto("Goto Owned Home", 4, WorldTypes::CELL_HOME, WorldTypes::NEAREST_OWNED_LOC)); // not right
	
	// PICKUP
	possibleActions.push_back(new ActionPickupResource("Pickup Food", 4, WorldTypes::CELL_FOOD));
	possibleActions.push_back(new ActionPickupResource("Pickup Wood", 4, WorldTypes::CELL_WOOD));
	
	// DEPOSIT
	possibleActions.push_back(new ActionDropResource("Deposit Food", 4, WorldTypes::CELL_FOOD));
	possibleActions.push_back(new ActionDropResource("Deposit Wood", 4, WorldTypes::CELL_WOOD));
	
	// CONSTRUCT
	possibleActions.push_back(new ActionBuildHome("Place Home", 4));
	possibleActions.push_back(new ActionDestroyHome("Destroy Home", 4));
	
	// CONSUME
	possibleActions.push_back(new ActionSleep("Sleep", 4));
	possibleActions.push_back(new ActionUseCarriedResource("Eat", 4, WorldTypes::CELL_FOOD));
	

	
	// ---------------------------------------
	
	actionTree = new ActionTree();
	
	currentAction = NULL;
	//        actionTree->PrintTree();
}

void ActionsModule::Update(GridAgent& agent){
	actionTree->Update(agent);
}


Action* ActionsModule::GetNextAction(GridAgent& agent){
	//	BuildTree(agent);
	
	Action* nextAction = NULL;
	//	nextAction = actionTree->GetActionForState(*agent.stateModule.GetCurrentState());
	nextAction = actionTree->GetAction(agent);
	
	return nextAction;
}

void ActionsModule::DoNextAction(GridAgent& agent){
	Action* nextAction = GetNextAction(agent);
	if(nextAction && nextAction->IsValid(&agent)){
		currentAction = nextAction;
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
