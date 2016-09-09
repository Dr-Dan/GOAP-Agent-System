//
//  MemoryModule.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 20/04/2015.
//
//

#include "MemoryModule.h"
#include "GridAgent.h"
#include "WorldTypes.h"
using namespace WorldTypes;

MemoryModule::~MemoryModule(){
	Utility::ClearContainerPointers(cellFacts);
}

void MemoryModule::AddCellFact(CellFact fact){
	cellFacts.push_back(new CellFact(fact));
	facts.push_back(cellFacts.back());
}

void MemoryModule::AddAgentFact(AgentFact fact){
	agentFacts.push_back(fact);
	facts.push_back(&agentFacts.back());
}


bool MemoryModule::IsInMemory(int worldId){
	for(Fact* fact : facts){
		if (fact->GetTargetId() == worldId) {
			return true;
		}
	}
	return false;
}

CellFact* MemoryModule::GetCellFact(int worldId){
	for(int i = 0; i < cellFacts.size(); i++){
		if (cellFacts[i]->GetTargetId() == worldId) {
			return cellFacts[i];
		}
	}
	return NULL;
}

CellFact* MemoryModule::GetCellFact(ofVec2f gridPos){
	for(int i = 0; i < cellFacts.size(); i++){
		if (cellFacts[i]->GetGridPos() == gridPos) {
			return cellFacts[i];
		}
	}
	return NULL;
}

AgentFact MemoryModule::GetAgentFact(int worldId){
	for(int i = 0; i < agentFacts.size(); i++){
		if (agentFacts[i].GetTargetId() == worldId) {
			return agentFacts[i];
		}
	}
}

//void MemoryModule::UpdateCellInfo(const GridCell& cell){
//	bool homeChanged = HomeHasChanged(cell);
//	int cellId = cell.GetId();
//	if(homeChanged){
//		UpdateHomeInfo(cellId);
//	}
//	// Update memory
//	UpdateCellFact(cellId, cell.GetType(), vecCellNearRes, mapCellNearRat, combinedRating);
//}
//}

void MemoryModule::UpdateCellFact(int worldId, ItemType cellTypeIn, vector<Resource> cellResources_){
	for(int i = 0; i < cellFacts.size(); i++){
		CellFact* cellFact = cellFacts[i];
		if (cellFact->GetTargetId() == worldId) {
			cellFact->SetType(cellTypeIn);
			cellFact->UpdateResources(cellResources_);
		}
	}
}

void MemoryModule::UpdateCellFact(int worldId, ItemType cellTypeIn, vector<Resource> cellResources_, mapRat cellRatings_){
	for(int i = 0; i < cellFacts.size(); i++){
		CellFact* cellFact = cellFacts[i];
		if (cellFact->GetTargetId() == worldId) {
			cellFact->SetType(cellTypeIn);
			cellFact->UpdateResources(cellResources_);
			cellFact->UpdateRatings(cellRatings_);
		}
	}
}

void MemoryModule::UpdateCellFact(int worldId, ItemType cellTypeIn, vector<Resource> cellResources_, mapRat cellRatings_, float combinedRating_){
	for(int i = 0; i < cellFacts.size(); i++){
		CellFact* cellFact = cellFacts[i];
		if (cellFact->GetTargetId() == worldId) {
			cellFact->SetType(cellTypeIn);
			cellFact->UpdateResources(cellResources_);
			cellFact->UpdateRatings(cellRatings_);
			cellFact->SetCombinedRating(combinedRating_);

		}
	}
}

void MemoryModule::UpdatePosAgentFact(int worldId, ofVec2f newPos){
	ofVec2f posToAdd = newPos;
	for(AgentFact agentFact : agentFacts){
		AgentFact* aF = &agentFact;
		if (agentFact.GetTargetId() == worldId) {
			aF->SetGridPos(posToAdd);
		}
	}
}

bool MemoryModule::KnowsOfCell(int cellId){
	if(cellFacts.size() > 0){
		for(CellFact* cellFact : cellFacts){
			if(cellFact->GetTargetId() == cellId){
				return true;
			}
		}
	}
	return false;
}

bool MemoryModule::KnowsOfCellType(ItemType cellType){
	if(cellFacts.size() > 0){
		for(CellFact* cellFact : cellFacts){
			if(cellFact->GetFactType() == cellType){
				return true;
			}
		}
	}
	return false;
}

bool MemoryModule::KnowsOfResourceType(ItemType cellType){
	if(cellFacts.size() > 0){
		for(CellFact* cellFact : cellFacts){
			if(cellFact->GetResourceAmt(cellType)){
				return true;
			}
		}
	}
	return false;
}


bool MemoryModule::KnowsOfAgent(int agentId){
	if(agentFacts.size() > 0){
		for(AgentFact agentFact : agentFacts){
			if(agentFact.GetTargetId() == agentId){
				return true;
			}
		}
	}
	return false;
}

bool MemoryModule::KnowsOfHomeLocation(){
	if(!cellFacts.empty()){
		//		sort(cellFacts.begin(), cellFacts.end(), Utility::CellFactFoodRatingComp);
		
		for(int i = 0; i < cellFacts.size(); i++){
			if(cellFacts[i] ->GetFactType() == CELL_NEUTRAL){
				return true;
			}
		}
	}
	
	return false;
}

bool MemoryModule::KnowsOfUnfilledStorage(){
	if(!cellFacts.empty()){
		//		sort(cellFacts.begin(), cellFacts.end(), Utility::CellFactFoodRatingComp);
		
		for(int i = 0; i < cellFacts.size(); i++){
			if(cellFacts[i] ->GetFactType() == CELL_STORAGE ||
			   cellFacts[i] ->GetFactType() == CELL_STORAGE){
				if(!cellFacts[i]->IsFull()){
				return true;
				}
			}
		}
	}
	
	return false;
}

// is sort better than this comparing balls??
bool MemoryModule::GetPosNearestCell(ofVec2f& targetVec, ofVec2f pos, ItemType cellType){
	float currentDist = -1;
	ofVec2f closestPos = ofVec2f();
	
	for(CellFact* cellFact : cellFacts){
		if(cellType == cellFact->GetFactType()){
			float newDist = Utility::GetGridDistance(pos, cellFact->GetGridPos());
			// if new distance is closer or hasn't been set
			if(newDist < currentDist || currentDist == -1){
				currentDist = newDist;
				closestPos = cellFact->GetGridPos();
			}
		}
	}
	
	if(currentDist != -1){ // if currentDist has been changed
		targetVec = closestPos;
		return true;
	}
	
	return false;
}

// is sort better than this comparing balls??
bool MemoryModule::GetPosNearestCellList(vector<ofVec2f>& targetVec, ofVec2f pos, ItemType cellType){
	float currentDist = -1;

	vector<pair<ofVec2f, float>> distToPos;
	
	for(CellFact* cellFact : cellFacts){
		if(cellType == cellFact->GetFactType()){
			float newDist = Utility::GetGridDistance(pos, cellFact->GetGridPos());
			// if new distance is closer or hasn't been set
			if(newDist < currentDist || currentDist == -1){
				currentDist = newDist;
				distToPos.push_back(std::make_pair(cellFact->GetGridPos(), currentDist));
			}
		}
	}
	
	vector<ofVec2f> finalVec;
	for(pair<ofVec2f, float> d : distToPos){
		finalVec.push_back(d.first);
	}
	
	if(currentDist != -1){ // if currentDist has been changed
		targetVec = finalVec;
		return true;
	}
	
	return false;
}

bool MemoryModule::GetPosNearestResource(ofVec2f& targetVec, ofVec2f pos, ItemType resType){
	float currentDist = -1;
	ofVec2f closestPos = ofVec2f();
	
	for(CellFact* cellFact : cellFacts){
		if(cellFact->GetResourceAmt(resType)){ // will return 0(false) if no resources present
			float newDist = Utility::GetGridDistance(pos, cellFact->GetGridPos());
			if(newDist < currentDist || currentDist == -1){
				
				currentDist = newDist;
				closestPos = cellFact->GetGridPos();
			}
		}
	}
	
	if(currentDist != -1){
		targetVec = closestPos;
		return true;
	}
	return false;
}

//bool MemoryModule::GetPosHighestRatingCell(ofVec2f& targetVec, ItemType compType){
//	// better to keep a separate vector of sorted elements?
//	if(!cellFacts.empty()){
//		if(cellFacts[0] ->GetFactType() == compType){
//
//		targetVec = cellFacts[0]->GetGridPos();
//		}
//		return true;
//	}
//	return false;
//
//}

bool MemoryModule::GetPosHighestRatingCell(ofVec2f& targetVec, ItemType desiredType){
	// better to keep a separate vector of sorted elements?
	sortCellsByCombinedRating();
	
	if(!cellFacts.empty()){
		
		for(int i = 0; i < cellFacts.size(); i++){
			if(cellFacts[i] ->GetFactType() == desiredType
			   /* && cellFacts[i]->GetRatingsMap()[targetType] > 0.1*/){
				targetVec = cellFacts[i]->GetGridPos();
				return true;
			}
		}
		
		//		targetVec = cellFacts[0]->GetGridPos();
		//		return true;
	}
	
	return false;
	
}

bool MemoryModule::GetPosHighestRatingCell(ofVec2f& targetVec, ItemType desiredType, CellCompareFunc compFunc){
	// better to keep a separate vector of sorted elements?
	compFunc();
	
	if(!cellFacts.empty()){
		
		for(int i = 0; i < cellFacts.size(); i++){
			if(cellFacts[i] ->GetFactType() == desiredType
			   /* && cellFacts[i]->GetRatingsMap()[targetType] > 0.1*/){
				targetVec = cellFacts[i]->GetGridPos();
				return true;
			}
		}
		
		//		targetVec = cellFacts[0]->GetGridPos();
		//		return true;
	}
	
	return false;
	
}

//bool MemoryModule::GetPosHighestRatingCell(ofVec2f& targetVec, ItemType targetType, ItemType desiredType){
//	// better to keep a separate vector of sorted elements?

//this is where targetType would be used
//	sortCellsByFoodRating();
//
//	if(!cellFacts.empty()){
//
//		for(int i = 0; i < cellFacts.size(); i++){
//		//this is where desiredType would be used
//			if(cellFacts[i] ->GetFactType() == desiredType
//			   /* && cellFacts[i]->GetRatingsMap()[CELL_FOOD] > 0.1*/){
//				targetVec = cellFacts[i]->GetGridPos();
//				return true;
//			}
//		}
//
//		//		targetVec = cellFacts[0]->GetGridPos();
//		return true;
//	}
//
//	return false;
//
//}

CellFact* MemoryModule::GetFactHighestRatingCellFood(ItemType desiredType){
	sortCellsByFoodRating();
	bool knowsCellHome = false;
	
	if(!cellFacts.empty()){
		
		for(int i = 0; i < cellFacts.size(); i++){
			if(cellFacts[i] ->GetFactType() == desiredType
			   /* && cellFacts[i]->GetRatingsMap()[CELL_FOOD] > 0.1*/){
				//				factOut = cellFacts[i];
				return cellFacts[i];

//				for(int j = 0; j < cellFacts.size(); j++){
//					if(Utility::GetGridDistance(cellFacts[i]->GetGridPos(), cellFacts[j]->GetGridPos()) < 2){
//						if(cellFacts[j]->GetFactType() == CELL_HOME){
//							return cellFacts[j];
//						}
//					}
//				}
				
			}
			
			//		targetVec = cellFacts[0]->GetGridPos();
		}
	}
	return NULL;
}

CellFact* MemoryModule::GetFactHighestRatingCellCombined(ItemType desiredType){
	sortCellsByCombinedRating();
	bool knowsCellHome = false;
	
	if(!cellFacts.empty()){
		
		for(int i = 0; i < cellFacts.size(); i++){
			if(cellFacts[i] ->GetFactType() == desiredType
			   /* && cellFacts[i]->GetRatingsMap()[CELL_FOOD] > 0.1*/){
				//				factOut = cellFacts[i];
				return cellFacts[i];
				
				//				for(int j = 0; j < cellFacts.size(); j++){
				//					if(Utility::GetGridDistance(cellFacts[i]->GetGridPos(), cellFacts[j]->GetGridPos()) < 2){
				//						if(cellFacts[j]->GetFactType() == CELL_HOME){
				//							return cellFacts[j];
				//						}
				//					}
				//				}
				
			}
			
			//		targetVec = cellFacts[0]->GetGridPos();
		}
	}
	return nullptr;
}

CellFact* MemoryModule::GetFactHighestRatingCell(ItemType desiredType, CellCompareFunc compFunc){
	compFunc();
	
	bool knowsCellHome = false;
	
	if(!cellFacts.empty()){
		
		for(int i = 0; i < cellFacts.size(); i++){
			if(cellFacts[i] ->GetFactType() == desiredType
			   /* && cellFacts[i]->GetRatingsMap()[CELL_FOOD] > 0.1*/){
				//				factOut = cellFacts[i];
				return cellFacts[i];
				
				//				for(int j = 0; j < cellFacts.size(); j++){
				//					if(Utility::GetGridDistance(cellFacts[i]->GetGridPos(), cellFacts[j]->GetGridPos()) < 2){
				//						if(cellFacts[j]->GetFactType() == CELL_HOME){
				//							return cellFacts[j];
				//						}
				//					}
				//				}
				
			}
			
			//		targetVec = cellFacts[0]->GetGridPos();
		}
	}
	return NULL;
}



bool MemoryModule::GetPosNearestAgent(ofVec2f& targetVec, ofVec2f pos){
	float currentDist = -1;
	ofVec2f closestPos = ofVec2f();
	
	for(AgentFact agentFact : agentFacts){
		float newDist = Utility::GetGridDistance(pos, agentFact.GetGridPos());
		if(newDist < currentDist || currentDist == -1){
			
			currentDist = newDist;
			closestPos = agentFact.GetGridPos();
		}
	}
	if(currentDist != -1){
		targetVec = closestPos;
		return true;
	}
	return false;
	
}

void MemoryModule::sortCellsByFoodRating(){
	if(!cellFacts.empty()){
		sort(cellFacts.begin(), cellFacts.end(), Utility::CellFactFoodRatingComp);
	}
	//	cellsSorted = true;
}

void MemoryModule::sortCellsByCombinedRating(){
	if(!cellFacts.empty()){
		sort(cellFacts.begin(), cellFacts.end(), Utility::CellFactCombinedRatingComp);
	}
	//	cellsSorted = true;
}

void MemoryModule::UpdateHomeInfo(int cellId){
	RemoveHome();
	GetCellFact(cellId)->SetHome(true);
}

bool MemoryModule::HomeHasChanged(const GridCell& cell){
	bool homeMatch = cell.GetId() == GetCurrentHomeCellId();
	if(homeMatch){
	return HasHome() &&
	cell.GetType() != CELL_HOME;
	}
	return false;
}

void MemoryModule::RemoveHome(){
	if(homeCellId != -1){
		GetCellFact(homeCellId)->SetHome(false);
		homeCellId = -1;
		hasHome = false;
	}
	//	for(int i = 0; i < cellFacts.size(); i++){
	//		cellFacts[i]->SetHome(false);
	//	}
}

void MemoryModule::SetHomeCell(int cellId){
	// this function perhaps needn't exist
	// or could change the cell in fact vector
	//	cout<<"Home!"<<endl;
	hasHome = true;
	GetCellFact(cellId)->SetHome(true);
	homeCellId = cellId;
	/*
	 for(int i = 0; i < cellFacts.size(); i++){
		if (cellFacts[i]->GetTargetId() == cellId && cellFacts[i]->GetFactType() == CELL_HOME) {
	 cout<<"Home!"<<endl;
	 hasHome = true;
	 GetCellFact(cellId).SetHome(true);
	 homeCellId = cellId;
		}
	 }
	 */
}

int MemoryModule::GetBestHomeCellId(){
//	if(HasHome()){
		CellFact* homeCell = GetFactHighestRatingCellCombined(CELL_NEUTRAL);
		if(homeCell){
			//			float currentRat = agent->memoryModule.GetFactHighestRatingCellCombined(CELL_NEUTRAL)->GetCombinedRating();
			
			return homeCell->GetTargetId();
		}
//}
	return -1;
}

int MemoryModule:: GetCurrentHomeCellId(){
	// could do search of cellfacts...
	return homeCellId;
}

bool MemoryModule::HasHome(){
	return hasHome;
}

bool MemoryModule::ShouldDestroyHome(){
	bool knowsBetterCell = false;

	if(HasHome()){
		int bestHomeId = GetBestHomeCellId();
		
		if(GetCellFact(bestHomeId)->GetCombinedRating() >
		   GetCellFact(GetCurrentHomeCellId())->GetCombinedRating()){
			knowsBetterCell = GetCurrentHomeCellId() != bestHomeId;
		}
	}
	
	return HasHome() && knowsBetterCell;
	
}

void MemoryModule::RefreshCellMemory(const GridCell& cell){
	ItemType typeCellFact;
	mapRat mapKnownCellRat;
	vector<Resource> vecKnownCellRes;
	int cellId = cell.GetId();
	
	vector<Resource> vecCellNearRes = cell.GetResourceHandler()->GetResources();
	mapRat mapCellNearRat = cell.GetRatingMap();
	float combinedRating = cell.GetCombinedRating();
	
	if(KnowsOfCell(cellId)){
		CellFact* cellFact = GetCellFact(cellId);
		vecKnownCellRes = cellFact->GetResourceVec();
		typeCellFact = cellFact->GetFactType();
		mapKnownCellRat = cellFact->GetRatingsMap();
	} else {
		return;
	}
	
	// if cell differs from memory by...
	// type
	bool cellTypeChanged = cell.GetType() != typeCellFact;
	// or resource amount
	bool cellResourcesChanged = CellResourcesChanged(vecKnownCellRes, vecCellNearRes);
	// or by rating
	bool cellRatingsChanged = mapCellNearRat != mapKnownCellRat;
	
	// ----------------------------------------------------------------------
	
	if(cellTypeChanged || cellResourcesChanged || cellRatingsChanged) {
		bool homeChanged = HomeHasChanged(cell);
		if(homeChanged){
			UpdateHomeInfo(cellId);
		}
		// Update memory
		UpdateCellFact(cellId, cell.GetType(), vecCellNearRes, mapCellNearRat, combinedRating);
	}
}

bool MemoryModule::CellResourcesChanged(const vector<Resource>& vecKnownCellRes, const vector<Resource>& vecCellNearRes){
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

