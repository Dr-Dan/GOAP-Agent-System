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
#include "WorldTypes.h"

class GridAgent;

class GoalExplore: public Goal{
public:
	GoalExplore():Goal(){}
	
	GoalExplore(string name_):Goal(name_){}
	
	GoalExplore(string name_, int relevance):Goal(name_, relevance){}
	
	virtual void UpdateValidity(GridAgent& agent);
	virtual void UpdateRelevance(GridAgent& agent);
};

class GoalSatisfyNeed: public Goal{
	ItemType resType;
	
public:
	GoalSatisfyNeed():Goal(){}
	GoalSatisfyNeed(string name, ItemType res):
	Goal(name),
	resType(res){}
	GoalSatisfyNeed(string name, int relevance, ItemType res):
	Goal(name, relevance),
	resType(res){}
	
	virtual void UpdateValidity(GridAgent& agent);
	virtual void UpdateRelevance(GridAgent& agent);
};

class GoalBuild: public Goal{
	ItemType resType;
	
public:
	GoalBuild():Goal(){}
	
	GoalBuild(string name, ItemType res):
	Goal(name),
	resType(res){}
	
	GoalBuild(string name, int relevance, ItemType res):
	Goal(name, relevance),
	resType(res){}
	
	void UpdateValidity(GridAgent& agent);
	void UpdateRelevance(GridAgent& agent);
};

class GoalDestroyBuilding: public Goal{
	ItemType resType;
	
public:
	GoalDestroyBuilding():Goal(){}
	
	GoalDestroyBuilding(string name, ItemType res):
	Goal(name),
	resType(res){}
	
	GoalDestroyBuilding(string name, int relevance, ItemType res):
	Goal(name, relevance),
	resType(res){}
	
	void UpdateValidity(GridAgent& agent);
	void UpdateRelevance(GridAgent& agent);
};

class GoalStoreResource: public Goal{
	ItemType resType;
	
public:
	GoalStoreResource():Goal(){}
	
	GoalStoreResource(string name, ItemType res):
	Goal(name),
	resType(res){}
	
	GoalStoreResource(string name, int relevance, ItemType res):
	Goal(name, relevance),
	resType(res){}
	
	void UpdateValidity(GridAgent& agent);
	void UpdateRelevance(GridAgent& agent);
};

#endif /* GoalMore_hpp */
