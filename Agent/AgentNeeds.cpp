//
//  AgentNeeds.cpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 03/06/2016.
//
//

#include "AgentNeeds.h"
#include "ofMath.h"

AgentNeeds::AgentNeeds(){
	int hungerLimit = 70;
	int tirednessLimit = 70;
	int hungerUrgency = 50;
	int tirednessUrgency = 50;
	
	int hunger = (int)ofRandom(0, hungerLimit/2);
	int tiredness = (int)ofRandom(0, tirednessLimit/2);
	
	// setup needs
	// int need_, int needLimit_, int needSatisfaction_, int needGrowthRate_, int needLossMult_, int needUrgency_
	mapNeeds.insert(pairNeeds(CELL_FOOD, NeedsStruct(hunger, hungerLimit, 10, 2, 15, hungerUrgency)));
	mapNeeds.insert(pairNeeds(CELL_HOME, NeedsStruct(tiredness, tirednessLimit, 10, 1, 10, tirednessUrgency)));	
}

void AgentNeeds::UpdateNeed(ItemType needType){
	NeedsStruct* need = &mapNeeds[needType];
	if(need->need < 0){
		need->need = 0;
	}  else if(need->need > need->needLimit){
		need->need = need->needLimit;
	}
	else{
		need->need += need->needGrowthRate;
	}
}

int AgentNeeds::GetNeedAmt(ItemType resType) const{
	if(mapNeeds.count(resType)){
		return mapNeeds.at(resType).need;
	}
}

int AgentNeeds::GetNeedGrowthAmt(ItemType needType) const{
	return mapNeeds.at(needType).needGrowthRate;
}

int AgentNeeds::GetNeedReductionAmt(ItemType needType) const{
	return mapNeeds.at(needType).needLossRate;
}

// need this exist? or should UseResource be removed or somehow made more different
// e.g. this for need, other for actual use e.g. building house
void AgentNeeds::SatisfyNeed(ItemType needType, int mult){
	mapNeeds[needType].need -= mapNeeds[needType].needLossRate * mult;
}

// ---------------------------------------------
// Attribute state checking bools

bool AgentNeeds::NeedIsUrgent(ItemType itemType){
	if(mapNeeds[itemType].need >= mapNeeds[itemType].needUrgency){
		return true;
	}
	return false;
}

bool AgentNeeds::NeedIsUrgentAny(){
	for(pairNeeds need : mapNeeds){
	if(NeedIsUrgent(need.first)){
		return true;
	}
	}
	return false;
}

bool AgentNeeds::NeedIsSatisfied(ItemType itemType){
	if(mapNeeds[itemType].need <= mapNeeds[itemType].needSatisfaction){
		return true;
	}
	return false;
}
