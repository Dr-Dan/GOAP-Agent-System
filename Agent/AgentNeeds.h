//
//  AgentNeeds.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 03/06/2016.
//
//

#ifndef AgentNeeds_hpp
#define AgentNeeds_hpp

#include <stdio.h>
#include "WorldTypes.h"

using namespace WorldTypes;

struct NeedsStruct{
	
	NeedsStruct(){
		needLimit = 100;
		need = 0;
		needSatisfaction = 10;
	}
	
	NeedsStruct(int needLimit_){
		needLimit = needLimit_;
	}
	
	NeedsStruct(int need_, int needLimit_){
		need = need_;
		needLimit = needLimit_;
	}
	
	NeedsStruct(int need_, int needLimit_, int needSatisfaction_){
		need = need_;
		needLimit = needLimit_;
		needSatisfaction = needSatisfaction_;
	}
	
	NeedsStruct(int need_, int needLimit_, int needSatisfaction_, int needGrowthRate_){
		need = need_;
		needLimit = needLimit_;
		needSatisfaction = needSatisfaction_;
		needGrowthRate = needGrowthRate_;
	}
	
	NeedsStruct(int need_, int needLimit_, int needSatisfaction_, int needGrowthRate_, int needLossMult_){
		need = need_;
		needLimit = needLimit_;
		needSatisfaction = needSatisfaction_;
		needGrowthRate = needGrowthRate_;
		needLossRate = needLossMult_;
	}
	
	NeedsStruct(int need_, int needLimit_, int needSatisfaction_, int needGrowthRate_, int needLossMult_, int needUrgency_){
		need = need_;
		needLimit = needLimit_;
		needSatisfaction = needSatisfaction_;
		needGrowthRate = needGrowthRate_;
		needLossRate = needLossMult_;
		needUrgency = needUrgency_;
	}
	
	int need;
	int needUrgency, needLimit, needSatisfaction;
	int needLossRate, needGrowthRate; // multiply need shrinkage e.g. food will need to satisfy hunger faster than it grows
};

class AgentNeeds{
	typedef pair<ItemType, NeedsStruct> pairNeeds;
	map<ItemType, NeedsStruct> mapNeeds; // will later store all needs e.g. hunger
	
public:
	AgentNeeds();
	
	void UpdateNeed(ItemType needType);

	int GetNeedAmt(ItemType resType) const;

	int GetNeedGrowthAmt(ItemType needType) const;
	
	int GetNeedReductionAmt(ItemType needType) const;
	
	//	int GetMinHomeRating() const;
	// need this exist? or should UseResource be removed or somehow made more different
	// e.g. this for need, other for actual use e.g. building house
	void SatisfyNeed(ItemType needType, int mult=1);

	// ---------------------------------------------
	// Attribute state checking bools
	
	bool NeedIsUrgent(ItemType itemType);
	bool NeedIsSatisfied(ItemType itemType);
};
#endif /* AgentNeeds_hpp */
