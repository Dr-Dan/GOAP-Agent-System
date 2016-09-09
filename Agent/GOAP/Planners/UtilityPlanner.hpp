//
//  UtilityPlanner.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 24/08/2016.
//
//

#ifndef UtilityPlanner_hpp
#define UtilityPlanner_hpp

#include <stdio.h>
#include "AIBase.hpp"

class UtilityPlanner: public AIBase{
public:
	TimedAction* GetNextAction(GridAgent& agent);
	void Update(GridAgent& agent);
	std::string ToString();
};
#endif /* UtilityPlanner_hpp */
