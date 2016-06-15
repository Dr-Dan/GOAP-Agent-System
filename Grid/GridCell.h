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
#include "ofMain.h"
#include "Entity.h"
#include "WorldTypes.h"
#include "CellMath.h"
#include "GridCellDisplay.h"
#include "Resource.h"
#include "ResourceUtility.h"

using namespace WorldTypes;

class GridCell: public Entity{
	

	// Variables
	
	ofVec2f pos;
	ofVec2f gridPos;
	int cellSize;
	ofRectangle cellRect;
//	ofColor cellColor;
	
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
	
	// stores max resource amounts
	map<ItemType, int> mapMaxRes;
	
	// Next state info
	// Could this just be some kind of resource class???
	// should both sets of state values belong to same object
//	struct CellStateRes {
//		CellStateRes():
//		itemType(WorldTypes::CELL_NEUTRAL),
//		mapResources(mapRes())
//		{
//			
//		}
//		
//		// vars
//		ItemType itemType;
//		mapRes mapResources;
//		
//	} nextState, currentState;
//	
	vector<Resource> cellResourcesCur, cellResourcesNext;
	
	// PVT FUNCTIONS
	void Setup();

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
	
	
	void SetupResource(ItemType itemTypeIn, bool setRandom = false);
	void SetupResource(ItemType itemTypeIn, int amtRes, bool setRandom = false, bool reset = true);
	
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
	
//	mapRes GetResourceMap();
	mapRat GetRatingMap();
	float GetCombinedRating();
	
	Resource* GetResource(WorldTypes::ItemType type);
	
	vector<Resource> GetResources();
	
	float GetAmtResource(WorldTypes::ItemType type) const;

	void SetChanged(bool state);
	
	// -------------------------------------------------------------------------------
	// RESOURCES
	
	// -----------------------------------------------------------------
	// Checkers
	
    bool IsResource();
    
    bool CellContainsResource(ItemType resType);
    
    // sum all stored resources and compare against max capacity
    bool CellIsFull();

    bool CanAddResources(ItemType resType, int amt);
	
    bool HasResources(ItemType resType, int amt);
	
	bool IsChanged(){
		return hasChanged;
	}

	// -----------------------------------------------------------------
	// Resource Ratings
	void ClearResourceRating(ItemType itemType);
	void ClearResourceRatingAll();

    void SetResourceRating(WorldTypes::ItemType resType, float dist, float resAmt);
	void SetResourceRating(WorldTypes::ItemType resType, float dist, float resAmt, CellMath::ResourceRateFunc resFunc);

	// this could perhaps take a map of pair<ItemType, itemImportance>
	// but for now will just average
	void SetCombinedRating(vector<WorldTypes::ItemType> combineTypes);
	// -----------------------------------------------------------------
	// Resource Changers
	
	bool AddResource(ItemType resType, int amt);
	
	// this returns the amount that is removed if possible
	int RemoveResources(ItemType resType, int amt);
	
};


#endif /* defined(__AgentGOBGridTest__GridCell__) */
