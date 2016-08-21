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

//void SensorModule::UpdateCellView(const vector<GridCell*>& cellsNear_){
//	cellsNear = cellsNear_;
//}

//void SensorModule::UpdateAgentView(const vector<GridAgent*>& agentsNear_){
//	agentsNear = agentsNear_;
//}

// could these update classes use templates or generic facts?
void SensorModule::UpdateCellMemory(MemoryModule& memoryModule,
									const vector<GridCell*>& cellsNear_){
	
	for(int i = 0; i < cellsNear.size(); i++){
		// get neaby cell resource map
		vector<Resource> vecCellNearRes = cellsNear[i]->GetResourceHandler()->GetResources();
		mapRat mapCellNearRat = cellsNear[i]->GetRatingMap();
		float combinedRating = cellsNear[i]->GetCombinedRating();
		
		int cellId = cellsNear[i]->GetId();
		if(!memoryModule.IsInMemory(cellId)) {
			if(ShouldAddCell(*cellsNear[i])) {
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
			ItemType typeCellFact;
			mapRat mapKnownCellRat;
			vector<Resource> vecKnownCellRes;
			
			if(memoryModule.KnowsOfCell(cellId)){
				CellFact* cellFact = memoryModule.GetCellFact(cellId);
				vecKnownCellRes = cellFact->GetResourceVec();
				typeCellFact = cellFact->GetFactType();
				mapKnownCellRat = cellFact->GetRatingsMap();
			}
			
			// if cell differs from memory by...
			// type
			bool cellTypeChanged = cellsNear[i]->GetType() != typeCellFact;
			// or resource amount
			bool cellResourcesChanged = CellResourcesChanged(vecKnownCellRes, vecCellNearRes);
			// or by rating
			bool cellRatingsChanged = mapCellNearRat != mapKnownCellRat;
			
			// ----------------------------------------------------------------------
			
			if(cellTypeChanged || cellResourcesChanged || cellRatingsChanged) {
				bool homeChanged = memoryModule.HomeHasChanged(*cellsNear[i]);
				if(homeChanged){
					memoryModule.UpdateHomeInfo(cellId);
				}
				// Update memory
				memoryModule.UpdateCellFact(cellId, cellsNear[i]->GetType(), vecCellNearRes, mapCellNearRat, combinedRating);
			}
		}
	}
	
	cellsNear.clear(); // clear cell memory
}

bool SensorModule::ShouldAddCell(const GridCell& cell){
	return cell.IsResource() ||
	cell.GetRatingMap()[CELL_WOOD] > 0 ||
	cell.GetRatingMap()[CELL_FOOD] > 0;
}


bool SensorModule::CellResourcesChanged(const vector<Resource>& vecKnownCellRes, const vector<Resource>& vecCellNearRes){
	if(vecCellNearRes.size() == vecKnownCellRes.size()){
		for(int i = 0; i < vecCellNearRes.size(); i++){
			if(vecCellNearRes[i].GetAmtResource() ==
			   vecKnownCellRes[i].GetAmtResource()
			   &&
			   vecCellNearRes[i].GetType() ==
			   vecKnownCellRes[i].GetType()
			   ){
				return true;
			}
		}
	}
	return false;
}

// need to make this work for setting more than just position
void SensorModule::UpdateAgentMemory(MemoryModule& memoryModule,
									 const vector<GridAgent*>& agentsNear_){
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