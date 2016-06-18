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

using namespace WorldTypes;

class Resource {
	// vars
	ItemType itemType;
	int amtRes;

public:
	Resource();
	
	void SetupResource(ItemType itemType);

	void SetupResource(ItemType itemType, int amtRes);
	
	void SetupResourceRandom(ItemType itemType);

	void ChangeResourceAmt(int amt);
	
	ItemType GetType() const;
	
	float GetAmtResource() const;

};
#endif /* defined(__agentGridProto__Resource__) */
