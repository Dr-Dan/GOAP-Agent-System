//
//  GridAgent.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 24/02/2015.
//
//

#include "GridAgent.h"

GridAgent::GridAgent(ofVec2f startCell):
Entity(),
attributes(),
memoryModule(),
navModule(),
sensorModule(),
actionsModule(new ActionsModule()),
moveModule(startCell,1)
{
//    gridPos = startCell;
//    this->gridSize = gridSize;
//    attributes = AgentAttributes();
//    
//    memoryModule = MemoryModule();
//    navModule = NavigationModule();
//    sensorModule = SensorModule();
//    actionsModule = new ActionsModule();
//    moveModule = MovementModule(startCell,1);
}

void GridAgent::Update(){
    stateModule.UpdateState(this);
    motiveModule.UpdateGoal(this);
	actionsModule->Update(*this);
}

void GridAgent::ManageAttributes(){
    attributes.UpdateNeeds();
}

void GridAgent::DoCurrentAction(){
	actionsModule->DoNextAction(*this);
}

void GridAgent::Move(){
    moveModule.DoMovement();
}

void GridAgent::ScanCells(const vector<GridCell*>& cellsNear){
	sensorModule.UpdateCellMemory(memoryModule, cellsNear); // take current cell parameter?

//    sensorModule.UpdateCellView(cellsNear);
}

void GridAgent::ScanAgents(const vector<GridAgent*>& agentsNear){
	sensorModule.UpdateAgentMemory(memoryModule, agentsNear); // take current cell parameter?
	//    sensorModule.UpdateAgentView(agentsNear);
}

void GridAgent::SetCurrentCell(GridCell* currentCellIn){
    sensorModule.SetCurrentCell(currentCellIn);
}