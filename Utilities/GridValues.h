//
//  GridValues.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 19/04/2015.
//
//

// This class contains constants for use relative to the grid system

#ifndef __AgentGOBGridTest__GridValues__
#define __AgentGOBGridTest__GridValues__

#include <stdio.h>
#include <map>

class GridValues{
public:
	static const int CELL_SIZE{20};
	static const int AGENT_SIZE{18};
	
    static const int GRID_DIMS[2];
	static const int AGENT_VIEW_RADIUS{2};

	// for cells
	static const int MAX_RESOURCES{50};
	static const int MAX_RATING{20};
	
	static const int RATING_THRES{3};

	static const int CELL_CHANGE_DIST{0};
};

#endif /* defined(__AgentGOBGridTest__GridValues__) */
