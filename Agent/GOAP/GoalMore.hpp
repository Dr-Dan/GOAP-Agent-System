//
//  GoalMore.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 25/08/2016.
//
//

#ifndef GoalMore_hpp
#define GoalMore_hpp

#include <stdio.h>
#include "Goal.h"
class GridAgent;

class GoalExplore: public Goal{
public:
	GoalExplore():Goal(){}
	
	GoalExplore(string name_):Goal(name_){}
	
	GoalExplore(string name_, int relevance):Goal(name_, relevance){}
	
	virtual void UpdateValidity(GridAgent& agent);
	virtual void UpdateRelevance(GridAgent& agent);
};

class GoalEat: public Goal{
public:
	GoalEat():Goal(){}
	
	GoalEat(string name_):Goal(name_){}
	
	GoalEat(string name_, int relevance):Goal(name_, relevance){}
	
	virtual void UpdateValidity(GridAgent& agent);
	virtual void UpdateRelevance(GridAgent& agent);
};

class GoalBuildHome: public Goal{
public:
	GoalBuildHome():Goal(){}
	
	GoalBuildHome(string name_):Goal(name_){}
	
	GoalBuildHome(string name_, int relevance):Goal(name_, relevance){}
	
	void UpdateValidity(GridAgent& agent);
	void UpdateRelevance(GridAgent& agent);
};

class GoalSleep: public Goal{
public:
	GoalSleep():Goal(){}
	
	GoalSleep(string name_):Goal(name_){}
	
	GoalSleep(string name_, int relevance):Goal(name_, relevance){}
	
	void UpdateValidity(GridAgent& agent);
	void UpdateRelevance(GridAgent& agent);
};


#endif /* GoalMore_hpp */
