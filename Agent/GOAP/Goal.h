//
//  Goal.h
//  AgentGOAPActionsTestSimpler
//
//  Created by D J Clarke on 18/04/2015.
//
//

#ifndef __AgentGOAPActionsTestSimpler__Goal__
#define __AgentGOAPActionsTestSimpler__Goal__

#include <stdio.h>
#include "ActionsRegister.h"
#include "ofMain.h"

//#include "WorldTypes.h"
//using namespace WorldTypes;

class Goal{
	float relevanceLimit;
	bool isValid = true;
	
	// VARS
	string name;
	float value;
	float relevance;
	float changeRate;
	
	
public:

	// CONSTRUCTORS
	Goal():
	relevance(1),
	relevanceLimit(50),
	name("Neutral Goal"),
	changeRate(1)
	{
		LoadConditions(name);
	}
	
	Goal(string name_):
	relevance(1),
	relevanceLimit(50),
	name(name_),
	changeRate(1)
	{
		LoadConditions(name);
	}
	
	Goal(string name_, int relevance):
	relevance(relevance),
	relevanceLimit(50),
	name(name_),
	changeRate(1)
	{
		LoadConditions(name);
	}
	
	Goal(string name_, int relevance, int relevanceLimit):
	relevance(relevance),
	relevanceLimit(relevanceLimit),
	name(name_),
	changeRate(1)
	{
		LoadConditions(name);
	}
	
	Goal(string name_, int relevance, int relevanceLimit, int changeRate):
	relevance(relevance),
	relevanceLimit(relevanceLimit),
	name(name_),
	changeRate(changeRate)
	{
		LoadConditions(name);
	}
	
	// FUNCTIONS
	
	string GetName(){
		return name;
	}
	
	int GetNumCons(){
		return satisfactionConds.size();
	}
	
	pairCond GetCondition(int num){
		pairCond pC = pairCond();
		if(num < GetNumCons()){
			pC = satisfactionConds.at(num);
		}
		return pC;
	}
	
	void SetChangeRate(int newRate){
		changeRate = newRate;
	}
	
	void UpdateRelevance(){
		ChangeRelevance(changeRate);
		relevance = ofClamp(relevance, 0, relevanceLimit);
	}
	
	void SetRelevance(int newValue){
		
			relevance = newValue;
		
		// remove this later...
		relevance = ofClamp(relevance, 0, relevanceLimit);

	}
	
	float GetRelevance(){
		return relevance;
	}
	
	void ChangeRelevance(float changeVal){
//		if(IsValid())
		relevance += changeVal;
		
//		limit relevance value
		relevance = ofClamp(relevance, 0, relevanceLimit);
		
	}
	
	void AddVitalCondition(pairCond condition){
		vitalConds.push_back(condition);
	}
	
	vector<pairCond> GetVitalConditions(){
		return vitalConds;
	}
	
	bool HasVitalCondition(){
		if(vitalConds.size() > 0){
			return true;
		}
		return false;
	}
	
	void SetValidity(bool newValidity){
		isValid = newValidity;
	}

	bool IsValid(){
		return isValid;
	}
private:
	vector<pairCond> satisfactionConds;
	vector<pairCond> vitalConds; // conditions vital to goal completion
	
	void LoadConditions(string name_){
		int numConds = ActionsRegister::Instance()->GoalCountConditions(name_);
		
		for(int i = 0; i < numConds; i++){
			satisfactionConds.push_back(ActionsRegister::Instance()->GetGoalCondition(name_.c_str(), i));
		}
	}
};
#endif /* defined(__AgentGOAPActionsTestSimpler__Goal__) */
