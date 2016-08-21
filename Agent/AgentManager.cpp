//
//  AgentManager.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 17/04/2015.
//
//

#include "AgentManager.h"
#include "Grid.h"

AgentManager::~AgentManager(){
	Utility::ClearContainerPointers(agents);
}

AgentManager::AgentManager():
gridDims(ofVec2f(GridValues::GRID_DIMS[0], GridValues::GRID_DIMS[1])),
agentSize(GridValues::CELL_SIZE-2)
{}

AgentManager::AgentManager(ofVec2f gridDims_):
gridDims(gridDims_),
agentSize(GridValues::CELL_SIZE-2)
{}

AgentManager::AgentManager(ofVec2f gridDims_, int agentSize_):
gridDims(gridDims_),
agentSize(agentSize_)
{}

void AgentManager::UpdateAgents(){
	for(GridAgent* agent: agents){
		agent->Update();
	}
}

void AgentManager::UpdateStepTime(){
	for(GridAgent* agent: agents){
		agent->ManageAttributes();
		agent->DoCurrentAction();
		agent->Move();
	}
}

void AgentManager::UpdateAgentsGridView(Grid& gridIn){
	for(GridAgent* agent: agents){
		agent->ScanCells(gridIn.GetSurroundingCells(agent->moveModule.GetGridPos(), GridValues::AGENT_VIEW_RADIUS));
		agent->ScanAgents(GetNearbyAgents(agent->moveModule.GetGridPos(), GridValues::AGENT_VIEW_RADIUS));
		
		agent->SetCurrentCell(gridIn.GetCell(agent->moveModule.GetGridPos()));
	}
}

GridAgent* AgentManager::GetAgent(int agentNo){
	if(GetNumAgents() > 0){
		return agents[agentNo];
	}
	return NULL;
}

vector<GridAgent*> AgentManager::GetNearbyAgents(const ofVec2f& callerPos, int distance){
	vector<GridAgent*> nearbyAgents;
	for(GridAgent* a: agents){
		if(Utility::GetGridDistance(callerPos, a->moveModule.GetGridPos()) <= distance){
			nearbyAgents.push_back(a);
		}
	}
	return nearbyAgents;
}

void AgentManager::AddAgent(ofVec2f pos_){
	agents.push_back(new GridAgent(pos_));
	GridAgent* latestAgent = agents.back();
	
	//    latestAgent->agentId = agents.size();
	latestAgent->agentSize = agentSize;
}

void AgentManager::AddAgentsRandomPos(int numAgents){
	for(int i = 0; i < numAgents; i++){
		ofVec2f randPos = ofVec2f((int)ofRandom(gridDims.x),(int)ofRandom(gridDims.x));
		AddAgent(randPos);
	}
}

int AgentManager::GetNumAgents(){
	return agents.size();
}

void AgentManager::DisplayAgents(){
	for(GridAgent* a: agents) {
		DisplayVisitor::Render(*a);
	}
}
