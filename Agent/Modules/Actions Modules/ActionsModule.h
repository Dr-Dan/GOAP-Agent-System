//
//  ActionsModule.h
//  AgentGOAPActionsTestSimpler
//
//  Created by D J Clarke on 18/04/2015.
//
//

#ifndef __AgentGOAPActionsTestSimpler__ActionsModule__
#define __AgentGOAPActionsTestSimpler__ActionsModule__

#include <stdio.h>
#include <vector>
#include <list>
#include <iostream>

#include "WorldState.h"
#include "AgentAction.h"
#include "Goal.h"
#include "GridAgentActions.h"
#include "GOAPPlanner.h"
#include "WorldTypes.h"
#include "Utility.h"

class GridAgent;

class ActionsModule{
	static deque<TimedAction*> possibleActions; // is there a way to group these and use globally?
	
	Action* currentAction = NULL;
	
	Action* GetNextAction(GridAgent& agent);
	
	AIBase* planner;
	
public:
	
	~ActionsModule();
	ActionsModule();
	
	void Update(GridAgent& agent);
	
	AIBase* GetPlanner();
	
	void DoNextAction(GridAgent& agent);
	Action* GetCurrentAction();
	
	deque<TimedAction*> getPossibleActions(){
		return possibleActions;
	}
};
#endif /* defined(__AgentGOAPActionsTestSimpler__ActionsModule__) */
