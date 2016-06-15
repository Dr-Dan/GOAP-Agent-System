//
//  AgentActionResource.cpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 10/06/2016.
//
//

#include "AgentActionResource.hpp"
#include "GridAgent.h"
#include "ResourceUtility.h"


// -----------------------------------------------------------------
// ActionPickupResource

void ActionPickupResource::Execute(GridAgent* agent){
	agent->moveModule.StopMovement();
	
	int pickupAmt = agent->attributes.GetResourcePickupAmt(resType);
	GridCell* currentCell = agent->sensorModule.GetCurrentCell(); // get agent's cell
	
	//	    if(currentCell->HasResources(resType, pickupAmt)){
	agent->attributes.PickupResource(resType, pickupAmt, currentCell);
	//	    }
}

bool ActionPickupResource::TaskComplete(GridAgent* agent){
	return true;
}

bool ActionPickupResource::IsValid(GridAgent* agent){
	GridCell* currentCell = agent->sensorModule.GetCurrentCell();
	if(currentCell->GetType() == resType){
		return true;
	}
	
	return false;
}

// -----------------------------------------------------------------
// ActionUseCarriedResource

void ActionUseCarriedResource::Execute(GridAgent* agent){
	agent->moveModule.StopMovement();
	
	agent->attributes.UseResource(resType);
	
}

bool ActionUseCarriedResource::TaskComplete(GridAgent* agent){
	return true;
}


bool ActionUseCarriedResource::IsValid(GridAgent* agent){
	
	if(agent->attributes.HasResource(resType)){
		return true;
	}
	
	return false;
}

// -----------------------------------------------------------------
// ActionDropResource

void ActionDropResource::Execute(GridAgent* agent){
	agent->moveModule.StopMovement();
	
	int dropAmt = agent->attributes.GetResourceDropAmt(resType);
	
	// this is maybe a little dodgy?? And not consistent with other stuff
	agent->attributes.DepositResource(resType, dropAmt, agent->sensorModule.GetCurrentCell());
}

bool ActionDropResource::TaskComplete(GridAgent* agent){
	return true;
}

bool ActionDropResource::IsValid(GridAgent* agent){
	if(agent->attributes.HasResource(resType)){
		return true;
	}
	
	return false;
}
