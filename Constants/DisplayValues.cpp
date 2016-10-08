//
//  DisplayValues.cpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 10/09/2016.
//
//

#include "DisplayValues.hpp"

const DisplayValues::colourMap DisplayValues::CELL_COLOURS = DisplayValues::colourMap{
	std::make_pair(CELL_NEUTRAL, ofColor(255)),
	std::make_pair(CELL_FOOD, ofColor(220,160,0)),
	std::make_pair(CELL_WOOD, ofColor(255)),
	std::make_pair(CELL_HOME, ofColor(220,30,0)),
	std::make_pair(CELL_STORAGE, ofColor(220,30,160))
};
