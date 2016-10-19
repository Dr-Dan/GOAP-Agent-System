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
//	currentState.SetCondition("Is Exploring", (!agent->attributes.NeedIsUrgent(CELL_FOOD) && !agent->attributes.NeedIsUrgent(CELL_HOME)));
	
		currentState.SetCondition("ishungry", agent->attributes.NeedIsUrgent(CELL_FOOD)); // has no use?
//	currentState.SetCondition("isexploring", true); // has no use?
	
	currentState.SetCondition("isfull", agent->attributes.NeedIsSatisfied(CELL_FOOD)); // has no use?
	
	currentState.SetCondition("foundfood", agent->memoryModule.KnowsOfResourceType(CELL_FOOD));
		currentState.SetCondition("foundwood", agent->memoryModule.KnowsOfResourceType(CELL_WOOD));
	currentState.SetCondition("foundhomelocation", agent->memoryModule.KnowsOfHomeLocation());
	
	currentState.SetCondition("atfood", agent->sensorModule.AtCell(CELL_FOOD));
	currentState.SetCondition("atwood", agent->sensorModule.AtCell(CELL_WOOD));
	
	currentState.SetCondition("hasfood", agent->attributes.HasResource(CELL_FOOD));
	currentState.SetCondition("haswood", agent->attributes.HasResource(CELL_WOOD));

	currentState.SetCondition("istired", agent->attributes.NeedIsUrgent(CELL_HOME));

	//
	//	currentState.SetCondition("Home Found", agent->memoryModule.HasHome());
		currentState.SetCondition("athome", agent->sensorModule.AtCell(CELL_HOME) /* && agent->memoryModule.HasHome()
																					   && agent->memoryModule.GetCellFact(agent->sensorModule.GetCurrentCell()->GetId()).IsCellHome()*/);
	
		currentState.SetCondition("isrested", agent->attributes.NeedIsSatisfied(CELL_HOME));
	
	
		// this is super convoluted
		ofVec2f topHomeLocation = ofVec2f();
		GridCell* currentCell = agent->sensorModule.GetCurrentCell();
	
		agent->memoryModule.GetPosHighestRatingCell(topHomeLocation, CELL_NEUTRAL);
	
		// shouldn't need to do this
		if(currentCell) {
		//	cout<<ofToString(homeLocation)<<endl;
		currentState.SetCondition("athomelocation", currentCell->GetGridPos() == topHomeLocation);
		currentState.SetCondition("atownedhome", currentCell->GetId() == agent->memoryModule.GetCurrentHomeCellId() && agent->memoryModule.HasHome());
		}
	
		currentState.SetCondition("homeplaced", agent->memoryModule.HasHome());
	
	// ------------------------------------------------------------------------------------------
	
	//	currentState.SetCondition("Has Home", agent->attributes.hasHome);
	
	//
	//	currentState.SetCondition("Storage Found Food", agent->memoryModule.KnowsOfCellType(CELL_STORAGE));
	//	currentState.SetCondition("Storage Found Wood", agent->memoryModule.KnowsOfCellType(CELL_STORAGE));
	//
	//	currentState.SetCondition("Carrying Food", (agent->attributes.HasResource(CELL_FOOD) /*&&
	//																						  agent->attributes.CanPickupResource(CELL_FOOD, agent->attributes.GetResourcePickupAmt(CELL_FOOD))*/));
	//
	//	currentState.SetCondition("Carrying Wood", (agent->attributes.HasResource(CELL_WOOD)));
	//
	//	currentState.SetCondition("Is At Storage Food", agent->sensorModule.AtCell(CELL_STORAGE));
	//	currentState.SetCondition("Is At Storage Wood", agent->sensorModule.AtCell(CELL_STORAGE));
	//
	//	// where to put sort function
	//	currentState.SetCondition("Home Location Found", agent->memoryModule.KnowsOfHomeLocation());
	//
	//	// this is super convoluted
	//	ofVec2f topHomeLocation = ofVec2f();
	//	GridCell* currentCell = agent->sensorModule.GetCurrentCell();
	//
	//	agent->memoryModule.GetPosHighestRatingCell(topHomeLocation, CELL_NEUTRAL);
	//
	//	// shouldn't need to do this
	//	if(currentCell) {
	//	//	cout<<ofToString(homeLocation)<<endl;
	//	currentState.SetCondition("Is At Home Location", currentCell->GetGridPos() == topHomeLocation);
	//	currentState.SetCondition("At Owned Home", currentCell->GetId() == agent->memoryModule.GetCurrentHomeCellId() && agent->memoryModule.HasHome());
	//	}
	//
	//	currentState.SetCondition("Home Placed", agent->memoryModule.HasHome());
	
	
	
	//	currentState.SetCondition("Has Home", agent->attributes.hasHome);
	
	// need some kind of message from agent that this is happening?
	//	currentState.SetCondition("Increase Food Stock", agent->sensorModule.AtCell(CELL_STORAGE) && agent->attributes.HasResource(CELL_FOOD));
	
}
