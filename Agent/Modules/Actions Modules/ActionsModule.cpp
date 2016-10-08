//
//  ActionsModule.cpp
//  AgentGOAPActionsTestSimpler
//
//  Created by D J Clarke on 18/04/2015.
//
//

#include "ActionsModule.h"
#include "GridAgent.h"

deque<TimedAction*> ActionsModule::possibleActions = {
	new ActionIdle(pairCond("is waiting", 1)),
	new ActionWander(pairCond("found food", 1)),
	new ActionGoto(pairCond("at food", 1), WorldTypes::CELL_FOOD, WorldTypes::NEAREST_CELL),
	new ActionPickupResource(pairCond("has food", 1), WorldTypes::CELL_FOOD),
	new ActionUseCarriedResource(pairCond("used food", 1), WorldTypes::CELL_FOOD)

	/*
	new ActionWander("Find Wood", 2),
	
	new ActionWander("Find Home", 2),
	new ActionWander("Find Home Location", 2),
	
	new ActionWander("Find Storage Food", 2),
	new ActionWander("Find Storage Wood", 2),
	
	// GOTO
	new ActionGoto("Goto Food", 4, WorldTypes::CELL_FOOD, WorldTypes::NEAREST_CELL),
	new ActionGoto("Goto Wood", 4, WorldTypes::CELL_WOOD, WorldTypes::NEAREST_CELL),
	new ActionGoto("Goto Home", 4, WorldTypes::CELL_HOME, WorldTypes::NEAREST_OWNED_LOC),
	new ActionGotoStorage("Goto Storage Food", 4,  WorldTypes::NEAREST_CELL),
	new ActionGotoStorage("Goto Storage Wood", 4,  WorldTypes::NEAREST_CELL),
	new ActionGoto("Goto Home Location", 4, WorldTypes::CELL_NEUTRAL, WorldTypes::NEAREST_BUILD_LOC),
	new ActionGoto("Goto Owned Home", 4, WorldTypes::CELL_HOME, WorldTypes::NEAREST_OWNED_LOC),
	
	// PICKUP
	new ActionPickupResource("Pickup Food", 4, WorldTypes::CELL_FOOD),
	new ActionPickupResource("Pickup Wood", 4, WorldTypes::CELL_WOOD),
	
	// DEPOSIT
	new ActionDropResource("Deposit Food", 4, WorldTypes::CELL_FOOD),
	new ActionDropResource("Deposit Wood", 4, WorldTypes::CELL_WOOD),
	
	// CONSTRUCT
	new ActionBuildHome("Place Home", 4),
	new ActionDestroyHome("Destroy Home", 4),
	
	// CONSUME
	new ActionSleep("Sleep", 4),
	new ActionUseCarriedResource("Eat", 4, WorldTypes::CELL_FOOD)
	 */
};

ActionsModule::~ActionsModule(){
	Utility::ClearContainerPointers(possibleActions);
	if(planner){
		delete planner;
	}
}

ActionsModule::ActionsModule(){
	// ACTIONS
	// exploration
	// for each in WanderActions:

	
	// ---------------------------------------
	
	planner = new GOAPPlanner();
	
	currentAction = NULL;
}

void ActionsModule::Update(GridAgent& agent){
	planner->Update(agent);
}


TimedAction* ActionsModule::GetNextAction(GridAgent& agent){
	//	BuildTree(agent);
	
	TimedAction* nextAction = NULL;
	//	nextAction = actionTree->GetActionForState(*agent.stateModule.GetCurrentState());
	nextAction = planner->GetNextAction(agent);
	
	return nextAction;
}

void ActionsModule::DoNextAction(GridAgent& agent){
	TimedAction* nextAction = GetNextAction(agent);
	if(nextAction && nextAction->IsValid(&agent)){
		currentAction = nextAction;
		currentAction->Execute(&agent);
	}
}

TimedAction* ActionsModule::GetCurrentAction(){
	if(currentAction){
		return currentAction;
	}
	return NULL;
}

AIBase* ActionsModule:: GetPlanner(){
	return planner;
}
