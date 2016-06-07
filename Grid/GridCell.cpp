//
//  GridCell.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 24/02/2015.
//
//

#include "GridCell.h"
#include "GridValues.h"

// -------------------------------------------------------------------------------
// CONSTRUCTORS

GridCell::GridCell():
Entity(),
pos(ofVec2f()),
gridPos(ofVec2f()),
cellSize(GridValues::CELL_SIZE),
cellRect(ofRectangle())
{
	SetupType(CELL_NEUTRAL);
	Setup();
}

GridCell::GridCell(ofVec2f pos, ofVec2f gridPos, int cellSize):
Entity(),
pos(pos),
gridPos(gridPos),
cellSize(cellSize),
cellRect(ofRectangle(pos, cellSize, cellSize))
{
	SetupType(CELL_NEUTRAL);
	Setup();
}

GridCell::GridCell(ofVec2f pos, ofVec2f gridPos, int cellSize, ItemType cellType):
Entity(),
pos(pos),
gridPos(gridPos),
cellSize(cellSize),
cellRect(ofRectangle(pos, cellSize, cellSize))
{
	SetupType(cellType);
	Setup();
}

// -------------------------------------------------------------------------------
// FUNCTIONS

// -----------------------------------------------------------------
// Setup
void GridCell::Setup(){
	mapMaxRes[CELL_FOOD] = 50;
	mapMaxRes[CELL_WOOD] = 50;
	
	SetupResource(CELL_NEUTRAL);
	
	SetChanged(true);
}

void GridCell::SetupType(ItemType type){
	cellTypeNext = type;
	//			cellType = type;
	//	nextStateRes.SetupResource(type);
	
	//		cellDisplay.SetCellType(type);
	
	
	if(cellTypeNext == CELL_FOOD || cellTypeNext == CELL_WOOD){
		isResourceNext = true;
	} else{
		isResourceNext = false;
	}
	
	if(isResourceNext){
		SetupResource(type, true);
	} else {
		cellResourcesNext.clear();
	}
	
	if(cellTypeNext == CELL_STORAGE){
		SetupResource(CELL_FOOD, 0, false);
	}
	
	
	SetChanged(true);
}

//TODO
// needs to handle multiple types! e.g. storage
void GridCell::SetupResource(ItemType itemTypeIn, int amtRes, bool setRandom){
	cellResourcesNext.clear();
	cellResourcesNext.push_back(Resource());
	if(setRandom){
		cellResourcesNext.back().SetupResourceRandom(itemTypeIn);
	} else{
		cellResourcesNext.back().SetupResource(itemTypeIn, amtRes);
		
	}
	//	nextState.mapResources.clear();
	
	//	nextState.mapResources.insert(pair<ItemType,float>(itemTypeIn, ofRandom(0,mapMaxRes[itemTypeIn])));
	//	nextState.mapResources[itemTypeIn] = ofClamp(nextState.mapResources[itemTypeIn], 0, mapMaxRes[itemTypeIn]);
	
	SetChanged(true);
}

void GridCell::SetupResource(ItemType itemTypeIn, bool setRandom){
	SetupResource(itemTypeIn, 0, setRandom);
}

// -------------------------------------------------------------------------------
// Update

void GridCell::UpdateOverlay(WorldTypes::OverlayType overlayType){
	//	if(IsChanged()){
	
	if(cellResourcesCur.empty()){
		if(cellType == CELL_HOME){
			cellDisplay.SetCellType(CELL_HOME);
//			mapRatings[CELL_HOME] = 10;
		} else if(cellType == CELL_STORAGE){
			cellDisplay.SetCellType(CELL_STORAGE);
			//			mapRatings[CELL_HOME] = 10;
		} else{
			cellDisplay.SetCellType(CELL_NEUTRAL);
		}
	} else{
		cellDisplay.SetCellType(cellResourcesCur[0].GetType());
	}
	
	//	cellDisplay.UpdateOverlay(overlayType, mapRatings, combinedRating);
	cellDisplay.UpdateOverlay(overlayType, mapRatings[CELL_FOOD], mapRatings[CELL_WOOD], mapRatings[CELL_HOME], combinedRating);
	//	}
	
}

void GridCell::Update(){
	//	hasChanged = false;
	bool hasRes = false;
	
	// there is a better way to do this
	//	if(isResourceNext){
	
	for(int i = 0; i < cellResourcesNext.size(); i++){
		if(cellResourcesNext[i].GetAmtResource() > 0){
			hasRes = true;
		}
	}
	//	}
	
	if(!hasRes && (cellType != CELL_HOME && cellType != CELL_STORAGE)){
		SetupType(CELL_NEUTRAL);
		isResourceNext = false;
		SetChanged(true);
	}
}

// -----------------------------------------------------------------
// Buffering

void GridCell::SwapStates(){
	// swap and clear buffer items
	cellResourcesCur = cellResourcesNext;
	//	cout<<"res:"<<cellResourcesNext[0].GetAmtResource()<<endl;
	//		cout<<"type:"<<cellResourcesNext[0].GetType()<<endl;
	cellType = cellTypeNext;
	//	currentState.mapResources = nextState.mapResources;
	//	currentState.itemType = nextState.itemType;
	isResource = isResourceNext;
	//	mapRatings = mapRatingsNext;
}

// -----------------------------------------------------------------
// GetSetters

ofVec2f GridCell::GetPos() const{
	return pos;
}

ofVec2f GridCell::GetGridPos() const{
	return gridPos;
}

int GridCell::GetSize() const{
	return cellSize;
}


ofRectangle GridCell::GetRect() const {
	return cellRect;
}

// watch out, returning current state
//mapRes GridCell::GetResourceMap(){
//	return currentState.mapResources;
//}

mapRat GridCell::GetRatingMap(){
	return mapRatings;
}

float GridCell:: GetCombinedRating(){
	return combinedRating;
}

ItemType GridCell::GetType() const{
	if(cellResourcesNext.size() >= 1 ){
//		return cellResourcesNext[0].GetType();
	}
	return cellTypeNext;
}

Resource* GridCell::GetResource(WorldTypes::ItemType type){
	for(int i = 0; i < cellResourcesNext.size(); i++){
		if(cellResourcesNext[i].GetType() == type){
		return &cellResourcesNext[i];
		}
	}
}

vector<Resource> GridCell:: GetResources(){
	return cellResourcesNext;
}

float GridCell::GetAmtResource(WorldTypes::ItemType type) const{
	//	if(nextState.mapResources.count(type)){
	//		return nextState.mapResources.at(type);
	//	}
	
	for(int i = 0; i < cellResourcesNext.size(); i++){
		if(cellResourcesNext[i].GetType() == type){
			return cellResourcesNext[i].GetAmtResource();
		}
	}
	
	return 0;
}

void GridCell:: SetChanged(bool state){
	hasChanged = state;
}


// -------------------------------------------------------------------------------
// RESOURCES

// -----------------------------------------------------------------
// Checkers

bool GridCell::IsResource(){
	return isResourceNext;
}

bool GridCell::CellContainsResource(ItemType resType){
	if(!cellResourcesNext.empty()){
		for(int i = 0; i < cellResourcesNext.size(); i++){
			Resource cellRes = cellResourcesNext[i];
			if(cellRes.GetType() == resType && cellRes.GetAmtResource() > 0){
				return true;
			}
		}
	}
	return false;
}


bool GridCell::CellIsFull(){
	int resTotal = 0;
	for(Resource res: cellResourcesNext){
		resTotal += res.GetAmtResource();
	}
	if(resTotal >= GridValues::MAX_RESOURCES){
		return true;
	}
	return false;
}


bool GridCell::CanAddResources(ItemType resType, int amt){
	if(GetAmtResource(resType) + amt <= GridValues::MAX_RESOURCES){
		return true;
	}
	//	cout<<"Cell: "<<GetId()<<" Is full of type "<<resType<<endl;
	return false;
}

bool GridCell::HasResources(ItemType resType, int amt){
	if(CellContainsResource(resType) && amt <= GetAmtResource(resType)){
		return true;
	}
	//	cout<<"Cell: "<<GetId()<<" Has no resources of type "<<resType<<endl;
	return false;
}



// -----------------------------------------------------------------
// Resource Ratings
void GridCell::ClearResourceRating(ItemType itemType){
	mapRatings[itemType] = 0;
	
	// is it cheaper to just ignore this and assign anyway ??
	if(!hasChanged){
		//	SetChanged(true);
	}
}

void GridCell::ClearResourceRatingAll(){
	//	mapRatings[CELL_FOOD] = 0;
	//	mapRatings[CELL_WOOD] = 0;
	
	for(pairRat pR : mapRatings){
		ClearResourceRating(pR.first);
	}
	//	SetChanged(true);
}

void GridCell::SetResourceRating(WorldTypes::ItemType resType, float dist, float resAmt){
	//	ClearResourceRating(resType);
	mapRatings[resType] += /*(int)*/(GridValues::MAX_RATING/powf((1.0 + dist*3), 2)*0.25*resAmt);
	mapRatings[resType] = ofClamp(mapRatings[resType], -GridValues::MAX_RATING, GridValues::MAX_RATING);
	//	ratingResources[resType] += ((MAX_RATING/powf((1.0 + dist), 1.9)));
	
	SetChanged(true);
}

void GridCell::SetResourceRating(WorldTypes::ItemType resType, float dist, float resAmt, CellMath::ResourceRateFunc resFunc){
	//	ClearResourceRating(resType);
	
	mapRatings[resType] += resFunc(resAmt, dist, GridValues::MAX_RATING);
	mapRatings[resType] = ofClamp(mapRatings[resType], -GridValues::MAX_RATING, GridValues::MAX_RATING);
	
	SetChanged(true);
}

void GridCell::SetCombinedRating(vector<WorldTypes::ItemType> combineTypes){
	combinedRating = 0;
	int numTypes = combineTypes.size();
	
	for(WorldTypes::ItemType iType : combineTypes){
		if(mapRatings.count(iType)){
			combinedRating += mapRatings[iType];
		}
	}
	
	combinedRating /= (float)numTypes;
	combinedRating = ofClamp(combinedRating, 0, GridValues::MAX_RATING);
	
	SetChanged(true);
}


// -----------------------------------------------------------------
// Resource Changers

bool GridCell::AddResource(ItemType resType, int amt) {
return ResourceUtility::AddResource(GetResource(resType), amt);
//	if(CanAddResources(resType, amt)){
//		for(int i = 0; i < cellResourcesNext.size(); i++){
//			if(cellResourcesNext[i].GetType() == resType){
//				cellResourcesNext[i].ChangeResourceAmt(amt);
//				SetChanged(true);
//				
//				return true;
//			}
//		}
//	}
//	return false;
}

int GridCell::RemoveResources(ItemType resType, int amt){
//	Resource* resource = NULL;
	
	return ResourceUtility::RemoveResources(GetResource(resType), amt);
	
//	for(int i = 0; i < cellResourcesNext.size(); i++){
//		if(cellResourcesNext[i].GetType() == resType){
//			resource = &cellResourcesNext[i];
//		}
//	}
//	
//	if(resource){
//	if(HasResources(resType, amt)){
//		resource->ChangeResourceAmt(-amt);
//		SetChanged(true);
//		return amt; // if it has the resources, return demanded amount
//	} else if(!HasResources(resType, amt) && resource->GetAmtResource() != 0){
//		int remainder = resource->GetAmtResource(); // take what is left from resources
//		resource->SetupResource(resType, 0); // resources now empty
//		SetChanged(true);
//		return remainder; // else return remainder
//	}
//	}
//	
//	return 0;
}

