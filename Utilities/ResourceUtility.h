//
//  ResourceUtility.h
//  agentGridProto
//
//  Created by D J Clarke on 19/07/2015.
//
//

#ifndef __agentGridProto__ResourceUtility__
#define __agentGridProto__ResourceUtility__

#include <stdio.h>
#include <iostream>
#include "WorldTypes.h"
#include "GridValues.h"

using namespace WorldTypes;
class Resource;
class AgentAttributes;
class GridCell;
class GridAgent;

class ResourceUtility {
	
public:
	ResourceUtility();
	
	static bool CanAddResources(Resource* res, int amt);
	
	static bool HasResources(Resource* res, int amt);
	
	// -----------------------------------------------------------------
	// Resource Changers
	// Could return reminder if total deposit isn't possible?
	static bool AddResource(Resource* res, int amt);
	
	// this returns the amount that is removed if possible
	static int RemoveResources(Resource* res, int amt);
	
	// Agent-> Cell interaction
	static bool PickupResource(ItemType resType, float amt, AgentAttributes* attribs, GridCell* targetCell);
	static bool DepositResource(ItemType resType, float amt, AgentAttributes* attribs, GridCell* targetCell);
	static bool GiveResource(ItemType resType, float amt, AgentAttributes* attribs, GridAgent* agentOther);
};
#endif /* defined(__agentGridProto__ResourceUtility__) */
