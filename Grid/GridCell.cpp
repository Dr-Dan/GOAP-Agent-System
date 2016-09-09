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
cellRect(ofRectangle(pos, cellSize, cellSize)),
resHandler(cellType)
{
	SetupType(cellType);
	Setup();
}

// -------------------------------------------------------------------------------
// FUNCTIONS

// -----------------------------------------------------------------
// Setup
void GridCell::Setup(){
	SetChanged(true);
}

void GridCell::SetupType(ItemType type){
	cellTypeNext = type;
	
	if(cellTypeNext == CELL_NEUTRAL){
		resHandler.ClearResources();
		isResourceNext = false;
		SetChanged(true);
		return;
	}
	
	if(cellTypeNext == CELL_FOOD || cellTypeNext == CELL_WOOD){
		isResourceNext = true;
	} else{
		isResourceNext = false;
	}
	
	if(isResourceNext){
		resHandler.SetupResource(type, true);
	} else {
		resHandler.ClearResources();
	}
	
	if(cellTypeNext == CELL_STORAGE){
		resHandler.AddResourceType(CELL_FOOD, 0);
		resHandler.AddResourceType(CELL_WOOD, 0);
	}
	
	SetChanged(true);
}

// -------------------------------------------------------------------------------
// Update

void GridCell::UpdateOverlay(WorldTypes::OverlayType overlayType){
	//	if(IsChanged()){
	
	if(!resHandler.HasResource()){
		if(cellType == CELL_HOME){
			cellDisplay.SetCellType(CELL_HOME);
		} else{
			cellDisplay.SetCellType(CELL_NEUTRAL);
		}
	} else if(cellType == CELL_STORAGE){
		cellDisplay.SetCellType(CELL_STORAGE);
	} else{
		cellDisplay.SetCellType(cellType);
	}
	
	cellDisplay.UpdateOverlay(overlayType, mapRatings[CELL_FOOD], mapRatings[CELL_WOOD], mapRatings[CELL_HOME], combinedRating);
}

void GridCell::Update(){
	bool hasRes = false;
	
	if(resHandler.HasResourceNext()){
		hasRes = true;
	}
	
	//	}
	
	if(!hasRes &&
	   (cellType != CELL_HOME && cellType != CELL_STORAGE)){
		   SetupType(CELL_NEUTRAL);
//		   isResourceNext = false;
//		   SetChanged(true);
	   }
}

// -----------------------------------------------------------------
// Buffering
// update to next state
void GridCell::SwapStates(){
	// swap and clear buffer items
	//	cellResourcesCur = cellResourcesNext;
	resHandler.SwapStates();
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

mapRat GridCell::GetRatingMap() const{
	return mapRatings;
}

float GridCell:: GetCombinedRating() const{
	return combinedRating;
}

ItemType GridCell::GetType() const{
	return cellTypeNext;
}

void GridCell:: SetChanged(bool state){
	hasChanged = state;
}


// -------------------------------------------------------------------------------
// RESOURCES

// -----------------------------------------------------------------
// Checkers

bool GridCell::IsResource() const{
	return isResourceNext;
}

bool GridCell::CellContainsResource(ItemType resType) const{
	if(resHandler.HasResourceNext()){
		vector<Resource> res = resHandler.GetResources();
		for(int i = 0; i < res.size(); i++){
			Resource cellRes = res[i];
			if(cellRes.GetType() == resType && cellRes.GetAmtResource() > 0){
				return true;
			}
		}
	}
	return false;
}


ResourceHandler* GridCell::GetResourceHandler() const{
	return const_cast<ResourceHandler*>(&resHandler);
}

// -----------------------------------------------------------------
// Resource Ratings
// would be nice to put this in separate class
void GridCell::ClearResourceRating(ItemType itemType){
	mapRatings[itemType] = 0;
}

void GridCell::ClearResourceRatingAll(){
	for(pairRat pR : mapRatings){
		ClearResourceRating(pR.first);
	}
}

void GridCell::SetResourceRating(WorldTypes::ItemType resType, float dist, float resAmt){
	mapRatings[resType] += /*(int)*/(GridValues::MAX_RATING/powf((1.0 + dist*3), 2)*0.25*resAmt);
	mapRatings[resType] = ofClamp(mapRatings[resType], -GridValues::MAX_RATING, GridValues::MAX_RATING);
	//	ratingResources[resType] += ((MAX_RATING/powf((1.0 + dist), 1.9)));
	
	SetChanged(true);
}

void GridCell::SetResourceRating(WorldTypes::ItemType resType, float dist, float resAmt, CellMath::ResourceRateFunc resFunc){
	
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



