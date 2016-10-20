//
//  MotivationsModule.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 30/06/2015.
//
//

#include "MotivationsModule.h"
#include "GridAgent.h"
#include "Utility.h"

MotivationsModule::MotivationsModule(){
	// GOALS
	//	primaryGoals = {
	//		new Goal("satisfyhunger", 0),
	//		new Goal("discover", 0),
	//	};
	goals = {
		
		new GoalSatisfyNeed("satisfyhunger", 0, CELL_FOOD),
		new GoalExplore("discover", 0),
		new GoalSatisfyNeed("getrested", 0, CELL_HOME),
		new GoalBuild("buildhome", 0, CELL_HOME),
		new GoalDestroyBuilding("destroyhome", 0, CELL_HOME),
		new GoalStoreResource("storefood", 0, CELL_FOOD),
		//				Goal("Store Wood", 0),
	};
	
	for(int i = 0; i < goals.size(); i++){
		mapGoals.insert(pair<string, Goal*>(goals[i]->GetName(), goals[i]));
	}
}

MotivationsModule::~MotivationsModule(){
	mapGoals.clear();
	Utility::ClearContainerPointers(goals);
}

void MotivationsModule::UpdateGoal(GridAgent* agent){
	UpdateGoalValidity(agent);
	
	// ------------------------------------------------------------
	// RELEVANCE
	
	// this could be replaced by a static function that gets all these values from somewhere else... then no need for these horrible implicit values
	// e.g. GoalRelevanceMaster::SetRelevance(mapGoals["Build Home"])
	// OR.. GoalRelevanceMaster::SetRelevance(GoalBuildHome) or
	

	for(int i = 0;i < goals.size(); ++i){
		goals[i]->UpdateRelevance(*agent);
		goals[i]->Update();
	}

}

void MotivationsModule::UpdateGoalValidity(GridAgent* agent){
	for(int i = 0;i < goals.size(); ++i){
		goals[i]->UpdateValidity (*agent);
	}
}


void MotivationsModule::SetGoalRelevance(string name, float value){
	mapGoals[name]->SetRelevance(value);
}

void MotivationsModule::ChangeGoalRelevance(string name, float changeValue){
	mapGoals[name]->ChangeRelevance(changeValue);
}

Goal MotivationsModule::GetTopGoal(){
	if(!goals.empty()){
		Goal* topGoal = goals[0];
		
		sort(goals.begin(), goals.end(), goalRelevanceComp);
		//		sort(mapGoals.begin(), mapGoals.end(), goalRelevanceCompMap); // not allowed apparently
		
		// reallocate mapGoals
		mapGoals.clear();
		for(int i = 0; i < goals.size(); i++){
			mapGoals.insert(pair<string, Goal*>(goals[i]->GetName(), goals[i]));
		}
		
		// return highest ranking valid goal
		for(int i = 0; i < goals.size(); i++){
			if(goals[i]->IsValid()){
				Goal goalOut = *goals[i];
				
				if(topGoal->GetName() != goalOut.GetName()){
					goalChanged = true;
				}
				// return goal at top of sorted vector
				return goalOut;
			}
		}
	}
	
	return *mapGoals.begin()->second;
}
