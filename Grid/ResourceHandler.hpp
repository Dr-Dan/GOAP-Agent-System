//
//  ResourceHandler.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 16/06/2016.
//
//

#ifndef ResourceHandler_hpp
#define ResourceHandler_hpp

#include <stdio.h>

#include "WorldTypes.h"
#include "CellMath.h"
#include "Resource.h"
#include "ResourceUtility.h"
#include <vector>
#include <map>

using namespace std;
class ResourceHandler{
	
	// resources variables
//	bool isResource = false, isResourceNext = false;
	
//	mapRat mapRatings;
	// average of ratings. Does not take resource importance into account
	float combinedRating = 0 /*, combinedRatingNext*/;

	// stores max resource amounts
	map<ItemType, int> mapMaxRes;

	vector<Resource> resourcesCur, resourcesNext;
	
public:
	
	// CONSTRUCTOR
	ResourceHandler();
	ResourceHandler(ItemType resType);
	// -------------------------------------------------------------------------------
	// FUNCTIONS
	
	// -----------------------------------------------------------------
	// Setup
	void SetupResource(ItemType itemTypeIn, bool setRandom = false);
	void SetupResource(ItemType itemTypeIn, int amtRes, bool setRandom = false, bool reset = true);
	
	void SetupType(ItemType type);
	
	void AddResourceType(ItemType type, int amtRes=0);
	void ClearResources();
	
	void SwapStates();
	
	Resource* GetResource(WorldTypes::ItemType type);
	
	vector<Resource> GetResources() const;
	
	int GetAmtResource(WorldTypes::ItemType type) const;
	int GetAmtResourceTotal() const;
	
	
	// -------------------------------------------------------------------------------
	// RESOURCES
	
	// -----------------------------------------------------------------
	// Checkers
	
	bool CellContainsResource(ItemType resType);
	
	// sum all stored resources and compare against max capacity
	bool IsFull();
	bool ContainsAnyResource();
	
	bool CanAddResources(ItemType resType, int amt);
	
	bool HasResourceAmt(ItemType resType, int amt);
	bool HasNoResource(vector<Resource>& res, WorldTypes::ItemType type) const;
	
	bool HasResource() const;
	bool HasResourceNext() const;

	// -----------------------------------------------------------------

};
#endif /* ResourceHandler_hpp */
