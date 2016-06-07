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
    
    bool GetConditionValue(string name);
    
    bool ConditionsContainPairMatch(pairCond pairConditionIn);
    
    bool ConditionsMatch(mapCond conditionsIn);
    
    bool SharesCondition(pairCond conditionIn);
    
    bool SharesCondition(mapCond conditionsIn);
    
    void PrintValues() const;
    
};
#endif /* defined(__AgentGOAPActionsTestSimpler__WorldState__) */
