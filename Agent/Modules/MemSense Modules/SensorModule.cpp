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

void SensorModule::UpdateCellView(vector<GridCell*> cellsNear_){
	cellsNear = cellsNear_;
}

void SensorModule::UpdateAgentView(vector<GridAgent*> agentsNear_){
	agentsNear = agentsNear_;
}

// could these update classes use templates or generic facts?
void SensorModule::UpdateCellMemory(MemoryModule& memoryModule){
	
	for(int i = 0; i < cellsNear.size(); i++){
		int cellId = cellsNear[i]->GetId();
		// get neaby cell resource map
		vector<Resource> vecCellNearRes = cellsNear[i]->GetResourceHandler()->GetResources();
		mapRat mapCellNearRat = cellsNear[i]->GetRatingMap();
		float combinedRating = cellsNear[i]->GetCombinedRating();
		
		// TODO: this is crapppp
		if(!memoryModule.IsInMemory(cellId)) { // if cell not known
													  //			if(cellsNear[i]->GetType() != CELL_NEUTRAL) { // and if cell is not neutral
			if(/*cellsNear[i]->GetType() != CELL_NEUTRAL ||
				cellsNear[i]->GetAmtResource(CELL_FOOD) >= 0.1 || */
			   cellsNear[i]->GetRatingMap()[CELL_WOOD] > 0 ||
			   cellsNear[i]->GetRatingMap()[CELL_FOOD] > 0) { // and if cell is not neutral
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
			
			// ----------------------------------------------------------------------
			// BOOL STUFF
			// get known cell type from memory
			ItemType typeCellFact;
			mapRat mapKnownCellRat;
			
			// get known cell resource map
			vector<Resource> vecKnownCellRes;
			
			if(memoryModule.GetCellFact(cellId) != NULL){
			 vecKnownCellRes = memoryModule.GetCellFact(cellId)->GetResourceVec();
				typeCellFact = memoryModule.GetCellFact(cellId)->GetFactType();
				mapKnownCellRat = memoryModule.GetCellFact(cellId)->GetRatingsMap();
			}
			
			// probably no need for this, must be a compromise out there
			
			// if cell differs from memory by...
			// type
			bool cellTypeChanged = cellsNear[i]->GetType() != typeCellFact;
			// or
			// resource amount
			bool cellResourcesChanged = false;
			
			if(vecCellNearRes.size() == vecKnownCellRes.size()){
				for(int i = 0; i < vecCellNearRes.size(); i++){
					if(vecCellNearRes[i].GetAmtResource() ==
					   vecKnownCellRes[i].GetAmtResource()
					   &&
					   vecCellNearRes[i].GetType() ==
					   vecKnownCellRes[i].GetType()
					   ){
						cellResourcesChanged = true;
					}
				}
			}
			
			bool cellRatingsChanged = mapCellNearRat != mapKnownCellRat;
			
			// ----------------------------------------------------------------------
			
			if(cellTypeChanged || cellResourcesChanged || cellRatingsChanged) {
				bool homeChanged = cellsNear[i]->GetId() == memoryModule.GetCurrentHomeCellId() && memoryModule.HasHome();
				if(cellsNear[i]->GetType() != CELL_HOME
				   && homeChanged){
					memoryModule.RemoveHome();
					//					memoryModule.GetCellFact(cellId).SetHome(true);
				}
				// Update memory
				memoryModule.UpdateCellFact(cellId, cellsNear[i]->GetType(), vecCellNearRes, mapCellNearRat, combinedRating);
			}
		}
	}
	
	cellsNear.clear(); // clear cell memory
}


// need to make this work for setting more than just position
void SensorModule::UpdateAgentMemory(MemoryModule& memoryModule){
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
	agentsNear.clear(); // clear agent memory
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