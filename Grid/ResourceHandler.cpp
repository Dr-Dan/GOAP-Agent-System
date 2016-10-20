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
	int resExistsAt = -1;
	for(int i = 0; i < resourcesNext.size(); ++i){
		if(resourcesNext[i].GetType() == type){
			resExistsAt = i;
			break;
		}
	}
	
	if(resExistsAt != -1){
		resourcesNext[resExistsAt].SetResourceAmt(amtRes);
	} else{
		resourcesNext.push_back(Resource());
		resourcesNext.back().SetupResource(type, amtRes);
	}
}

void ResourceHandler::ClearResources(){
	resourcesNext.clear();
	resourcesCur.clear();
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

int ResourceHandler::GetAmtResource(WorldTypes::ItemType type) const{
	for(int i = 0; i < resourcesNext.size(); i++){
		if(resourcesNext[i].GetType() == type){
			return resourcesNext[i].GetAmtResource();
		}
	}
	return 0;
}

int ResourceHandler::GetAmtResourceTotal() const{
	int totalResources = 0;
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
	if(GetAmtResourceTotal() >= GridValues::MAX_RESOURCES){
		return true;
	}
	return false;
}

bool ResourceHandler::ContainsAnyResource(){
	if(resourcesNext.empty()){
		return false;
	}
	
	for(Resource res: resourcesNext){
		if(res.GetAmtResource() > 0){
			return true;
		}
	}
	return false;
}


bool ResourceHandler::CanAddResources(ItemType resType, int amt){
	if(GetAmtResourceTotal()   + amt <= GridValues::MAX_RESOURCES){
		return true;
	}
	//	cout<<"Cell: "<<GetId()<<" Is full of type "<<resType<<endl;
	return false;
}

bool ResourceHandler::HasResourceAmt(ItemType resType, int amt){
	if(CellContainsResource(resType) && GetAmtResource(resType) >= amt){
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


