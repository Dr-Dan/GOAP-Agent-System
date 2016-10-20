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


void GoalSatisfyNeed::UpdateValidity(GridAgent &agent){
	SetValidity(agent.memoryModule.KnowsOfCellType(resType));
}

void GoalSatisfyNeed::UpdateRelevance(GridAgent &agent){
	
	if(resType == CELL_HOME){
		if(agent.attributes.NeedIsUrgent(CELL_HOME) && agent.memoryModule.HasHome()){
			ChangeRelevance(1);
		}
		if(agent.attributes.NeedIsSatisfied(CELL_HOME)){
			SetRelevance(0);
		}
	} else {
		if(agent.attributes.NeedIsUrgent(resType)){
			ChangeRelevance(1);
		}
		
		if(agent.attributes.NeedIsSatisfied(resType)){
			SetRelevance(0);
		}
	}
}

// GOAL BUILD HOME
void GoalBuild::UpdateValidity(GridAgent& agent){
	if(resType == CELL_HOME){
		SetValidity(!agent.memoryModule.HasHome());
	}
}

void GoalBuild::UpdateRelevance(GridAgent& agent){
	if(resType == CELL_HOME){
		if(agent.attributes.NeedIsUrgent(CELL_HOME)
		   /* || !agent.memoryModule.HasHome()*/){
			SetRelevance(30);
		} else{
			SetRelevance(0);
		}
	}
}

// GOAL DESTROY HOME
void GoalDestroyBuilding::UpdateValidity(GridAgent& agent){
	if(resType == CELL_HOME){
		SetValidity(agent.memoryModule.ShouldDestroyHome());
	}
}

void GoalDestroyBuilding::UpdateRelevance(GridAgent& agent){
	if(resType == CELL_HOME){
		if(agent.memoryModule.HasHome() && agent.memoryModule.ShouldDestroyHome()){
			ChangeRelevance(1);
		} else{
			SetRelevance(0);
		}
	}
}

// GOAL STORE RESOURCE
void GoalStoreResource::UpdateValidity(GridAgent& agent){
	SetValidity(agent.memoryModule.KnowsOfCellType(CELL_STORAGE) &&
				agent.memoryModule.KnowsOfUnfilledStorage());
}

void GoalStoreResource::UpdateRelevance(GridAgent& agent){
	// food storage
	if(agent.memoryModule.KnowsOfCellType(CELL_STORAGE)){
		ChangeRelevance(10);
	} else{
		SetRelevance(0);
	}
}
