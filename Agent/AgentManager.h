//
//  AgentManager.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 17/04/2015.
//
//

#ifndef __AgentGOBGridTest__AgentManager__
#define __AgentGOBGridTest__AgentManager__

#include <stdio.h>
#include "GridAgent.h"
#include "ofVec2f.h"
#include "DisplayVisitor.h"
#include "GridValues.h"

class Grid;
class AgentManager{
    vector<GridAgent*> agents;
    ofVec2f gridDims;
	
public:
    
    int agentSize; // size of agent ellipse, should be stored elsewhere?

    ~AgentManager();
    AgentManager();
    
    AgentManager(ofVec2f gridDims_);
    AgentManager(ofVec2f gridDims_, int agentSize_);

    void UpdateAgents();
    void UpdateAgentsGridView(Grid& gridIn);
    void UpdateStepTime();
    
    GridAgent* GetAgent(int agentNo);
    
    // returns a vector containing all agents within a distance of given position
    vector<GridAgent*> GetNearbyAgents(const ofVec2f& callerPos, int distance);
    
    void AddAgent(ofVec2f pos_);
    
    void AddAgentsRandomPos(int numAgents);
    int GetNumAgents();
    void DisplayAgents();
};
#endif /* defined(__AgentGOBGridTest__AgentManager__) */
