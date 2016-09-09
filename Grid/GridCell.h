//
//  GridCell.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 24/02/2015.
//
//

#ifndef __AgentGOBGridTest__GridCell__
#define __AgentGOBGridTest__GridCell__

#include <stdio.h>
//#include "ofMain.h"
#include "ofVec2f.h"
#include "ofRectangle.h"

#include "Entity.h"
#include "WorldTypes.h"
#include "CellMath.h"
#include "GridCellDisplay.h"
#include "Resource.h"
#include "ResourceUtility.h"
#include "ResourceHandler.hpp"

using namespace WorldTypes;

class GridCell: public Entity{
protected:
	// Variables
	
	ofVec2f pos;
	ofVec2f gridPos;
	int cellSize;
	ofRectangle cellRect;
	
	bool isOccupied = false;
	float cellAmt = 1.0f;

	bool hasChanged = false;
	
	// will later store if cell contains agent
	bool occupied;
	
	
	// resources variables
	bool isResource = false, isResourceNext = false;
	
	mapRat mapRatings;
	// average of ratings. Does not take resource importance into account
	float combinedRating = 0 /*, combinedRatingNext*/;
	
	ItemType cellType, cellTypeNext;

	void Setup();
	
	ResourceHandler resHandler;

//	Resource nextStateRes, currentStateRes;
public:
	GridCellDisplay cellDisplay;
	// Constructors
	
    GridCell();
	
    GridCell(ofVec2f pos, ofVec2f gridPos, int cellSize);
	
	GridCell(ofVec2f pos, ofVec2f gridPos, int cellSize, ItemType cellType);

	
	// -------------------------------------------------------------------------------
	// FUNCTIONS
	
	// -----------------------------------------------------------------
	// Setup
	
	void SetupType(ItemType type);

	// -------------------------------------------------------------------------------
	// Update
	
    void Update();
	
	// should belong to different class
	void UpdateOverlay(WorldTypes::OverlayType overlayType);

	// -----------------------------------------------------------------
	// Buffering
	
	void SwapStates();
	
	// -----------------------------------------------------------------
	// GetSetters
	
	ofVec2f GetPos() const;
	ofVec2f GetGridPos() const;

	int GetSize() const;
	
	ofRectangle GetRect() const;
	
	ItemType GetType() const;
	
	mapRat GetRatingMap() const;
	float GetCombinedRating() const;

	void SetChanged(bool state);
	
	// -------------------------------------------------------------------------------
	// RESOURCES
	
	// -----------------------------------------------------------------
	// Checkers
	
    bool IsResource() const;
    
    bool CellContainsResource(ItemType resType) const;
//	bool IsEmpty()

	bool IsChanged() const{
		return hasChanged;
	}
	
	ResourceHandler* GetResourceHandler() const;

	// -----------------------------------------------------------------
	// Resource Ratings
	void ClearResourceRating(ItemType itemType);
	void ClearResourceRatingAll();

    void SetResourceRating(WorldTypes::ItemType resType, float dist, float resAmt);
	void SetResourceRating(WorldTypes::ItemType resType, float dist, float resAmt, CellMath::ResourceRateFunc resFunc);

	// this could perhaps take a map of pair<ItemType, itemImportance>
	// but for now will just average
	void SetCombinedRating(vector<WorldTypes::ItemType> combineTypes);

	
};


#endif /* defined(__AgentGOBGridTest__GridCell__) */
