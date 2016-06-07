//
//  AgentAttributes.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 12/03/2015.
//
//

#ifndef __AgentGOBGridTest__AgentAttributes__
#define __AgentGOBGridTest__AgentAttributes__

#include <stdio.h>
//#include "ofMain.h"
#include "GridCell.h"
#include "WorldTypes.h"
#include "AgentNeeds.h"

using namespace WorldTypes;

class GridAgent;

class AgentAttributes{
	
	struct ItemCarried{
		int amtCarried;
		int maxCarried;
		int pickupAmt, dropAmt;
		
		ItemCarried(){
			amtCarried = 0;
			maxCarried = 20;
			pickupAmt = 3;
			dropAmt = 5;
		}
		
		ItemCarried(int maxCarried_){
			amtCarried = 0;
			maxCarried = maxCarried_;
			pickupAmt = 1;
			dropAmt = 5;
		}
		
		ItemCarried(int amtCarried_, int maxCarried_, int pickupAmt_){
			amtCarried = amtCarried_;
			maxCarried = maxCarried_;
			pickupAmt = pickupAmt_;
		}
		
		ItemCarried(int amtCarried_, int maxCarried_, int pickupAmt_, int dropAmt_){
			amtCarried = amtCarried_;
			maxCarried = maxCarried_;
			pickupAmt = pickupAmt_;
			dropAmt = dropAmt_;
		}
	};
	
	typedef pair<ItemType, ItemCarried> pairItemCarried;
	map<ItemType, ItemCarried> mapResources;
	
	static const int EAT_RATE = 1;
	
	AgentNeeds agentNeeds;
	
public:
	bool eating = false;
	bool foodFound = false;
	
	int minHomeRating = 5;
	
	AgentAttributes();
 
	// ---------------------------------------------
	// need bank of attribute inc/dec effects somewhere to use?
	void UpdateNeeds();
	
	//    void UpdateNeed(NeedsStruct& p_Ns);
	
	// ---------------------------------------------
	// Resource stuff
	
	int GetNeedAmt(ItemType resType) const;
	
	int GetResourceAmt(ItemType resType) const;
	bool HasResource(ItemType resName);
	
	// using bool as this may need to co-ordinate
	// with a function that reduces the amount in a cell
	
	int GetResourcePickupAmt(ItemType resType);
	
	int GetResourceDropAmt(ItemType resType);
	
	bool PickupResource(ItemType resName, int amt);
	
	bool CanPickupResource(ItemType resType, float amt);
	
	bool PickupResource(ItemType resType, float amt, GridCell* targetCellOther);
	bool DepositResource(ItemType resType, float amt, GridCell* targetCellOther);
	bool GiveResource(ItemType resType, float amt, GridAgent* agentOther);
	bool CanUseResource(ItemType resType, float amt);
	
	int GetResourceOrRemainder(ItemType resType, int amt);
	
	// ---------------------------------------------
	// action based functions
	int GetNeedGrowthAmt(ItemType needType) const;
	int GetNeedReductionAmt(ItemType needType) const;
	
	//	int GetMinHomeRating() const;
	// need this exist? or should UseResource be removed or somehow made more different
	// e.g. this for need, other for actual use e.g. building house
	void SatisfyNeed(ItemType needType);
	
	bool UseResource(ItemType resType);
	
	// ---------------------------------------------
	// Attribute state checking bools
	
	bool NeedIsUrgent(ItemType itemType);
	bool NeedIsSatisfied(ItemType itemType);
};
#endif /* defined(__AgentGOBGridTest__AgentAttributes__) */
