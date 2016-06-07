//
//  CellMath.h
//  agentGridProto
//
//  Created by D J Clarke on 08/07/2015.
//
//

#ifndef __agentGridProto__CellMath__
#define __agentGridProto__CellMath__

#include <stdio.h>
#include "ofMain.h"
#include "GridValues.h"

class GridCell;

class CellMath{
public:
	typedef float (*ResourceRateFunc)(float resAmt, float dist, float maxInf);

	static float CellRatingCalcSimple(float resAmt, float dist, float maxInf);
	static float CellRatingCalcPlateau(float resAmt, float dist, float maxInf);

	// provides a function for comparing cell distances
	// useful as a predicate in sort functions
	static bool CellDistCompare(pair<GridCell*, float>  a, pair<GridCell*, float>  b);

	static float GetRatingThreshold(float thresValue);
	
};
#endif /* defined(__agentGridProto__CellMath__) */
