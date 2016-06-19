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
#include "WorldState.h"
#include "AgentAction.h"
#include "Goal.h"
#include <vector>
#include <list>
#include <iostream>
#include "Utility.h"
#include "GridAgentActions.h"
#include "actionTree.h"
#include "WorldTypes.h"

class GridAgent;

class ActionsModule{
	deque<TimedAction*> possibleActions; // is there a way to group these and use globally?
	
	Action* currentAction = NULL;
	
	Action* GetNextAction(GridAgent& agent);
	
	ActionTree* actionTree;
	
public:
	
	~ActionsModule();
	ActionsModule();
	
	void Update(GridAgent& agent);
	
	ActionTree* GetTree();
	
	void DoNextAction(GridAgent& agent);
	Action* GetCurrentAction();
	
	deque<TimedAction*> getPossibleActions(){
		return possibleActions;
	}
};
#endif /* defined(__AgentGOAPActionsTestSimpler__ActionsModule__) */
