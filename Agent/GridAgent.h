//
//  GridAgent.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 24/02/2015.
//
//

#ifndef __AgentGOBGridTest__GridAgent__
#define __AgentGOBGridTest__GridAgent__

#include <stdio.h>
#include "ofMain.h"
#include "Entity.h"

#include "GridAgentActions.h"
#include "GridCell.h"
#include "GridValues.h"

#include "AgentAttributes.h"
#include "NavigationModule.h"
#include "SensorModule.h"
#include "MemoryModule.h"
#include "StateModule.h"
#include "MovementModule.h"
#include "MotivationsModule.h"
#include "ActionsModule.h"
#include <memory>

class GridAgent:public Entity{
    
public:
    NavigationModule navModule;
    SensorModule sensorModule;
    ActionsModule* actionsModule;
    MemoryModule memoryModule;
    MovementModule moveModule;
	MotivationsModule motiveModule;
	StateModule stateModule;
    AgentAttributes attributes;
    
//    int agentId;

    int agentSize = 0;
    
    bool isHoming = false;
    
    bool isTalking = false;

    // Constructors
    ~GridAgent(){
        if(actionsModule){
            delete actionsModule;
        }
    }
    
    GridAgent():Entity(){}
    
    GridAgent(ofVec2f startCell);
    
    // -----------------------------------------------------
    // Functions
    
    void Move();
    void Update();
    
    void DoCurrentAction();
    void ManageAttributes();
    
    
    // -----------------------------------------------------
    // Knowledge related
    
    // Cells
    void SetNearbyCells(vector<GridCell*> cellsNear);
    
    void SetNearbyAgents(vector<GridAgent*> agentsNear);
    
    void SetCurrentCell(GridCell* currentCellIn);
};
#endif /* defined(__AgentGOBGridTest__GridAgent__) */