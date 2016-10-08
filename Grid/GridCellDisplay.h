//
//  GridCellDisplay.h
//  agentGridProto
//
//  Created by D J Clarke on 09/07/2015.
//
//

#ifndef __agentGridProto__GridCellDisplay__
#define __agentGridProto__GridCellDisplay__

#include <stdio.h>
//#include "ofMain.h"
#include "ofColor.h"
#include "WorldTypes.h"
#include "GridValues.h"
#include "DisplayValues.hpp"
using namespace WorldTypes;

class GridCellDisplay{
	ofColor cellColor;
	ofColor cellOverlayColor;
	float overlayAlpha = 210;
	
	float hueFood = 28;
	float hueWood = 85;
	float hueHome = 0;
	
	ItemType cellType;
	void SetCellRatingColor(float rating, float hue);
	

public:
	ofColor GetColor() const{
		return cellColor;
	}
	
	ofColor GetOverlayColor () const {
		return cellOverlayColor;
	}

	void SetCellType(ItemType cellType){
		this->cellType = cellType;
		SetupDisplay();
	}
	
	void SetupDisplay();
	
	void UpdateOverlay(WorldTypes::OverlayType overlayType, mapRat& mapRatings, float combinedRating);
	
	// this is faster??? must be passing map is slow
	void UpdateOverlay(WorldTypes::OverlayType overlayType, float foodRat, float woodRat, float combinedRating);
	
	void UpdateOverlay(WorldTypes::OverlayType overlayType, float foodRat, float woodRat, float homeRat, float combinedRating);
	

};
#endif /* defined(__agentGridProto__GridCellDisplay__) */
