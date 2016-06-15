//
//  WorldTypes.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 02/05/2015.
//
//

#ifndef __AgentGOBGridTest__WorldTypes__
#define __AgentGOBGridTest__WorldTypes__

#include <stdio.h>
#include <map>
#include <string>

using namespace std;

namespace WorldTypes{
    // -----------------------------------
    // enums
    
    enum GotoSpec{
        NEAREST_CELL = 0,
        NEAREST_RES,
		NEAREST_EMPTY,
		NEAREST_BUILD_LOC,
		NEAREST_OWNED_LOC,
        SPECIFIC
    };
    
    enum ItemType{
        AGENT = 0,
        CELL_NEUTRAL,
        CELL_FOOD,
        CELL_WOOD,
        CELL_HOME,
        CELL_STORAGE
    };
	
	
	enum OverlayType{
		NO_OVERLAY,
		OVERLAY_FOOD,
		OVERLAY_WOOD,
		OVERLAY_HOME,
		OVERLAY_AVG
	};
	
	// RATING_POP_DENSITY..?
//	enum RatingType{
//		RATING_FOOD,
//		RATING_WOOD,
//		RATING_AVG
//	};

    
    // -----------------------------------
    // types
    
    // containers for conditions and their state
    // used for actions and goals
    typedef map<string, bool> mapCond;
    typedef pair<string, bool> pairCond;
    
    // types for resources and relative amounts
    // used mainly in agent and cell classes
    typedef  map<ItemType, int> mapRes;
    typedef  pair<ItemType, int> pairRes;
	
	// types for resource ratings
	typedef  map<ItemType, float> mapRat;
	typedef  pair<ItemType, float> pairRat;
	
};
#endif /* defined(__AgentGOBGridTest__WorldTypes__) */
