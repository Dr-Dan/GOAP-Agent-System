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
	virtual ~AIBase(){}
	virtual TimedAction* GetNextAction(GridAgent& agent)=0;
	virtual void Update(GridAgent& agent)=0;
	virtual std::string ToString()=0;
	// Display(DisplayThing* caller)
};
#endif /* AIBase_hpp */
