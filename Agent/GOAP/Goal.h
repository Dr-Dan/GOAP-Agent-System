//
//  Goal.h
//  AgentGOAPActionsTestSimpler
//
//  Created by D J Clarke on 18/04/2015.
//
//

#ifndef __AgentGOAPActionsTestSimpler__Goal__
#define __AgentGOAPActionsTestSimpler__Goal__

#include <stdio.h>
#include "GoalTypes.hpp"
#include "ActionsRegister.h"
#include "GridAgentActions.h"
//#include "ofMain.h"

//#include "WorldTypes.h"
//using namespace WorldTypes;

class GridAgent;
class Goal{
	float relevanceLimit{50};
	bool isValid = true;
	
	// VARS
	string name;
	float value;
	float relevance;
	float changeRate;
	
	
public:
	
	virtual ~Goal();
	// CONSTRUCTORS
	Goal();
	
	Goal(pairCond effect);
	
	Goal(pairCond effect, pairCond precondition);
	
//	Goal(string name_);
	
//	Goal(string name_, int relevance);
	
	// FUNCTIONS
	
	virtual void Update();
	
	string GetName() const;
	
	int GetNumCons() const;
	
	pairCond GetCondition(int num) const;
		
	virtual void UpdateRelevance(GridAgent& agent){}
	
	void SetRelevance(int newValue);
	
	float GetRelevance() const;
	
	void ChangeRelevance(float changeVal);

	void SetValidity(bool newValidity);
	
	virtual void UpdateValidity(GridAgent& agent){}

	void AddPrecondition(pairCond pair);
	void AddEffect(pairCond pair);

	bool IsValid();
	
	bool CanBeSolvedBy(Goal goal);
	bool CanBeSolvedBy(TimedAction action);
	bool CanBeSolvedBy(pairCond effect);

	vector<pairCond> preconditions;
	vector<pairCond> effects;
//protected:

	
//	void LoadConditions(string name_){
//		int numConds = ActionsRegister::Instance()->GoalCountConditions(name_);
//		
//		for(int i = 0; i < numConds; i++){
//			satisfactionConds.push_back(ActionsRegister::Instance()->GetGoalCondition(name_.c_str(), i));
//		}
//	}
};
#endif /* defined(__AgentGOAPActionsTestSimpler__Goal__) */

/*
	
 	void AddVitalCondition(pairCond condition);
 	bool HasVitalCondition();
 	vector<pairCond> GetVitalConditions();
	
*/