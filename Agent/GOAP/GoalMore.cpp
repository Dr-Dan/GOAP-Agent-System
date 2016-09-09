//
//  GoalMore.cpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 25/08/2016.
//
//

#include "GoalMore.hpp"
#include "GridAgent.h"

// GOAL EXPLORE
void GoalExplore::UpdateValidity(GridAgent& agent){
	// perhaps replace with ...CanMove()
	SetValidity(true);
}

void GoalExplore::UpdateRelevance(GridAgent& agent){
	if(agent.attributes.NeedIsUrgentAny()){
		SetRelevance(0);
	} else {
		ChangeRelevance(1);
	}
}

// GOAL EAT
void GoalEat::UpdateValidity(GridAgent& agent){
	SetValidity(agent.memoryModule.KnowsOfCellType(CELL_FOOD) ||
				agent.attributes.HasResource(CELL_FOOD));
}

void GoalEat::UpdateRelevance(GridAgent& agent){
	if(agent.attributes.NeedIsUrgent(CELL_FOOD)){
		ChangeRelevance(1);
	}
	
	if(agent.attributes.NeedIsSatisfied(CELL_FOOD)){
		SetRelevance(0);
	}
}

// GOAL BUILD HOME
void GoalBuildHome::UpdateValidity(GridAgent& agent){
	SetValidity(!agent.memoryModule.HasHome());
}

void GoalBuildHome::UpdateRelevance(GridAgent& agent){

}

// GOAL SLEEP
void GoalSleep::UpdateValidity(GridAgent& agent){
	SetValidity(agent.memoryModule.HasHome());
}

void GoalSleep::UpdateRelevance(GridAgent& agent){

}

