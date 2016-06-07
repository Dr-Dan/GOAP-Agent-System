//
//  AgentBlackboard.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 18/05/2015.
//
//

#ifndef __AgentGOBGridTest__AgentBlackboard__
#define __AgentGOBGridTest__AgentBlackboard__

#include <stdio.h>
#include "MemoryModule.h"
#include "ofVec2f.h"
#include <map>

class AgentBlackboard{

public:
	AgentBlackboard();
	
	void UpdateFromMemory(MemoryModule* mMod);
	
	ofVec2f GetAgentPos(int agentId);
	map<int, ofVec2f> agentPosititions;
};
#endif /* defined(__AgentGOBGridTest__AgentBlackboard__) */
