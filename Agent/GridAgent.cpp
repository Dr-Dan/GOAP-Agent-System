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
    sensorModule.UpdateCellMemory(memoryModule); // take current cell parameter?
    sensorModule.UpdateAgentMemory(memoryModule); // take current cell parameter?
    
    stateModule.UpdateState(this);
    motiveModule.UpdateGoal(this);
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

void GridAgent::SetNearbyCells(vector<GridCell*> cellsNear){
    sensorModule.UpdateCellView(cellsNear);
}

void GridAgent::SetNearbyAgents(vector<GridAgent*> agentsNear){
    sensorModule.UpdateAgentView(agentsNear);
}

void GridAgent::SetCurrentCell(GridCell* currentCellIn){
    sensorModule.SetCurrentCell(currentCellIn);
}