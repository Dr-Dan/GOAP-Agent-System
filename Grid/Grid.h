//
//  AgentGrid.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 24/02/2015.
//
//

#ifndef __AgentGOBGridTest__Grid__
#define __AgentGOBGridTest__Grid__

#include <stdio.h>

//#include "ofMain.h"
#include "ofVec2f.h"

#include "GridCell.h"
#include "DisplayVisitor.h"
#include "TimeMaster.h"
#include "WorldTypes.h"
#include "GridValues.h"
#include "CellMath.h"
#include "AgentManager.h"
class Grid{
    
    // Variables
    ofVec2f gridDims; // Grid dimensions
	vector<GridCell> cells;
	int cellSize;
//	vector<int> changedCells;
//	map<int, WorldTypes::mapRat> mapIdToRatings;
	
	vector<WorldTypes::ItemType> resTypes;
//	AgentManager* agentManager;

	
	bool displayResText = false;
public:

	WorldTypes::ItemType ratDisplayType;
	WorldTypes::OverlayType overlayType;
	// -----------------------------------------------------------------

    // Constructors
    Grid();

	// -----------------------------------------------------------------

    // Functions
    
    void Setup();
    
    void CreateGrid();
    void Update();

    void Display(bool showResAmt = false);
	
	void CheckCells();
	
    // -----------------------------------------------------------------
    // Cell Info
    
    // need better distance/rating metric?! + should be utility
	
	void ClearRatings();
	
	void UpdateRatings();
//	void UpdateRatings(WorldTypes::ItemType currentRes);
	
	// need to decide from which point rating types will be chosen
//	void UpdateRatingsCombined();
	
	void RandomizeGrid();
	
	void ClearGrid();
	
//	void SetCellsIsChanged(bool state);

	// change single cell
	void ChangeCellType(int cellId, WorldTypes::ItemType newRes);
	// change cell group
	void ChangeCellType(int cellId, WorldTypes::ItemType newRes, int dist);

	// -----------------------------------------------------------------
    // Cell Access
    
    GridCell* GetCell(ofVec2f gridPos);
    GridCell* GetCell(int cellId);
	
	vector<GridCell>& GetCells(){
		return cells;
	}
	
    vector<GridCell*> GetSurroundingCells(ofVec2f gridPos,int radius);
	
	
	// -----------------------------------------------------------------
	// Graveyard


};
#endif /* defined(__AgentGOBGridTest__Grid__) */
