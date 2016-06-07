//
//  DisplayVisitor.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 19/04/2015.
//
//

#ifndef __AgentGOBGridTest__DisplayVisitor__
#define __AgentGOBGridTest__DisplayVisitor__

#include <stdio.h>
#include "ofMain.h"
#include "WorldTypes.h"

class GridAgent;
class GridCell;

class DisplayVisitor{

public:
    DisplayVisitor(){
        
    }
	
    static void Render(const GridAgent& agent);
    static void Render(const GridCell& cell);
    static void Render(const GridCell& cell, bool showNums, bool showingOverlay);
    static void Render(const string& text);

//	enum GridDisplayMode{
//		DRAW_OUTLINE,
//		NO_OUTLINE
//	};

};
#endif /* defined(__AgentGOBGridTest__DisplayVisitor__) */
