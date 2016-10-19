//
//  WorldState.h
//  AgentGOAPActionsTestSimpler
//
//  Created by D J Clarke on 18/04/2015.
//
//

#ifndef __AgentGOAPActionsTestSimpler__WorldState__
#define __AgentGOAPActionsTestSimpler__WorldState__

#include <stdio.h>
#include "WorldTypes.h"
#include <iostream>
#include <vector>
#include "Goal.h"

using namespace WorldTypes;

class WorldState{
	mapCond conditions;
	
public:

    WorldState() = default;
    
    WorldState(mapCond conditions_);

    float GetRating();
    
    void SetCondition(string name, bool value);
    void SetCondition(pairCond pairIn);
    void SetCondition(mapCond mapIn);
	
	mapCond GetConditionsMap() const;
    pairCond GetConditionPair(string name) const;
	pairCond GetConditionPair(int index) const;
    
    bool GetConditionValue(string name) const;
    
    bool ConditionsContainPairMatch(pairCond pairConditionIn) const;
    
    bool ConditionsMatch(mapCond conditionsIn) const;
    
    bool SharesCondition(pairCond conditionIn) const;
    
    bool SharesCondition(mapCond conditionsIn) const;
	
	bool ContainsConditions(mapCond conditionsIn) const;
	
	int GetNumConditions() const;
    
    void PrintValues() const;
    
};
#endif /* defined(__AgentGOAPActionsTestSimpler__WorldState__) */
