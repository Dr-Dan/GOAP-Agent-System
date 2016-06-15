//
//  Player.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 09/06/2016.
//
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
//#include "AgentAttributes.h"
//#include "SensorModule.h"
//#include "MemoryModule.h"
//#include "StateModule.h"
//#include "MotivationsModule.h"
//#include "ActionsModule.h"
#include "NavigationModule.h"
#include "MovementModule.h"
#include "Entity.h"
#include "ofVec2f.h"

class Player:public Entity{
	NavigationModule navModule;
//	SensorModule sensorModule;
//	ActionsModule* actionsModule;
//	MemoryModule memoryModule;
	MovementModule moveModule;
//	MotivationsModule motiveModule;
//	StateModule stateModule;
//	AgentAttributes attributes;
	
public:
	
	void SetTargetPosition(ofVec2f targetPos);
	void Move();
};
#endif /* Player_hpp */
