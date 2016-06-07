//
//  AgentAttributes.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 12/03/2015.
//
//

#include "AgentAttributes.h"
#include "GridAgent.h"
#include "ofMath.h"

AgentAttributes::AgentAttributes(){
	int hungerLimit = 70;
	int tirednessLimit = 70;
	int hungerUrgency = 50;
	int tirednessUrgency = 50;
	
	int hunger = (int)ofRandom(0, hungerLimit/2);
	int tiredness = (int)ofRandom(0, tirednessLimit/2);
	
	// setup possible starting resource stuff
	mapResources.insert(pairItemCarried(CELL_FOOD, ItemCarried()));
	mapResources.insert(pairItemCarried(CELL_WOOD, ItemCarried()));
}


// ---------------------------------------------
// need bank of attribute inc/dec effects somewhere to use?
void AgentAttributes::UpdateNeeds(){
	agentNeeds.UpdateNeed(CELL_FOOD);
	agentNeeds.UpdateNeed(CELL_HOME);
}

// ---------------------------------------------
// Resource stuff

int AgentAttributes::GetNeedAmt(ItemType resType) const{
	return agentNeeds.GetNeedAmt(resType);
}

int AgentAttributes::GetResourceAmt(ItemType resType) const{
	return mapResources.at(resType).amtCarried;
}

bool AgentAttributes::HasResource(ItemType resName){
	if(mapResources.count(resName)){
		if (mapResources[resName].amtCarried > 0) {
			return true;
		}
	}
	return false;
}

int AgentAttributes::GetResourcePickupAmt(ItemType resType){
	if(mapResources.count(resType)){
		return mapResources[resType].pickupAmt;
	}
	cout<<"Resource Not Found"<<endl;
	return 0;
}

int AgentAttributes::GetResourceDropAmt(ItemType resType){
	if(mapResources.count(resType)){
		return GetResourceOrRemainder(resType, mapResources[resType].dropAmt);
	}
	cout<<"Resource Not Found"<<endl;
	return 0;
}

bool AgentAttributes::PickupResource(ItemType resName, int amt){
	if(CanPickupResource(resName, amt)){
		mapResources[resName].amtCarried += amt;
		//		cout<<"food!"<<endl;
		return true;
	}
	return false;
}

bool AgentAttributes::CanPickupResource(ItemType resType, float amt){
	if(mapResources[resType].amtCarried + amt <= mapResources[resType].maxCarried){
		return true;
	}
	return false;
}

bool AgentAttributes::PickupResource(ItemType resType, float amt, GridCell* targetCellOther){
	if(CanPickupResource(resType, amt)){
		mapResources[resType].amtCarried += targetCellOther->RemoveResources(resType, amt);
		return true;
	}
	cout<<"I can't take more resources"<<endl;
	return false;
}

bool AgentAttributes::DepositResource(ItemType resType, float amt, GridCell* targetCellOther){
	if(CanUseResource(resType, amt)){
		bool can_deposit = targetCellOther->AddResource(resType, amt);
		if(can_deposit){
			mapResources[resType].amtCarried -= amt;
			return true;
		}
	}
	cout<<"I don't have the resources"<<endl;
	return false;
}

bool AgentAttributes::GiveResource(ItemType resType, float amt, GridAgent* agentOther){
	if(CanUseResource(resType, amt)){
		if(agentOther->attributes.PickupResource(resType, amt)){
			return true;
		}
	}
	cout<<"I don't have the resources"<<endl;
	return false;
}

bool AgentAttributes::CanUseResource(ItemType resType, float amt){
	if(amt <= mapResources[resType].amtCarried &&
	   amt > 0){
		return true;
	}
	//    cout<<amt<<" is too many resources"<<endl;
	return false;
}


int AgentAttributes::GetResourceOrRemainder(ItemType resType, int amt){
	if(CanUseResource(resType, amt)){
		return amt; // if it has the resources, return demanded amount
	} else if(!CanUseResource(resType, amt) && mapResources[resType].amtCarried != 0){
		int remainder = mapResources[resType].amtCarried; // take what is left from resources
		return remainder; // else return remainder
	}
	return 0;
}

// ---------------------------------------------
// action based functions
int AgentAttributes::GetNeedGrowthAmt(ItemType needType) const{
	return agentNeeds.GetNeedGrowthAmt(needType);
}

int AgentAttributes::GetNeedReductionAmt(ItemType needType) const{
	return agentNeeds.GetNeedReductionAmt(needType);
}

// need this exist? or should UseResource be removed or somehow made more different
// e.g. this for need, other for actual use e.g. building house
void AgentAttributes::SatisfyNeed(ItemType needType){
	agentNeeds.SatisfyNeed(needType);
}

bool AgentAttributes::UseResource(ItemType resType){
	int amtToUse = GetResourceOrRemainder(resType, EAT_RATE);
	mapResources[resType].amtCarried -= amtToUse;
	agentNeeds.SatisfyNeed(resType, amtToUse);
}

// ---------------------------------------------
// Attribute state checking bools
bool AgentAttributes::NeedIsUrgent(ItemType itemType){
	return agentNeeds.NeedIsUrgent(itemType);
}

bool AgentAttributes::NeedIsSatisfied(ItemType itemType){
	return agentNeeds.NeedIsSatisfied(itemType);;
}

//int AgentAttributes:: GetMinHomeRating() const{
//	return minHomeRating;
//}

