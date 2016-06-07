//
//  Utility.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 09/03/2015.
//
//

#include "Utility.h"
#include "GridCell.h"
#include "AgentFact.h"

int Utility::worldId = 0;

ofVec2f Utility::GetGridPos(ofVec2f refPos, vector<GridCell>& cells){
    ofVec2f posOut = ofVec2f();
    
    for(int i = 0; i < cells.size(); i++){
        if(cells[i].GetRect().inside(refPos)){
            posOut = cells[i].GetGridPos();
        }
    }
    return posOut;
}

int Utility::GetWorldId(){
    worldId++;
    return worldId-1;
}

ofVec2f Utility::GetRandomGridPos(){
    int randX = ofRandom(0,GridValues::GRID_DIMS[0]);
    int randY = ofRandom(0,GridValues::GRID_DIMS[1]);
    return ofVec2f(randX, randY);
}

ofVec2f Utility::GetGridDistance2d(ofVec2f startPos, ofVec2f endPos){
    return endPos-startPos;
}

float Utility::GetGridDistance(ofVec2f startPos, ofVec2f endPos){
    ofVec2f distOut = GetGridDistance2d(startPos, endPos);
    
    return distOut.length();
}

bool Utility::CellDistCompare(pair<GridCell*, float>  a, pair<GridCell*, float>  b){
	return a.second < b.second;
}

bool Utility::CellFactFoodRatingComp(CellFact* a, CellFact* b){
	return a->GetRatingAmt(WorldTypes::CELL_FOOD) > b->GetRatingAmt(WorldTypes::CELL_FOOD);
}

bool Utility::CellFactCombinedRatingComp(CellFact* a, CellFact* b){
		return a->GetCombinedRating() > b->GetCombinedRating();
}


