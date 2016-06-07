//
//  Resource.cpp
//  agentGridProto
//
//  Created by D J Clarke on 19/07/2015.
//
//

#include "Resource.h"

Resource::Resource():
itemType(WorldTypes::CELL_NEUTRAL),
amtRes(0)
{
	
}

void Resource::SetupResource(ItemType itemType, int amtRes){
	this->itemType = itemType;
	this->amtRes = amtRes;
	
	amtRes = ofClamp(amtRes, 0, GridValues::MAX_RESOURCES);
	
//	return *this;
}

void Resource::SetupResource(ItemType itemType){
	return SetupResource(itemType, 0);
}

void Resource::SetupResourceRandom(ItemType itemType){
	return SetupResource(itemType, ofRandom(0,GridValues::MAX_RESOURCES));
}

void Resource::ChangeResourceAmt(int amt){
	amtRes += amt;
}


ItemType Resource::GetType() const{
	return itemType;
}

float Resource::GetAmtResource() const{
	return amtRes;
}

/*
bool Resource::CanAddResources(ItemType resType, int amt){
	if(amtRes+ amt <= GridValues::MAX_RESOURCES){
		return true;
	}
	//	cout<<"Cell: "<<GetId()<<" Is full of type "<<resType<<endl;
	return false;
}

bool Resource::HasResources(ItemType resType, int amt){
	if(amt <= amtRes){
		return true;
	}
	//	cout<<"Cell: "<<GetId()<<" Has no resources of type "<<resType<<endl;
	return false;
}



// -----------------------------------------------------------------
// Resource Changers

bool Resource::AddResource(ItemType resType, int amt) {
	if(CanAddResources(resType, amt)){
		amtRes += amt;
		return true;
	}
	return false;
}

int Resource::RemoveResources(ItemType resType, int amt){
	if(HasResources(resType, amt)){
		amtRes-=amt;
		return amt; // if it has the resources, return demanded amount
	} else if(!HasResources(resType, amt) && amtRes != 0){
		int remainder = amtRes; // take what is left from resources
		amtRes = 0; // resources now empty
		return remainder; // else return remainder
	}
	
	return 0;
}
*/