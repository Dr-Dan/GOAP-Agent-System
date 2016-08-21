//
//  Utility.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 09/03/2015.
//
//

#ifndef __AgentGOBGridTest__Utility__
#define __AgentGOBGridTest__Utility__

#include <stdio.h>
//#include "ofMain.h"
#include "ofVec2f.h"
#include "GridValues.h"

class GridCell;
class CellFact;

class Utility{
        static int worldId;
public:
    static int GetWorldId();
    
    // should maybe be replaced with getCell
    // will have to add offset later?
    static ofVec2f GetGridPos(ofVec2f refPos, vector<GridCell>& cells);
    
    static ofVec2f GetRandomGridPos();
    
    // provides distance between two positions
	// as vector
    static ofVec2f GetGridDistance2d(ofVec2f startPos, ofVec2f endPos);
	
	//
    static float GetGridDistance(ofVec2f startPos, ofVec2f endPos);
	
	
	// provides a function for comparing cell distances
	// useful as a predicate in sort functions
	static bool CellDistCompare(pair<GridCell*, float>  a, pair<GridCell*, float>  b);
	static bool PairDistCompare(pair<ofVec2f, float>  a, pair<ofVec2f, float>  b);

	static bool CellFactFoodRatingComp(CellFact* a, CellFact* b);
	static bool CellFactCombinedRatingComp(CellFact* a, CellFact* b);

	
    template<typename T>
    static void ClearContainerPointers(vector<T>& vecToClear){
        int numGoals = vecToClear.size()-1;
        for(int i = 0; i < numGoals; i++) {
            if(vecToClear[i]){
                delete vecToClear[i];
            }
        }
        vecToClear.clear();
    }
    
    template<typename T>
    static void ClearContainerPointers(deque<T>& dequeToClear){
        int numGoals = dequeToClear.size()-1;
        for(int i = 0; i < numGoals; i++) {
            if(dequeToClear[i]){
                delete dequeToClear[i];
            }
        }
        dequeToClear.clear();
    }


};
#endif /* defined(__AgentGOBGridTest__Utility__) */
