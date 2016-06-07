//
//  ActionsRegister.h
//  AgentGOAPActionsTestSimplerPointers
//
//  Created by D J Clarke on 26/04/2015.
//
//

// NOTE
// code duplication alert!!!
// could start using map with string to specify pre/post/goal-condition?

#ifndef __AgentGOAPActionsTestSimplerPointers__ActionsRegister__
#define __AgentGOAPActionsTestSimplerPointers__ActionsRegister__

#include <stdio.h>
#include "ofxXmlSettings.h"
#include "ofMain.h"
#include "WorldTypes.h"

using namespace WorldTypes;

class ActionsRegister{
//	typedef map<string, pairCond> mapStrToCon;
	typedef map<string, vector<pairCond> > mapStrToCon;
	
	mapStrToCon nameToPrecon;
	mapStrToCon nameToPostcon;
	mapStrToCon nameToGoalCon;
	
	ofxXmlSettings XML;
	
    int numActionTags = 0, numGoalTags = 0;

    static ActionsRegister* actionsRegister;
    
public:
    static ActionsRegister* Instance();

    ~ActionsRegister();
    
    ActionsRegister();
    
    // ---------------------------------------------------------------
    
    void LoadConditions();

	int ActionCountPreconditions(string actionName);
	int ActionCountPostconditions(string actionName);
	int GoalCountConditions(string goalName);
	
	pairCond GetPrecondition(string actionName, int num);
	pairCond GetPostcondition(string actionName, int num);
	pairCond GetGoalCondition(string goalName, int num);
	
	
private:
    void MapInsertPrecondition(string actionName);
    
    void MapInsertPostcondition(string actionName);
    void MapInsertGoalCondition(string goalName);
    
    void LoadActionConditions();
    void LoadGoalConditions();
};
#endif /* defined(__AgentGOAPActionsTestSimplerPointers__ActionsRegister__) */
