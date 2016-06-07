//
//  Resource.h
//  agentGridProto
//
//  Created by D J Clarke on 19/07/2015.
//
//

#ifndef __agentGridProto__Resource__
#define __agentGridProto__Resource__

#include <stdio.h>
#include "WorldTypes.h"
#include "GridValues.h"
#include "ofMain.h"

// Next state info
// Could this just be some kind of resource class???
// should both sets of state values belong to same object
using namespace WorldTypes;

class Resource {
	// vars
	ItemType itemType;
	int amtRes;

public:
	Resource();
//	Resource(ItemType resType, int amtRes);
	
	void SetupResource(ItemType itemType);

	void SetupResource(ItemType itemType, int amtRes);
	
	void SetupResourceRandom(ItemType itemType);

	void ChangeResourceAmt(int amt);
	
	ItemType GetType() const;
	
	float GetAmtResource() const;


	// These should be in some sort of utility class???
	
	/*
	bool CanAddResources(ItemType resType, int amt);
	
	bool HasResources(ItemType resType, int amt);
	
	// -----------------------------------------------------------------
	// Resource Changers
	bool AddResource(ItemType resType, int amt);
	
	// this returns the amount that is removed if possible
	int RemoveResources(ItemType resType, int amt);
	*/
};
#endif /* defined(__agentGridProto__Resource__) */
