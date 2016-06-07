//
//  MovementModule.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 05/05/2015.
//
//

#include "MovementModule.h"
#include "GridAgent.h"

// -----------------------------------------------------
// Other

MovementModule::MovementModule(ofVec2f startPos, int defSpd_){
    gridPos = startPos;
    defSpd = defSpd_;
    Setup();
}

void MovementModule::Setup(){
    gridSize = ofVec2f(GridValues::GRID_DIMS[0],GridValues::GRID_DIMS[1]);
    spd = ofVec2f();
}

void MovementModule::DoMovement(){
    ofVec2f finalSpd = GetSpeedVecEdgeCollision();
    LimitSpeedVec(finalSpd, defSpd);
	
	nextGridPos = gridPos + finalSpd;
    gridPos += finalSpd;
}

ofVec2f MovementModule::GetSpeedVecEdgeCollision(){
    ofVec2f spdOut = ofVec2f();
    
    if(spd.x > 0){
        if(gridPos.x >= 0 && gridPos.x < gridSize.x-1){
            spdOut.x=spd.x;
        }
    } else if(spd.x < 0){
        if(gridPos.x > 0 && gridPos.x <= gridSize.x-1){
            spdOut.x=spd.x;
        }
    }
    
    if(spd.y > 0){
        if(gridPos.y >= 0 && gridPos.y < gridSize.y-1){
            spdOut.y=spd.y;
        }
    } else if(spd.y < 0){
        if(gridPos.y > 0 && gridPos.y <= gridSize.y-1){
            spdOut.y=spd.y;
        }
    }
    return spdOut;
}

void MovementModule::LimitSpeedVec(ofVec2f& spdIn, int maxSpd){
    int xSpd = ofClamp(spdIn.x, -maxSpd, maxSpd);
    int ySpd = ofClamp(spdIn.y, -maxSpd, maxSpd);
    
    spdIn.set(xSpd, ySpd);
}

ofVec2f MovementModule::GetGridPos() const{
    return gridPos;
}

void MovementModule::StopMovement(){
    spd.set(0);
}

void MovementModule::SetSpd(ofVec2f newSpd){
    spd = newSpd;
}

void MovementModule::HeadTowardsGridPos(ofVec2f targetPos){
    if(gridPos.x != targetPos.x){
        if(gridPos.x < targetPos.x){
            spd.x = defSpd;
        }
        if(gridPos.x > targetPos.x){
            spd.x = -defSpd;
        }
    } else{
        spd.x = 0;
    }
    
    if(gridPos.y != targetPos.y){
        
        if(gridPos.y < targetPos.y){
            spd.y = defSpd;
        }
        if(gridPos.y > targetPos.y){
            spd.y = -defSpd;
        }
    }
    else{
        spd.y = 0;
    }
}