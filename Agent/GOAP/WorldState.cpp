//
//  WorldState.cpp
//  AgentGOAPActionsTestSimpler
//
//  Created by D J Clarke on 18/04/2015.
//
//

#include "WorldState.h"

WorldState::WorldState(mapCond conditions_){
	SetCondition(conditions_);
}

float WorldState::GetRating(){
	float rating = 0;
	
	for(pairCond pC: conditions){
		if(pC.second == true){
			rating++;
		}
	}
	return rating;
}

void WorldState::SetCondition(string name, bool value){
	if(!conditions.count(name)){
		conditions.insert(pairCond(name, value));
		//            cout<<"Adding condition: "<<name<<" = "<<value<<endl;
	} else{
		conditions[name] = value;
		//            cout<<name<<" already exists!"<<endl;
	}
}

void WorldState::SetCondition(pairCond pairIn){
	SetCondition(pairIn.first, pairIn.second);
}

void WorldState::SetCondition(mapCond mapIn){
	for(pairCond pC : mapIn){
		SetCondition(pC);
	}
}

mapCond WorldState::GetConditionsMap() const{
	return conditions;
}


pairCond WorldState::GetConditionPair(string name) const{
	pairCond pairOut;
	if(conditions.count(name)){
		pairCond pairOut = pairCond(conditions.find(name)->first, conditions.find(name)->second);
	}
	return pairOut;
}

bool WorldState::GetConditionValue(string name) const{
	bool conditionStatus = false;
	if(conditions.count(name)){
		conditionStatus = conditions.at(name);
	} else {
		cout<<name<<" Not Found!!"<<endl;
	}
	return conditionStatus;
}

bool WorldState::ConditionsContainPairMatch(pairCond pairConditionIn) const{
	for(pairCond pC : conditions){
		if(pC.first == pairConditionIn.first && pC.second == pairConditionIn.second){
			return true;
		}
	}
	return false;
}

bool WorldState::ConditionsMatch(mapCond conditionsIn) const{
	if(conditions == conditionsIn){
		return true;
	}
	return false;
}

// TODO: check for already found conditions
bool WorldState::ContainsConditions(mapCond conditionsIn) const{
	int numFound = 0;
	int numConds = conditionsIn.size();
	
	for(pairCond condIn: conditionsIn){
		for(pairCond cond: conditions){
			if(cond == condIn){				
				numFound++;
		}
		}
	}

	if(numFound >= numConds){
		return true;
	}
	
	return false;
}

bool WorldState::SharesCondition(pairCond conditionIn) const{
	if(conditions.count(conditionIn.first) && conditions.at(conditionIn.first) == conditionIn.second){
		//                cout<<"Found::"<<pC.first<<endl;
		//                cout<<"Found2::"<<conditions.find(pC.first)->first<<endl;
		return true;
		
	}
	return false;
}

bool WorldState::SharesCondition(mapCond conditionsIn) const{
	for(pairCond pC : conditionsIn){
		if(conditions.count(pC.first) && conditions.at(pC.first) == pC.second){
			//                cout<<"Found::"<<pC.first<<endl;
			//                cout<<"Found2::"<<conditions.find(pC.first)->first<<endl;
			return true;
		}
	}
	return false;
}

void WorldState::PrintValues() const{
	for(pairCond pC: conditions){
		cout<<pC.first<<" = "<<pC.second<<endl;
	}
	cout<<"----------------"<<endl;
}