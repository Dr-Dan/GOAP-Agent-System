//
//  GoalTypes.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 25/08/2016.
//
//

#ifndef GoalTypes_hpp
#define GoalTypes_hpp

#include <stdio.h>

namespace WorldTypes{
	enum MotivationType{
		GOAL_EXPLORE,
		GOAL_EAT,
//		GOAL_SLEEP,
//		GOAL_BUILD_HOUSE,

		
		ACTION_WANDER,
		ACTION_EAT
	};
	
	struct Condition{
		MotivationType type;
		bool state;
	};
}
#endif /* GoalTypes_hpp */
