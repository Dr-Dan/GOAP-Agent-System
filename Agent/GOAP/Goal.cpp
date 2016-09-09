//
//  Goal.cpp
//  AgentGOAPActionsTestSimpler
//
//  Created by D J Clarke on 18/04/2015.
//
//

#include "Goal.h"
#include "GridAgent.h"
#include <cmath>

Goal::Goal():
relevance(1),
name("Neutral Goal"),
changeRate(1)
{
	LoadConditions(name);
}

Goal::Goal(string name_):
relevance(1),
name(name_),
changeRate(1)
{
	LoadConditions(name);
}

Goal::Goal(string name_, int relevance):
relevance(relevance),
name(name_),
changeRate(1)
{
	LoadConditions(name);
}

Goal::~Goal(){
	satisfactionConds.clear();
	vitalConds.clear();
}

// FUNCTIONS
void Goal::Update(){
//	ChangeRelevance(changeRate);
	relevance = ofClamp(relevance, 0, relevanceLimit);
}

string Goal::GetName() const{
	return name;
}

int Goal::GetNumCons() const{
	return satisfactionConds.size();
}

pairCond Goal::GetCondition(int num) const{
	pairCond pC = pairCond();
	if(num < GetNumCons()){
		pC = satisfactionConds.at(num);
	}
	return pC;
}



void Goal::SetRelevance(int newValue){
	
	relevance = newValue;
	// remove this later...
	relevance = ofClamp(relevance, 0, relevanceLimit);
	
}

float Goal::GetRelevance() const{
	return relevance;
}

void Goal::ChangeRelevance(float changeVal){
	//		if(IsValid())
	relevance += changeVal;
	
	//		limit relevance value
	relevance = ofClamp(relevance, 0, relevanceLimit);
	
}


void Goal::SetValidity(bool newValidity){
	isValid = newValidity;
}

bool Goal::IsValid(){
	return isValid;
}

/*
void Goal::AddVitalCondition(pairCond condition){
	vitalConds.push_back(condition);
}

vector<pairCond> Goal::GetVitalConditions(){
	return vitalConds;
}

bool Goal::HasVitalCondition(){
	if(vitalConds.size() > 0){
		return true;
	}
	return false;
//}
 
 
 //void Goal::SetChangeRate(int newRate){
 //	changeRate = newRate;
 //}
*/