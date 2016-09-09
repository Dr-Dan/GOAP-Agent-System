//
//  SensorModule.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 20/04/2015.
//
//

#include "SensorModule.h"
#include "GridAgent.h"

void SensorModule::SetCurrentCell(GridCell* cellIn){
	currentCell = cellIn;
}

GridCell* SensorModule:: GetCurrentCell(){
	return currentCell;
}

int SensorModule:: GetCurrentCellId(){
	return currentCell->GetId();
}

// could these update classes use templates or generic facts?
void SensorModule::UpdateCellMemory(MemoryModule& memoryModule,
									const vector<GridCell*>& cellsNear){
	for(int i = 0; i < cellsNear.size(); i++){
		int cellId = cellsNear[i]->GetId();
		if(!memoryModule.IsInMemory(cellId)) {
			if(ShouldAddCell(*cellsNear[i])) {
				// get neaby cell resource map
				vector<Resource> vecCellNearRes = cellsNear[i]->GetResourceHandler()->GetResources();
				mapRat mapCellNearRat = cellsNear[i]->GetRatingMap();
				float combinedRating = cellsNear[i]->GetCombinedRating();
				
				// Add to memory
				// CellFact(int factId_, string factType_, CellType itemType_, ofVec2f pos_)
				memoryModule.AddCellFact(
										 CellFact(
												  cellId,
												  cellsNear[i]->GetType(),
												  cellsNear[i]->GetGridPos(),
												  vecCellNearRes,
												  mapCellNearRat,
												  combinedRating
												  )
										 );
			}
		} else{ // if cell is known
			memoryModule.RefreshCellMemory(*cellsNear[i]);
		}
	}
	}

bool SensorModule::ShouldAddCell(const GridCell& cell){
	return cell.IsResource() ||
	cell.GetRatingMap()[CELL_WOOD] > 0 ||
	cell.GetRatingMap()[CELL_FOOD] > 0;
}


// need to make this work for setting more than just position
void SensorModule::UpdateAgentMemory(MemoryModule& memoryModule,
									 const vector<GridAgent*>& agentsNear){
	for(int i = 0; i < agentsNear.size(); i++){
		int agentId = agentsNear[i]->GetId();
		
		if(!memoryModule.IsInMemory(agentId)) { // if cell not known
			
			// Add to memory
			// AgentFact(int factId_, string factType_, CellType itemType_, ofVec2f pos_)
			memoryModule.AddAgentFact(
									  AgentFact(
												agentId,
												agentsNear[i]->moveModule.GetGridPos()
												)
									  );
		}
		else{ // if agent is known
			  // and agent differs from memory
			bool agentPosChanged = agentsNear[i]->moveModule.GetGridPos() !=
			memoryModule.GetAgentFact(agentId).GetGridPos();
			
			if(agentPosChanged) {
				// Update memory
				memoryModule.UpdatePosAgentFact(agentId, agentsNear[i]->moveModule.GetGridPos());
			}
		}
	}
}

bool SensorModule::AtCell(ItemType itemType){
	if(currentCell){
		if(currentCell->GetType() == itemType){
			return true;
		}
	}
	return false;
}

bool SensorModule::AtCellWithResource(ItemType itemType){
	if(currentCell){
		if(currentCell->GetResourceHandler()->GetAmtResource(itemType)){
			return true;
		}
	}
	return false;
}