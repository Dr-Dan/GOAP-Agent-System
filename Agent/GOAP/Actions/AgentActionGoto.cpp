//
//  AgentActionGoto.cpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 10/06/2016.
//
//

#include "AgentActionGoto.hpp"
#include "GridAgent.h"
#include "ResourceUtility.h"
#include <string>

// -----------------------------------------------------------------
// GotoAction

void ActionGoto::Execute(GridAgent* agent){
	
	//    agent->SetTarget(targetPos);
	ofVec2f targetPos = ofVec2f();
	if(gotoSpec == WorldTypes::NEAREST_CELL){
		if(agent->memoryModule.GetPosNearestCell(
												 targetPos,
												 agent->moveModule.GetGridPos(),
												 gotoType)){
			agent->navModule.SetTarget(targetPos);
		}
		
	} else if(gotoSpec == WorldTypes::NEAREST_RES){
		if(agent->memoryModule.GetPosNearestResource(
													 targetPos,
													 agent->moveModule.GetGridPos(),
													 gotoType)){
			agent->navModule.SetTarget(targetPos);
		}
		
	} else if(gotoSpec == WorldTypes::NEAREST_BUILD_LOC){
		if(agent->memoryModule.GetPosHighestRatingCell(targetPos,
													   gotoType)){
			agent->navModule.SetTarget(targetPos);
		}
	} else if(gotoSpec == WorldTypes::NEAREST_OWNED_LOC){
		// should be later changed
		if(agent->memoryModule.HasHome()){
			agent->navModule.SetTarget(agent->memoryModule.GetCellFact(agent->memoryModule.GetCurrentHomeCellId())->GetGridPos());
		}
	}
	
	if(agent->memoryModule.KnowsOfCellType(gotoType)){
		ofVec2f targetCell = agent->navModule.GetTargetDestination();
		agent->moveModule.HeadTowardsGridPos(targetCell);
	}
}

bool ActionGoto:: TaskComplete(GridAgent* agent){
	if(agent->navModule.AgentAtTarget(agent)){
		return true;
	}
	return false;
}

void ActionGoto::GetWorldStateEffect(WorldState& state){
	// set all other at X states to 0
	// set postcon in state
	for(pairCond p: state.GetConditionsMap()){
		string s = p.first;
		string sub = s.substr(0,5);
		if(sub == "Is At"){
			state.SetCondition(p.first, false);
		}
	}
	//	state.PrintValues();
	
	for(pairCond p: postConditions){
		state.SetCondition(p);
	}
}

// -----------------------------------------------------------------
// GotoActionStorage

void ActionGotoStorage::Execute(GridAgent* agent){
	
	if(!agent->memoryModule.KnowsOfCellType(CELL_STORAGE)){
		return;
	}
	
	if(gotoSpec == WorldTypes::NEAREST_CELL){
		ofVec2f targetPos = ofVec2f();
		if(agent->memoryModule.GetPosNearestCell(
												 targetPos,
												 agent->moveModule.GetGridPos(),
												 CELL_STORAGE)){
			agent->navModule.SetTarget(targetPos);
		}
	}
	else if(gotoSpec == WorldTypes::NEAREST_EMPTY){
		if(!agent->memoryModule.KnowsOfUnfilledStorage()){
			return;
		}
		vector<ofVec2f> cellPosList;
		if(agent->memoryModule.GetPosNearestCellList(
													 cellPosList,
													 agent->moveModule.GetGridPos(),
													 CELL_STORAGE)){
			
			for(int i = 0; i < cellPosList.size(); i++){
				if(!agent->memoryModule.GetCellFact(cellPosList[i])->IsFull()){
					agent->navModule.SetTarget(cellPosList[i]);
					break;
				}
			}
		}
	}
	
	ofVec2f targetCell = agent->navModule.GetTargetDestination();
	agent->moveModule.HeadTowardsGridPos(targetCell);
}

bool ActionGotoStorage:: TaskComplete(GridAgent* agent){
	if(agent->navModule.AgentAtTarget(agent)){
		return true;
	}
	return false;
}

bool ActionGotoStorage::IsValid(GridAgent* agent){
	if(agent->memoryModule.KnowsOfCellType(CELL_STORAGE)){
		return true;
	}
	return false;
}

void ActionGotoStorage::GetWorldStateEffect(WorldState& state){
	// set all other at X states to 0
	// set postcon in state
	
//	state.PrintValues();
	for(pairCond p: state.GetConditionsMap()){
		string s = p.first;
		string sub = s.substr(0,5);
		if(sub == "Is At"){
			state.SetCondition(p.first, false);
		}
	}
//	state.PrintValues();
	
	for(pairCond p: postConditions){
		state.SetCondition(p);
	}
}