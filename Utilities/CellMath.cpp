//
//  CellMath.cpp
//  agentGridProto
//
//  Created by D J Clarke on 08/07/2015.
//
//

#include "CellMath.h"
#include "GridCell.h"

float CellMath::CellRatingCalcSimple(float resAmt, float dist, float maxInf){
	return maxInf/sqrt(1+dist);
}

float CellMath:: CellRatingCalcPlateau(float resAmt, float dist, float maxInf){
	return (maxInf/powf((1.0 + dist*3), 2)*0.25*resAmt);
}

bool CellMath::CellDistCompare(pair<GridCell*, float>  a, pair<GridCell*, float>  b){
	return a.second < b.second;
}

float CellMath::GetRatingThreshold(float thresValue){
	return GridValues::MAX_RATING/(thresValue - 1);
}