//
//  DebugUI.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 27/04/2015.
//
//

#ifndef __AgentGOBGridTest__DebugUI__
#define __AgentGOBGridTest__DebugUI__

#include <stdio.h>
#include "DisplayVisitor.h"
#include "ofMain.h"

class AgentManager;
class DebugUI{
	AgentManager* agentManager;

public:
    
    DebugUI();
    
    DebugUI(AgentManager* aM);
	
    void Display();
	void DisplayFPS();
//    void display(GridAgent* agent);
};

#endif /* defined(__AgentGOBGridTest__DebugUI__) */
