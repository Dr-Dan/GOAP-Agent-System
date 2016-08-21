//
//  MotivationsModule.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 30/06/2015.
//
//

#ifndef __AgentGOBGridTest__MotivationsModule__
#define __AgentGOBGridTest__MotivationsModule__

#include <stdio.h>
#include "Goal.h"
//#include "ofMain.h"

class GridAgent;

static bool goalRelevanceComp(Goal a, Goal b){
	return a.GetRelevance() > b.GetRelevance();
}

static bool goalRelevanceCompMap(pair<string, Goal*> a, pair<string, Goal*> b){
	return a.second->GetRelevance() > b.second->GetRelevance();
}

class MotivationsModule{
	vector<Goal> goals;
	map<string, Goal*> mapGoals;
		
	bool goalChanged = false;
	
public:
	
	MotivationsModule();
	
	void UpdateGoal(GridAgent* agent);
	void SetGoalRelevance(string name, float value);
	void ChangeGoalRelevance(string name, float changeValue);
	Goal GetTopGoal();
	
};
#endif /* defined(__AgentGOBGridTest__MotivationsModule__) */
