//
//  StateModule.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 30/06/2015.
//
//

#include "StateModule.h"
#include "GridAgent.h"

void StateModule::SetCurrentState(WorldState stateIn){
	currentState = stateIn;
}

WorldState* StateModule::GetCurrentState(){
	return &currentState;
}

void StateModule::UpdateState(GridAgent* agent){
	currentState.SetCondition("Is Exploring", (!agent->attributes.NeedIsUrgent(CELL_FOOD) &&
											   !agent->attributes.NeedIsUrgent(CELL_HOME)));
	
	//    currentState.SetCondition("Is Hungry", agent->attributes.IsHungry()); // has no use?
	//    currentState.SetCondition("Food Found", agent->memoryModule.KnowsOfCellType(CELL_FOOD));
	currentState.SetCondition("Food Found", agent->memoryModule.KnowsOfResourceType(CELL_FOOD));
	
	//    currentState.SetCondition("Is At Food", agent->sensorModule.AtCell(CELL_FOOD) ||
	//							  (agent->sensorModule.AtCell(CELL_STORAGE) && agent->sensorModule.AtCellWithResource(CELL_FOOD)));
	currentState.SetCondition("Is At Food", agent->sensorModule.AtCell(CELL_FOOD));
	
	currentState.SetCondition("Is Full", agent->attributes.NeedIsSatisfied(CELL_FOOD));
	
	//    currentState.SetCondition("Is Tired", agent->attributes.IsTired());
	currentState.SetCondition("Home Found", agent->memoryModule.HasHome());
	currentState.SetCondition("Is At Home", agent->sensorModule.AtCell(CELL_HOME) /* && agent->memoryModule.HasHome()
																				   && agent->memoryModule.GetCellFact(agent->sensorModule.GetCurrentCell()->GetId()).IsCellHome()*/);
	
	currentState.SetCondition("Is Rested", agent->attributes.NeedIsSatisfied(CELL_HOME));
	
	currentState.SetCondition("Storage Found", agent->memoryModule.KnowsOfCellType(CELL_STORAGE));
	currentState.SetCondition("Carrying Food", (agent->attributes.HasResource(CELL_FOOD) /*&&
																						  agent->attributes.CanPickupResource(CELL_FOOD, agent->attributes.GetResourcePickupAmt(CELL_FOOD))*/));
	currentState.SetCondition("Is At Storage", agent->sensorModule.AtCell(CELL_STORAGE));
	
	// where to put sort function
	currentState.SetCondition("Home Location Found", agent->memoryModule.KnowsOfHomeLocation());
	
	// this is super convoluted
	ofVec2f topHomeLocation = ofVec2f();
	GridCell* currentCell = agent->sensorModule.GetCurrentCell();
	
	agent->memoryModule.GetPosHighestRatingCell(topHomeLocation, CELL_NEUTRAL);
	
	// shouldn't need to do this
	if(currentCell) {
	//	cout<<ofToString(homeLocation)<<endl;
	currentState.SetCondition("At Home Location", currentCell->GetGridPos() == topHomeLocation);
	currentState.SetCondition("At Owned Home", currentCell->GetId() == agent->memoryModule.GetCurrentHomeCellId() && agent->memoryModule.HasHome());
	}
	
	
	//	currentState.SetCondition("Has Home", agent->attributes.hasHome);
	
	// need some kind of message from agent that this is happening?
	//	currentState.SetCondition("Increase Food Stock", agent->sensorModule.AtCell(CELL_STORAGE) && agent->attributes.HasResource(CELL_FOOD));
	
}
