//
//  Resource.cpp
//  agentGridProto
//
//  Created by D J Clarke on 19/07/2015.
//
//

#include "Resource.h"
#include "ofMath.h"

Resource::Resource():
itemType(WorldTypes::CELL_NEUTRAL),
amtRes(0)
{
	
}

void Resource::SetupResource(ItemType itemType, int amtRes){
	this->itemType = itemType;
	this->amtRes = amtRes;
	
	amtRes = ofClamp(amtRes, 0, GridValues::MAX_RESOURCES);
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
