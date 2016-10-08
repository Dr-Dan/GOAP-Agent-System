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

//class GoalExplore: public Goal{
//public:
//	GoalExplore():Goal(){}
//	
////	GoalExplore(string name_):Goal(name_){}
//	
////	GoalExplore(string name_, int relevance):Goal(name_, relevance){}
//	
//	virtual void UpdateValidity(GridAgent& agent);
//	virtual void UpdateRelevance(GridAgent& agent);
//};

class GoalKnowsOfFood: public Goal{
public:
	GoalKnowsOfFood():Goal(){}
	GoalKnowsOfFood(pairCond effect):
	Goal(effect){}
	GoalKnowsOfFood(pairCond effect, pairCond precondition):
	Goal(effect, precondition){}
	
	virtual void UpdateValidity(GridAgent& agent);
	virtual void UpdateRelevance(GridAgent& agent);
};

class GoalBeAtFood: public Goal{
public:
	GoalBeAtFood():Goal(){}
	GoalBeAtFood(pairCond effect):
	Goal(effect){}
	GoalBeAtFood(pairCond effect, pairCond precondition):
	Goal(effect, precondition){}
	
	virtual void UpdateValidity(GridAgent& agent);
	virtual void UpdateRelevance(GridAgent& agent);
};

class GoalGetFood: public Goal{
public:
	GoalGetFood():Goal(){}
	GoalGetFood(pairCond effect):
	Goal(effect){}
	GoalGetFood(pairCond effect, pairCond precondition):
	Goal(effect, precondition){}
	
	virtual void UpdateValidity(GridAgent& agent){}
	virtual void UpdateRelevance(GridAgent& agent){}
};
class GoalEatFood: public Goal{
public:
	GoalEatFood():Goal(){}
	GoalEatFood(pairCond effect):
	Goal(effect){}
	GoalEatFood(pairCond effect, pairCond precondition):
	Goal(effect, precondition){}
	
	virtual void UpdateValidity(GridAgent& agent){}
	virtual void UpdateRelevance(GridAgent& agent){}
};


class GoalBeFull: public Goal{
public:
	GoalBeFull():Goal(){}
	GoalBeFull(pairCond effect):
	Goal(effect){}
	GoalBeFull(pairCond effect, pairCond precondition):
	Goal(effect, precondition){}
	
	virtual void UpdateValidity(GridAgent& agent);
	virtual void UpdateRelevance(GridAgent& agent);
};

class GoalRelax: public Goal{
public:
	GoalRelax():Goal(){}
	GoalRelax(pairCond effect):
	Goal(effect){}
	GoalRelax(pairCond effect, pairCond precondition):
	Goal(effect, precondition){}
	
	virtual void UpdateValidity(GridAgent& agent){}
	virtual void UpdateRelevance(GridAgent& agent);
};

class GoalBeIdle: public Goal{
public:
	GoalBeIdle():Goal(){}
	GoalBeIdle(pairCond effect):
	Goal(effect){}
	GoalBeIdle(pairCond effect, pairCond precondition):
	Goal(effect, precondition){}
	
	virtual void UpdateValidity(GridAgent& agent){}
	virtual void UpdateRelevance(GridAgent& agent){}
};
/*


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

*/
#endif /* GoalMore_hpp */
