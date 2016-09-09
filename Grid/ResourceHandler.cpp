//
//  ResourceHandler.cpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 16/06/2016.
//
//

#include "ResourceHandler.hpp"
#include "ofMath.h"

ResourceHandler::ResourceHandler(){
	
}

ResourceHandler::ResourceHandler(ItemType resType){
	SetupType(resType);
}

void ResourceHandler::SetupType(ItemType type){
	SetupResource(type, true);
}

void ResourceHandler::AddResourceType(ItemType type, int amtRes){
	resourcesNext.push_back(Resource());
	resourcesNext.back().SetupResource(type, amtRes);
}

void ResourceHandler::ClearResources(){
	resourcesNext.clear();
}

void ResourceHandler::SwapStates(){
		resourcesCur = resourcesNext;
	}


// these both needn't exist?
void ResourceHandler::SetupResource(ItemType itemTypeIn, int amtRes, bool setRandom, bool reset){
	if(reset){
		ClearResources();
	}
	
	if(setRandom){
		AddResourceType(itemTypeIn, ofRandom(0,GridValues::MAX_RESOURCES));
	} else{
		AddResourceType(itemTypeIn, amtRes);
	}
}

void ResourceHandler::SetupResource(ItemType itemTypeIn, bool setRandom){
	SetupResource(itemTypeIn, 0, setRandom);
}

Resource* ResourceHandler::GetResource(WorldTypes::ItemType type){
	for(int i = 0; i < resourcesNext.size(); i++){
		if(resourcesNext[i].GetType() == type){
			return &resourcesNext[i];
		}
	}
}

vector<Resource> ResourceHandler:: GetResources() const{
	return resourcesNext;
}

float ResourceHandler::GetAmtResource(WorldTypes::ItemType type) const{
	for(int i = 0; i < resourcesNext.size(); i++){
		if(resourcesNext[i].GetType() == type){
			return resourcesNext[i].GetAmtResource();
		}
	}
	return 0;
}

float ResourceHandler::GetAmtResourceTotal() const{
	float totalResources = 0;
	for(int i = 0; i < resourcesNext.size(); i++){
			totalResources += resourcesNext[i].GetAmtResource();
	}
	
	return totalResources;
}


// -------------------------------------------------------------------------------
// RESOURCES

// -----------------------------------------------------------------
// Checkers

bool ResourceHandler::CellContainsResource(ItemType resType){
	if(!resourcesNext.empty()){
		for(int i = 0; i < resourcesNext.size(); i++){
			Resource cellRes = resourcesNext[i];
			if(cellRes.GetType() == resType && cellRes.GetAmtResource() > 0){
				return true;
			}
		}
	}
	return false;
}


bool ResourceHandler::IsFull(){
	int resTotal = 0;
	for(Resource res: resourcesNext){
		resTotal += res.GetAmtResource();
	}
	if(resTotal >= GridValues::MAX_RESOURCES){
		return true;
	}
	return false;
}


bool ResourceHandler::CanAddResources(ItemType resType, int amt){
	if(GetAmtResource(resType) + amt <= GridValues::MAX_RESOURCES){
		return true;
	}
	//	cout<<"Cell: "<<GetId()<<" Is full of type "<<resType<<endl;
	return false;
}

bool ResourceHandler::HasResources(ItemType resType, int amt){
	if(CellContainsResource(resType) && amt <= GetAmtResource(resType)){
		return true;
	}
	//	cout<<"Cell: "<<GetId()<<" Has no resources of type "<<resType<<endl;
	return false;
}

bool ResourceHandler::HasResource() const{
	if(!resourcesCur.empty()){
		return true;
	}
	return false;
}

bool ResourceHandler::HasResourceNext() const{
	if(!resourcesNext.empty()){
		return true;
	}
	return false;
}

bool ResourceHandler::HasNoResource(vector<Resource>& res, WorldTypes::ItemType type) const{
	if(!res.empty() &&
	   GetAmtResource(type) == 0){
		return true;
	}
	return false;
}

// -----------------------------------------------------------------
// Resource Changers

bool ResourceHandler::AddResource(ItemType resType, int amt) {
	return ResourceUtility::AddResource(GetResource(resType), amt);
}

int ResourceHandler::RemoveResources(ItemType resType, int amt){
	return ResourceUtility::RemoveResources(GetResource(resType), amt);
}

