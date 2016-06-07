//
//  MotivationsModule.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 30/06/2015.
//
//

#include "MotivationsModule.h"
#include "GridAgent.h"

MotivationsModule::MotivationsModule(){
	// ---------------------------------------
	// GOALS
	goals.push_back(Goal("Eat Food", 0));
	goals.push_back(Goal("Explore", 1, 20));
	goals.push_back(Goal("Get Rested", 0));
	
	goals.push_back(Goal("Store Food", 0, 30));
	goals.back().AddVitalCondition(pairCond("Carrying Food", 1));
	
	goals.push_back(Goal("Build Home", 0));
	goals.push_back(Goal("Destroy Home", 0, 30));
	
	for(int i = 0; i < goals.size(); i++){
		mapGoals.insert(pair<string, Goal*>(goals[i].GetName(), &goals[i]));
	}
}

void MotivationsModule::UpdateGoal(GridAgent* agent){

	// this all should be in a module
	bool knowsBetterCell = false;
	
	if(agent->memoryModule.HasHome()){
		int bestHomeId = agent->memoryModule.GetBestHomeCellId();
	
	if(agent->memoryModule.GetCellFact(bestHomeId)->GetCombinedRating() >
	   agent->memoryModule.GetCellFact(agent->memoryModule.GetCurrentHomeCellId())->GetCombinedRating()){
	 knowsBetterCell = agent->memoryModule.GetCurrentHomeCellId() != bestHomeId;
	}
	}
	
	bool shouldDestroyHome = agent->memoryModule.HasHome() && knowsBetterCell;
	
	// ------------------------------------------------------------
	// VALIDITY
	// create function to link goals in terms of validity
	//	if(agent->memoryModule.HasHome()){
//	mapGoals.at("Explore")->SetValidity(agent->memoryModule.HasHome() && !knowsBetterCell);

	mapGoals.at("Build Home")->SetValidity(!agent->memoryModule.HasHome()
										/* && agent->attributes.GetResourceAmt(CELL_WOOD) > HOME_BUILD_COST*/);
	
	mapGoals.at("Destroy Home")->SetValidity(shouldDestroyHome);
	
	mapGoals.at("Get Rested")->SetValidity(agent->memoryModule.HasHome());
	//	} else{
	//		mapGoals["Build Home"]->SetValidity(true);
	//		mapGoals["Get Rested"]->SetValidity(false);
	//	}
	
	//	if(agent->memoryModule.KnowsOfCellType(CELL_STORAGE)){
	mapGoals.at("Store Food")->SetValidity(agent->memoryModule.KnowsOfCellType(CELL_STORAGE));
	//	} else{
	//		mapGoals["Store Food"]->SetValidity(false);
	//	}
	
	//	if(agent->memoryModule.KnowsOfCellType(CELL_FOOD)){
	mapGoals.at("Eat Food")->SetValidity(agent->memoryModule.KnowsOfCellType(CELL_FOOD));
	//	} else{
	//		mapGoals["Eat Food"]->SetValidity(false);
	//	}
	
	// ------------------------------------------------------------
	// RELEVANCE

	
	if(agent->attributes.NeedIsUrgent(CELL_HOME) || !agent->memoryModule.HasHome()){
		SetGoalRelevance("Build Home", 50);
		//		SetGoalRelevance("Get Rested", 49);
	} else{
		SetGoalRelevance("Build Home", 0);
	}
	
	if(agent->memoryModule.HasHome() && knowsBetterCell){
		ChangeGoalRelevance("Destroy Home", 1);
//		ChangeGoalRelevance("Explore", -1);
	} else{
		SetGoalRelevance("Destroy Home", 0);
	}
	
	// explore
	if(agent->attributes.NeedIsUrgent(CELL_FOOD) || agent->attributes.NeedIsUrgent(CELL_HOME) || shouldDestroyHome){
		ChangeGoalRelevance("Explore", -2);
		//		mapGoals["Explore"]->SetChangeRate(-2);
		//		ChangeGoalRelevance("Store Food", -1);
	} else {
		ChangeGoalRelevance("Explore", 1);
	}
	
	// eat
	if(agent->attributes.NeedIsUrgent(CELL_FOOD)){
		ChangeGoalRelevance("Eat Food", 1);
	}
	if(agent->attributes.NeedIsSatisfied(CELL_FOOD)){
		SetGoalRelevance("Eat Food", 0);
	}
	
	// sleep
	if(agent->attributes.NeedIsUrgent(CELL_HOME) && agent->memoryModule.HasHome()){
		ChangeGoalRelevance("Get Rested", 1);
	}
	if(agent->attributes.NeedIsSatisfied(CELL_HOME)){
		SetGoalRelevance("Get Rested", 0);
	}
	
	// food storage
	if(agent->memoryModule.KnowsOfCellType(CELL_STORAGE)){
		ChangeGoalRelevance("Store Food", 10);
	} else{
		SetGoalRelevance("Store Food", 0);
	}
	
	// later
	//	for(pair<string, Goal*> g : mapGoals){
	//		g.second->UpdateRelevance();
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
		Goal* topGoal = &goals[0];
		
		sort(goals.begin(), goals.end(), goalRelevanceComp);
		//		sort(mapGoals.begin(), mapGoals.end(), goalRelevanceCompMap); // not allowed apparently
		
		// reallocate mapGoals
		mapGoals.clear();
		for(int i = 0; i < goals.size(); i++){
			mapGoals.insert(pair<string, Goal*>(goals[i].GetName(), &goals[i]));
		}
		
		// return highest ranking valid goal
		for(int i = 0; i < goals.size(); i++){
			if(goals[i].IsValid()){
				Goal goalOut = goals[i];
				
				if(topGoal->GetName() != goalOut.GetName()){
					goalChanged = true;
				}
				// return goal at top of sorted vector
				return goalOut;
			}
		}
	}
	
	return Goal();
}
