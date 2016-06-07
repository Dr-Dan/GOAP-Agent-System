//
//  NavigationModule.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 19/04/2015.
//
//

#ifndef __AgentGOBGridTest__NavigationModule__
#define __AgentGOBGridTest__NavigationModule__

#include <stdio.h>
#include "ofMain.h"

class GridAgent;

class NavigationModule{
	ofVec2f targetDestination;
	bool hasTarget = false;
	
	bool IsAtTarget(ofVec2f posIn);

public:
    
	ofVec2f GetTargetDestination();
	bool HasTarget();
	void ClearTarget();
	
	void SetTarget(ofVec2f posIn);
    bool AgentAtTarget(GridAgent* agent);
};
#endif /* defined(__AgentGOBGridTest__NavigationModule__) */
