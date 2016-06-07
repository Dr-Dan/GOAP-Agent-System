//
//  GridAgentActions.cpp
//  AgentGridActions
//
//  Created by D J Clarke on 03/03/2015.
//
//

#include "GridAgentActions.h"
#include "GridAgent.h"
#include "ResourceUtility.h"

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

// -----------------------------------------------------------------
// ActionUseCell

void ActionUseCell::Execute(GridAgent* agent){
	agent->moveModule.StopMovement();
	//    cout<<"Doing eat action"<<endl;
	//    cout<<"Hg: "<<agent->attributes.hunger<<endl;
	
	GridCell* currentCell = agent->sensorModule.GetCurrentCell(); // get agent's cell
	if(!currentCell->GetResource(cellType)){
		return false;
	}
	if(currentCell->IsResource() && cellType != CELL_HOME){
		int amt = agent->attributes.GetNeedReductionAmt(cellType);
		if(ResourceUtility::RemoveResources(currentCell->GetResource(cellType), amt)){
//		if(currentCell->RemoveResources(cellType, agent->attributes.GetNeedReductionAmt(cellType))){
			agent->attributes.SatisfyNeed(cellType);
		}
	}
 else if(currentCell->GetType() == CELL_HOME){
		agent->attributes.SatisfyNeed(cellType);
	}
}

bool ActionUseCell::TaskComplete(GridAgent* agent){
	if(agent->attributes.NeedIsSatisfied(cellType)){
		return true;
	}
	return false;
}

// -----------------------------------------------------------------
// ActionChangeCell

void ActionChangeCell::Execute(GridAgent* agent){
	agent->moveModule.StopMovement();
	
	GridCell* currentCell = agent->sensorModule.GetCurrentCell(); // get agent's cell
	ItemType cellType = currentCell->GetType();
	bool cellNeedsChange = cellType != targetType;
	
	if(cellNeedsChange){
		if(cellType == CELL_HOME){
			currentCell->SetupType(targetType);
			agent->memoryModule.RemoveHome();
		}
		
		if(targetType == CELL_HOME){
			bool hasHome = agent->memoryModule.HasHome();
			
			if(!hasHome){
				//			agent->attributes.hasHome = true;
//							agent->memoryModule.GetCellFact(currentCell->GetId()).SetHome(true);
				agent->memoryModule.SetHomeCell(currentCell->GetId());
				currentCell->SetupType(targetType);
			}
		} else{
			currentCell->SetupType(targetType);
//			agent->memoryModule.RemoveHome();

		}
	}
}

bool ActionChangeCell::TaskComplete(GridAgent* agent){
	GridCell* currentCell = agent->sensorModule.GetCurrentCell(); // get agent's cell
	if(currentCell->GetType() == targetType){
		return true;
	}
	return false;
}



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

// -----------------------------------------------------------------
// ActionUseCarriedResource

void ActionUseCarriedResource::Execute(GridAgent* agent){
	agent->moveModule.StopMovement();
	
	agent->attributes.UseResource(cellType);
	
}

bool ActionUseCarriedResource::TaskComplete(GridAgent* agent){
	return true;
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



// -----------------------------------------------------------------
// ActionFindFood
// currently just wander, needs real implementation

void ActionWander::Execute(GridAgent* agent){
	//    agent->spd = ofVec2f((int)ofRandom(-2,2), (int)ofRandom(-2,2));
	/*
	 float tm = ofGetElapsedTimef();
	 
	 int noiseX = (ofNoise(tm * ofRandom(10)) - 0.5)*25;
	 int noiseY = (ofNoise(-tm * ofRandom(10)) - 0.5)*25;
	 
	 noiseX = ofClamp(noiseX, -1, 1);
	 noiseY = ofClamp(noiseY, -1, 1);
	 
	 //        cout<<"nX: "<< noiseX<<endl;
	 //        cout<<"nY: "<< noiseY<<endl<<endl;
	 
	 agent->moveModule.SetSpd(ofVec2f(noiseX, noiseY));
	 //    cout<<"Doing wander action"<<endl;
	 */
	
	ofVec2f targetCell = Utility::GetRandomGridPos();
	agent->moveModule.HeadTowardsGridPos(targetCell);
	
}

bool ActionWander::TaskComplete(GridAgent* agent){
	return false;
}
