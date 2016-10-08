//
//  DisplayValues.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 10/09/2016.
//
//

#ifndef DisplayValues_hpp
#define DisplayValues_hpp

#include <stdio.h>
#include "ofColor.h"
#include <map>
#include "WorldTypes.h"

using namespace WorldTypes;
class DisplayValues{
public:
	static const bool displayResText = false;
	
	static const bool displayRatText = false;
	
	typedef std::map<ItemType, ofColor> colourMap;
	static const colourMap CELL_COLOURS;
};
#endif /* DisplayValues_hpp */
