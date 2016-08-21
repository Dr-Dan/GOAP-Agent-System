//
//  MovementModule.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 05/05/2015.
//
//

#ifndef __AgentGOBGridTest__MovementModule__
#define __AgentGOBGridTest__MovementModule__

#include <stdio.h>
//#include "ofMain.h"
#include "ofVec2f.h"
#include "GridValues.h"

class GridAgent;
class MovementModule{
    ofVec2f gridSize;
    ofVec2f gridPos, nextGridPos, spd;
    int defSpd;
	
public:
    
    // -----------------------------------------------------
    // Other
    
    MovementModule() = default;
    
    MovementModule(ofVec2f startPos, int defSpd_);
    
    void Setup();
    
    void DoMovement();
    ofVec2f GetSpeedVecEdgeCollision();

    void LimitSpeedVec(ofVec2f& spdIn, int maxSpd);
    void HeadTowardsGridPos(ofVec2f targetPos);
    
    ofVec2f GetGridPos() const;
    
    void StopMovement();
    
    void SetSpd(ofVec2f newSpd);
};
#endif /* defined(__AgentGOBGridTest__MovementModule__) */
