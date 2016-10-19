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
		
		new Goal("satisfyhunger", 0),
		new Goal("discover", 0),
		new Goal("getrested", 0),
		new Goal("buildhome", 0),
//		new GoalBeIdle(pairCond("is waiting", 1)),
//		new GoalKnowsOfFood(pairCond("found food", 1)),
//		new GoalBeAtFood(pairCond("at food", 1), pairCond("found food", 1)),
//		new GoalGetFood(pairCond("has food", 1), pairCond("at food", 1)),
//		new GoalEatFood(pairCond("used food", 1), pairCond("has food", 1)),
//		new GoalEat("Eat Food", 0),
//		new GoalExplore("Explore", 1),

		
//
//				Goal("Store Food", 0),
//				Goal("Store Wood", 0),
//				Goal("Build Home", 0),
//				Goal("Destroy Home", 0)
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
	
	
	 // GoalBuildHome.SetRelevance(agentBB)  then...
	 // for(Goal g: goals){g.setRelevance(agentBB);}
	 if(agent->attributes.NeedIsUrgent(CELL_HOME) || !agent->memoryModule.HasHome()){
		SetGoalRelevance("buildhome", 30);
		//		SetGoalRelevance("Get Rested", 49);
	 } else{
		SetGoalRelevance("buildhome", 0);
	 }

	// eat
		if(agent->attributes.NeedIsUrgent(CELL_FOOD)){
			ChangeGoalRelevance("satisfyhunger", 1);
			SetGoalRelevance("discover", 0);
		}
	
		if(agent->attributes.NeedIsSatisfied(CELL_FOOD)){
			SetGoalRelevance("satisfyhunger", 0);
		}
	
	
	
	//	if(agent->memoryModule.HasHome() && knowsBetterCell){
	//		ChangeGoalRelevance("Destroy Home", 1);
	//		ChangeGoalRelevance("Explore", -1);
	//	} else{
	//		SetGoalRelevance("Destroy Home", 0);
	//	}
	
	// explore
	//	if(agent->attributes.NeedIsUrgent(CELL_FOOD) || agent->attributes.NeedIsUrgent(CELL_HOME) || agent->memoryModule.ShouldDestroyHome()){
	//		ChangeGoalRelevance("Explore", -2);
	//		//		mapGoals["Explore"]->SetChangeRate(-2);
	//		//		ChangeGoalRelevance("Store Food", -1);
	//	} else {
	//		ChangeGoalRelevance("Explore", 1);
	//	}
	
	
	 // sleep
	 if(agent->attributes.NeedIsUrgent(CELL_HOME) && agent->memoryModule.HasHome()){
		ChangeGoalRelevance("getrested", 1);
	 }
	 if(agent->attributes.NeedIsSatisfied(CELL_HOME)){
		SetGoalRelevance("getrested", 0);
	 }
	
	 /*
	 // food storage
	 if(agent->memoryModule.KnowsOfCellType(CELL_STORAGE)){
		ChangeGoalRelevance("Store Food", 10);
	 } else{
		SetGoalRelevance("Store Food", 0);
	 }
	 
	 // wood storage
	 if(agent->memoryModule.KnowsOfCellType(CELL_STORAGE)){
		ChangeGoalRelevance("Store Wood", 10);
	 } else{
		SetGoalRelevance("Store Wood", 0);
	 }
	 */
	
//	map<string, Goal*>::iterator i{mapGoals.begin()};
	
//	for(int i = 0;i < primaryGoals.size(); ++i){
//		primaryGoals[i]->UpdateRelevance(*agent);
//		primaryGoals[i]->Update();
//	}
//	
	
	for(int i = 0;i < goals.size(); ++i){
		goals[i]->UpdateRelevance(*agent);
		goals[i]->Update();
	}

	
	
//	for(pair<string, Goal*> g : mapGoals){
//		g.second->UpdateRelevance(*agent);
//		g.second->Update();
//	}
}

void MotivationsModule::UpdateGoalValidity(GridAgent* agent){
	/*
	 mapGoals.at("Build Home")->SetValidity(!agent->memoryModule.HasHome());
	 
	 mapGoals.at("Destroy Home")->SetValidity(agent->memoryModule.ShouldDestroyHome());
	 
	 mapGoals.at("Get Rested")->SetValidity(agent->memoryModule.HasHome());
	 
	 //	if(agent->memoryModule.KnowsOfCellType(CELL_STORAGE)){
	 mapGoals.at("Store Food")->SetValidity(agent->memoryModule.KnowsOfCellType(CELL_STORAGE) &&
	 agent->memoryModule.KnowsOfUnfilledStorage());
	 
	 mapGoals.at("Store Wood")->SetValidity(agent->memoryModule.KnowsOfCellType(CELL_STORAGE) &&
	 agent->memoryModule.KnowsOfUnfilledStorage());
	 */
	
	mapGoals.at("buildhome")->SetValidity(!agent->memoryModule.HasHome());

	mapGoals.at("getrested")->SetValidity(agent->memoryModule.HasHome());
	
	 //	if(agent->memoryModule.KnowsOfCellType(CELL_FOOD)){
	 mapGoals.at("satisfyhunger")->SetValidity(agent->memoryModule.KnowsOfCellType(CELL_FOOD));
	 
	
//	map<string, Goal*>::iterator i{mapGoals.begin()};
//	for(int i = 0;i < primaryGoals.size(); ++i){
//		primaryGoals[i]->UpdateValidity (*agent);
//	}
	
for(int i = 0;i < goals.size(); ++i){
	goals[i]->UpdateValidity (*agent);
	}
//	for(pair<string, Goal*> g : mapGoals){
//		g.second->UpdateValidity(*agent);
//	}
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
