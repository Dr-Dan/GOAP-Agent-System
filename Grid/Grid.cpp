//
//  AgentGrid.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 24/02/2015.
//
//

#include "Grid.h"

Grid::Grid():
gridDims(ofVec2f(GridValues::GRID_DIMS[0],GridValues::GRID_DIMS[1])),
overlayType(WorldTypes::NO_OVERLAY),
ratDisplayType(WorldTypes::CELL_FOOD){
	Setup();
}

// -----------------------------------------------------------------
// Functions

void Grid::Setup(){
	CreateGrid();
	
	resTypes.push_back(WorldTypes::CELL_FOOD);
	resTypes.push_back(WorldTypes::CELL_WOOD);
	resTypes.push_back(WorldTypes::CELL_HOME);
	
}

void Grid::CreateGrid(){
	int cellSize = GridValues::CELL_SIZE;
	for(int x = 0; x < gridDims.x; x++){
		for(int y = 0; y < gridDims.y; y++){
			cells.push_back(GridCell(ofVec2f(x * cellSize, y * cellSize),
									 ofVec2f(x,y), cellSize));
		}
	}
}

// -----------------------------------------------------------------

void Grid::Update(){
	for(int i = 0; i < cells.size(); i++) {
		//		if(cells[i].IsChanged()){
		cells[i].SwapStates();
		cells[i].Update();
		
		//		}
		
	}
}

void Grid::Display(bool showResAmt){
	
	bool showInfluence = false;
	
	if(overlayType != WorldTypes::NO_OVERLAY){
		showInfluence = true;
	} else{
		showInfluence = false;
	}
	
	for(int i = 0; i < cells.size(); i++) {
		//						if(cells[i].IsChanged()){
		cells[i].UpdateOverlay(overlayType);
		//						}
		DisplayVisitor::Render(cells[i], showResAmt, showInfluence);
		
		if(showInfluence){
			float cellFoodInf = 0;
			if(overlayType == OVERLAY_FOOD){
				cellFoodInf = cells[i].GetRatingMap()[CELL_FOOD];
			} else if(overlayType == OVERLAY_WOOD){
				cellFoodInf = cells[i].GetRatingMap()[CELL_WOOD];
			} else if(overlayType == OVERLAY_HOME){
				cellFoodInf = cells[i].GetRatingMap()[CELL_HOME];
			} else if(overlayType == OVERLAY_AVG){
				cellFoodInf = cells[i].GetCombinedRating();
			}
			
			if(cells[i].GetType() == CELL_HOME){
				if(GridValues::displayRatText){

				if(cellFoodInf <= -0.1){
					ofSetColor(255,0,0);
					ofFill();
					
					ofVec2f infoPos = (cells[i].GetPos() + ofVec2f(5,10));
					//		 this is the slower downer!!!
					ofDrawBitmapString(ofToString((cellFoodInf), 0), infoPos.x, infoPos.y);
				}
				}
			} else {
		 if(cellFoodInf >= 0.1){
			 if(GridValues::displayRatText){
			 ofSetColor(255,0,0);
			 ofFill();
			 
			 ofVec2f infoPos = (cells[i].GetPos() + ofVec2f(5,10));
			 //		 this is the slower downer!!!
			 ofDrawBitmapString(ofToString((cellFoodInf), 0), infoPos.x, infoPos.y);
			 }
		 }
		}
	}
	}
	
}


// -----------------------------------------------------------------
// Cell Info

void Grid::ClearRatings(){
	for(int i = 0; i < cells.size(); i++){
		if(cells[i].IsChanged()){
			cells[i].ClearResourceRatingAll();
		}
	}
}

void Grid::CheckCells(){
	for(int i = 0; i < cells.size(); i++){
		if(cells[i].IsChanged()){
			// ???
		}
	}
}

void Grid::ChangeCellType(int cellId, WorldTypes::ItemType newRes){
	GridCell* currentCell = GetCell(cellId);
	currentCell->SetupType(newRes);
	
	for(int i = 0; i < cells.size(); i++){
		//					cells[i].ClearResourceRatingAll();
		
		// get distance between cells
		ofVec2f cellPos[2] = {currentCell->GetGridPos(), cells[i].GetGridPos()};
		float dist = Utility::GetGridDistance(cellPos[0], cellPos[1]);
		
		// set all cells at given distance to changed for later processing
		if(dist < CellMath::GetRatingThreshold(GridValues::RATING_THRES)){
			cells[i].SetChanged(true);
		}
	}
}

void Grid::ChangeCellType(int cellId, WorldTypes::ItemType newRes, int dist){
	GridCell* currentCell = GetCell(cellId);
	//	currentCell->SetupType(newRes);
	vector<GridCell*> cellsNear;
	cellsNear = GetSurroundingCells(currentCell->GetGridPos(), dist);
	
	for(int h = 0; h < cellsNear.size(); h++){
		cellsNear[h]->SetupType(newRes);
		
		for(int i = 0; i < cells.size(); i++){
			//					cells[i].ClearResourceRatingAll();
			
			// get distance between cells
			ofVec2f cellPos[2] = {cellsNear[h]->GetGridPos(), cells[i].GetGridPos()};
			float dist = Utility::GetGridDistance(cellPos[0], cellPos[1]);
			
			// set all cells at given distance to changed for later processing
			if(dist < CellMath::GetRatingThreshold(GridValues::RATING_THRES)){
				cells[i].SetChanged(true);
			}
		}
	}
}

void Grid::UpdateRatings(){
	// calculate new ratings
	for(int i = 0; i < cells.size(); i++){
		
		// check cell has changed
		if(cells[i].IsChanged()){
			cells[i].ClearResourceRatingAll();
			
			for(int j = 0; j < cells.size(); j++){
				// get distance between cells
				ofVec2f cellPos[2] = {cells[i].GetGridPos(), cells[j].GetGridPos()};
				float dist = Utility::GetGridDistance(cellPos[0], cellPos[1]);
				
				if(cells[j].IsResource()){
					
					//				if(cells[j].GetType() == WorldTypes::CELL_FOOD
					//				   || cells[j].GetType() == WorldTypes::CELL_WOOD){
					
					//					// get distance between cells
					//					ofVec2f cellPos[2] = {cells[i].GetGridPos(), cells[j].GetGridPos()};
					//					float dist = Utility::GetGridDistance(cellPos[0], cellPos[1]);
					
					if(dist < CellMath::GetRatingThreshold(GridValues::RATING_THRES)){
						
						float resAmtFood = cells[j].GetAmtResource(WorldTypes::CELL_FOOD); // get amount of food in cell
						float resAmtWood = cells[j].GetAmtResource(WorldTypes::CELL_WOOD); // get amount of food in cell
						
						
						cells[i].SetResourceRating(WorldTypes::CELL_FOOD, dist, resAmtFood, CellMath::CellRatingCalcPlateau);
						
						cells[i].SetResourceRating(WorldTypes::CELL_WOOD, dist, resAmtWood, CellMath::CellRatingCalcPlateau);
						
						
						
					}
				} else if(cells[j].GetType() == CELL_HOME && dist > 0){
					float ratAmtHome = GridValues::MAX_RATING; // get amount of food in cell
				
				cells[i].SetResourceRating(WorldTypes::CELL_HOME, dist, -ratAmtHome, CellMath::CellRatingCalcPlateau);
			}
		}
		cells[i].SetCombinedRating(resTypes);
		
		cells[i].SetChanged(false);
		
	}
}
}


void Grid::RandomizeGrid(){
	ClearGrid();
	
	for(int i = 0; i < cells.size(); i++){
		WorldTypes::ItemType iType;
		int randNum = (int)ofRandom(6);
		
		switch (randNum) {
			case 0:
				iType = WorldTypes::CELL_NEUTRAL;
				break;
			case 1:
				iType = WorldTypes::CELL_FOOD;
				break;
			case 2:
				iType = WorldTypes::CELL_WOOD;
				break;
			default:
				iType = WorldTypes::CELL_NEUTRAL;
				break;
		}
		
		cells[i].SetupType(iType);
	}
}

void Grid::ClearGrid(){
	for(int i = 0; i < cells.size(); i++){
		cells[i].SetupType(WorldTypes::CELL_NEUTRAL);
	}
}

// -----------------------------------------------------------------
// Cell Access

GridCell* Grid::GetCell(ofVec2f gridPos){
	GridCell* cellOut = NULL;
	for(int i = 0; i < cells.size(); i++){
		if(cells[i].GetGridPos() == gridPos){
			cellOut = &cells[i];
		}
	}
	return cellOut;
}

GridCell* Grid::GetCell(int cellId){
	GridCell* cellOut = NULL;
	for(int i = 0; i < cells.size(); i++){
		if(cells[i].GetId() == cellId){
			cellOut = &cells[i];
		}
	}
	return cellOut;
}

vector<GridCell*> Grid::GetSurroundingCells(ofVec2f gridPos,int radius){
	vector<GridCell*> cellsOut;
	
	for(int x = gridPos.x - radius; x <= gridPos.x + radius; x++){
		for(int y = gridPos.y-radius; y <= gridPos.y+radius; y++){
			ofVec2f currPos = ofVec2f(x,y);
			GridCell* currCell = GetCell(currPos);
			if (currCell != NULL){
				cellsOut.push_back(currCell);
			}
		}
	}
	return cellsOut;
}

// ----------------------------------------------------------------------------------

// GRAVEYARD

//void Grid::UpdateRatings(WorldTypes::ItemType currentRes){
//	//	changedCells.clear();
//
//	//	WorldTypes::mapRat mapRatings;
//	//	mapRatings.insert(WorldTypes::pairRat(WorldTypes::CELL_FOOD, 0));
//	//	mapRatings.insert(WorldTypes::pairRat(WorldTypes::CELL_WOOD, 0));
//
//	// clear cell ratings
//	//	for(int i = 0; i < cells.size(); i++){
//	//		cells[i].ClearResourceRating(currentRes);
//	//	}
//
//	// calculate new ratings
//	for(int i = 0; i < cells.size(); i++){
//
//		if(cells[i].IsChanged()){
//			//					cells[i].ClearResourceRatingAll();
//
//			for(int j = 0; j < cells.size(); j++){
//
//				if(cells[j].GetType() == currentRes){
//					float resAmt = cells[j].GetAmtResource(currentRes); // get amount of food in cell
//
//					ofVec2f cellPos[2] = {cells[i].GetGridPos(), cells[j].GetGridPos()};
//
//					float dist = Utility::GetGridDistance(cellPos[0], cellPos[1]);
//
//					if(dist < CellMath::GetRatingThreshold(GridValues::RATING_THRES)){
//						//						cells[i].ClearResourceRatingAll();
//
//						cells[i].SetResourceRating(currentRes, dist, resAmt, CellMath::CellRatingCalcPlateau);
//
//
//						cells[i].SetChanged(true);
//
//						// store changed cell id for later
//						//						if(find(changedCells.begin(), changedCells.end(), i) == changedCells.end()){
//						//						changedCells.push_back(i);
//						//						}
//					}
//
//					//				cells[i].SetResourceRating(currentRes,dist);
//					//				cells[i].GetResourceMap()[WorldTypes::CELL_FOOD] += ((10/powf((1.0 + dist), 1.9)));
//
//					//                                        cells[i].foodRating += maxFoodInfluence/sqrt(1+dist);
//				}
//			}
//			//						cells[i].SetChanged(false);
//		}
//	}
//}


//void Grid:: UpdateRatingsCombined(){
//	for(int i = 0; i < cells.size(); i++){
//		if(cells[i].IsChanged()){
//			cells[i].SetCombinedRating(resTypes);
//		}
//	}
//}


//void Grid::SetCellsIsChanged(bool state){
//	for(int i = 0; i < cells.size(); i++){
//		cells[i].SetChanged(state);
//	}
//}

