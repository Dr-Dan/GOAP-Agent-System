//
//  GridCellDisplay.cpp
//  agentGridProto
//
//  Created by D J Clarke on 09/07/2015.
//
//

#include "GridCellDisplay.h"

void GridCellDisplay::SetupDisplay(){
	cellColor = GridValues::CELL_COLOURS.at(cellType);
}

void GridCellDisplay::UpdateOverlay(WorldTypes::OverlayType overlayType, mapRat& mapRatings, float combinedRating){
//	cellColor = ofColor(255);
	cellOverlayColor = ofColor(255, 0);
	
	float foodRat = mapRatings[CELL_FOOD];
	float woodRat = mapRatings[CELL_WOOD];

	if(overlayType == NO_OVERLAY){
		SetupDisplay();
	}
	 else if(overlayType == OVERLAY_FOOD){
		if(foodRat > 0.1){
			SetCellRatingColor(foodRat, hueFood);
		}
	} else if(overlayType == OVERLAY_WOOD){
		if(woodRat > 0.1){
			SetCellRatingColor(woodRat, hueWood);
		}
	} else if(overlayType == OVERLAY_AVG){
		cellOverlayColor.setHsb(0, 0,
								255-((155*(combinedRating/GridValues::MAX_RATING))), overlayAlpha);


	}
}

void GridCellDisplay::UpdateOverlay(WorldTypes::OverlayType overlayType, float foodRat, float woodRat, float combinedRating){
	//	cellColor = ofColor(255);
	cellOverlayColor = ofColor(255, 0);
	
	if(overlayType == NO_OVERLAY){
		SetupDisplay();
	}
	else if(overlayType == OVERLAY_FOOD){
		if(foodRat > 0.1){
			SetCellRatingColor(foodRat, hueFood);
		}
	} else if(overlayType == OVERLAY_WOOD){
		if(woodRat > 0.1){
			SetCellRatingColor(woodRat, hueWood);
		}
	} else if(overlayType == OVERLAY_AVG){
		cellOverlayColor.setHsb(0, 0,
								255-((155*(combinedRating/GridValues::MAX_RATING))), overlayAlpha);
		
		
	}
}

void GridCellDisplay::UpdateOverlay(WorldTypes::OverlayType overlayType, float foodRat, float woodRat, float homeRat, float combinedRating){
	//	cellColor = ofColor(255);
	cellOverlayColor = ofColor(255, 0);
	
	if(overlayType == NO_OVERLAY){
		SetupDisplay();
	}
	else if(overlayType == OVERLAY_FOOD){
		if(foodRat > 0.1){
			SetCellRatingColor(foodRat, hueFood);
		}
	} else if(overlayType == OVERLAY_WOOD){
		if(woodRat > 0.1){
			SetCellRatingColor(woodRat, hueWood);
		}
	} else if(overlayType == OVERLAY_HOME){
//		if(homeRat < -0.1){
			SetCellRatingColor(-homeRat, hueHome);
//		}
	} else if(overlayType == OVERLAY_AVG){
		cellOverlayColor.setHsb(0, 0,
								255-((155*(combinedRating/GridValues::MAX_RATING))), overlayAlpha);
		
		
	}
}

void GridCellDisplay:: SetCellRatingColor(float rating, float hue){
	
	float s = (200*(rating)/GridValues::MAX_RATING);
	float b = 255-(55*(rating)/GridValues::MAX_RATING);
	
//	cellColor.setHsb(hue, s, b);
	cellOverlayColor.setHsb(hue, s, b, overlayAlpha);
	
}