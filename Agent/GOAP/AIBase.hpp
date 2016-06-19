//
//  AIBase.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 19/06/2016.
//
//

#ifndef AIBase_hpp
#define AIBase_hpp

#include <stdio.h>
#include <string>

class GridAgent;
class TimedAction;

class AIBase{
public:
	virtual TimedAction* GetAction(GridAgent& agent){}
	virtual void Update(GridAgent& agent){}
	virtual std::string ToString(){}
};
#endif /* AIBase_hpp */
