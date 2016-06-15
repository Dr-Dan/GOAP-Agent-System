//
//  AgentActionBuild.cpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 10/06/2016.
//
//

#include "AgentActionBuild.hpp"
#include "GridAgent.h"
#include "ResourceUtility.h"

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
// ActionBuildHome

void ActionBuildHome::Execute(GridAgent* agent){
	agent->moveModule.StopMovement();
	
	GridCell* currentCell = agent->sensorModule.GetCurrentCell(); // get agent's cell
	ItemType cellType = currentCell->GetType();
	bool cellNeedsChange = cellType != CELL_HOME;
	
	//	int homeId = agent->memoryModule.GetCurrentHomeCellId();
	
	if(cellNeedsChange){
		//		if(cellType == CELL_HOME){
		//			currentCell->SetupType(targetType);
		//			agent->memoryModule.RemoveHome();
		//		}
		
		//		if(targetType == CELL_HOME){
		bool hasHome = agent->memoryModule.HasHome();
		
		//			if(!hasHome){
		agent->memoryModule.SetHomeCell(currentCell->GetId());
		currentCell->SetupType(CELL_HOME);
		agent->attributes.UseResource(CELL_WOOD);
		//			}
		//		} else{
		//			currentCell->SetupType(targetType);
		//		}
	}
	
}

bool ActionBuildHome::TaskComplete(GridAgent* agent){
	GridCell* currentCell = agent->sensorModule.GetCurrentCell(); // get agent's cell
	if(currentCell->GetType() == CELL_HOME){
		return true;
	}
	return false;
}

bool ActionBuildHome::IsValid(GridAgent* agent){
	GridCell* currentCell = agent->sensorModule.GetCurrentCell();
	bool hasResources = agent->attributes.HasResource(CELL_WOOD);
	
	if(currentCell->GetType() != CELL_HOME && hasResources){
		return true;
	}
	
	return false;
}

// -----------------------------------------------------------------
// ActionDestroyHome

void ActionDestroyHome::Execute(GridAgent* agent){
	agent->moveModule.StopMovement();
	
	GridCell* currentCell = agent->sensorModule.GetCurrentCell(); // get agent's cell
	ItemType cellType = currentCell->GetType();
	
	int homeId = agent->memoryModule.GetCurrentHomeCellId();
	bool isHome = homeId == currentCell->GetId();
	bool agentHasHome = agent->memoryModule.HasHome();
	
	if(isHome && agentHasHome &&
	   cellType == CELL_HOME){
		currentCell->SetupType(CELL_NEUTRAL);
		agent->memoryModule.RemoveHome();
	}
	
}

bool ActionDestroyHome::TaskComplete(GridAgent* agent){
	GridCell* currentCell = agent->sensorModule.GetCurrentCell(); // get agent's cell
																  //	int homeId = agent->memoryModule.GetCurrentHomeCellId();
	bool agentHasHome = agent->memoryModule.HasHome();
	
	if(currentCell->GetType() == CELL_NEUTRAL && !agentHasHome){
		return true;
	}
	return false;
}

bool ActionDestroyHome::IsValid(GridAgent* agent){
	GridCell* currentCell = agent->sensorModule.GetCurrentCell();
	if(currentCell->GetType() == CELL_HOME){
		return true;
	}
	
	return false;
}

