//
//  GridValues.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 19/04/2015.
//
//

#include "GridValues.h"

//const int GridValues::CELL_SIZE = 20;
const int GridValues::GRID_DIMS[2] = {30,30};
//const int GridValues::RATING_THRES = 3;
const GridValues::colourMap GridValues::CELL_COLOURS = GridValues::colourMap{
	std::make_pair(CELL_NEUTRAL, ofColor(255)),
	std::make_pair(CELL_FOOD, ofColor(220,160,0)),
	std::make_pair(CELL_WOOD, ofColor(255)),
	std::make_pair(CELL_HOME, ofColor(220,30,0)),
	std::make_pair(CELL_STORAGE, ofColor(220,30,160))
};
