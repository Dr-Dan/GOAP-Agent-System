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
	//	new ActionIdle("wait"),
	new ActionWander("wander"),
	new ActionWander("findfood"),
	new ActionWander("findwood"),
	new ActionWander("findhome"),
	new ActionWander("findhomelocation"),
	new ActionWander("findstoragefood"),
	
	new ActionGoto("gotofood", WorldTypes::CELL_FOOD, WorldTypes::NEAREST_CELL),
	new ActionGoto("gotowood", WorldTypes::CELL_WOOD, WorldTypes::NEAREST_CELL),
		 new ActionGoto("gotohomelocation", WorldTypes::CELL_NEUTRAL, WorldTypes::NEAREST_BUILD_LOC),
	new ActionGoto("gotoownedhome", WorldTypes::CELL_HOME, WorldTypes::NEAREST_OWNED_LOC),
	new ActionGotoStorage("gotostoragefood", WorldTypes::NEAREST_CELL),

	
	new ActionPickupResource("pickupfood", WorldTypes::CELL_FOOD),
	new ActionPickupResource("pickupwood", WorldTypes::CELL_WOOD),
	
	new ActionUseCarriedResource("eatfood", WorldTypes::CELL_FOOD),
	new ActionSleep("sleep"),

	new ActionDropResource("depositfood", WorldTypes::CELL_FOOD),

	new ActionBuildHome("placehome"),
	new ActionDestroyHome("destroyhome"),

	/*
	 new ActionWander("Find Wood", 2),

	 new ActionWander("Find Home Location", 2),
	 
	 new ActionWander("Find Storage Food", 2),
	 new ActionWander("Find Storage Wood", 2),
	 
	 // GOTO
	 new ActionGoto("Goto Food", 4, WorldTypes::CELL_FOOD, WorldTypes::NEAREST_CELL),
	 new ActionGoto("Goto Wood", 4, WorldTypes::CELL_WOOD, WorldTypes::NEAREST_CELL),
	 
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

TimedAction* ActionsModule::FindAction(string name){
	for(int i = 0; i < possibleActions.size(); ++i){
		if(possibleActions[i]->name == name){
			return possibleActions[i];
		}
	}
	return nullptr;
}

AIBase* ActionsModule:: GetPlanner(){
	return planner;
}
