//
//  ActionsRegister.cpp
//  AgentGOAPActionsTestSimplerPointers
//
//  Created by D J Clarke on 26/04/2015.
//
//

#include "ActionsRegister.h"

ActionsRegister* ActionsRegister::actionsRegister = 0;

// ---------------------------------------------------------------
// PUBLIC
ActionsRegister* ActionsRegister:: Instance(){
	if(actionsRegister == 0){
		actionsRegister = new ActionsRegister;
	}
	return actionsRegister;
}

ActionsRegister::~ActionsRegister(){
	nameToPrecon.clear();
	nameToPostcon.clear();
	nameToGoalCon.clear();
	
	if(actionsRegister){
		delete actionsRegister;
		actionsRegister = NULL;
	}
}

ActionsRegister::ActionsRegister(){
	string message;
	//we load our settings file
	//if it doesn't exist we can still make one
	//by hitting the 's' key
	string filename = "actionInfo.xml";
	
	if(XML.loadFile(filename) ){
		message = filename + " loaded!";
	}else{
		message = "unable to load " + filename + "check data/ folder";
	}
	
	printf("%s\n", message.c_str());
	
	// calculate number of xml tags of given name for actions and goals
	XML.pushTag("ALLACTIONS");
	numActionTags = XML.getNumTags("ACTION");
	XML.popTag();
	
	XML.pushTag("ALLGOALS");
	numGoalTags = XML.getNumTags("GOAL");
	XML.popTag();
	
	//        printf("Num actions in file: %d\n\n", numActionTags);
	
	LoadConditions();
}

void ActionsRegister::LoadConditions(){
	XML.pushTag("ALLACTIONS");
	LoadActionConditions();
	XML.popTag();
	
	XML.pushTag("ALLGOALS");
	LoadGoalConditions();
	XML.popTag();
}

int ActionsRegister::ActionCountPreconditions(string actionName){
	int numCons = 0;
	
	if(nameToPrecon.count(actionName)){
	numCons =  nameToPrecon[actionName].size();
	}
	
	return numCons;
}

int ActionsRegister::ActionCountPostconditions(string actionName){
	int numCons = 0;
	
	if(nameToPostcon.count(actionName)){
		numCons =  nameToPostcon[actionName].size();
	}
	
	return numCons;
}

int ActionsRegister::GoalCountConditions(string goalName){
	int numCons = 0;
	
	if(nameToGoalCon.count(goalName)){
		numCons =  nameToGoalCon[goalName].size();
	}
	
	return numCons;
}


pairCond ActionsRegister::GetPrecondition(string actionName, int num){
	return nameToPrecon[actionName].at(num);
}

pairCond ActionsRegister::GetPostcondition(string actionName, int num){
	return nameToPostcon[actionName].at(num);
}

pairCond ActionsRegister::GetGoalCondition(string goalName, int num){
	return nameToGoalCon[goalName].at(num);
}

// ---------------------------------------------------------------
// PRIVATE

// NOTE
// code duplication alert!!!
void ActionsRegister::MapInsertPrecondition(string actionName){
	vector<pairCond> preConditions;
	int numConds = XML.getNumTags("PRECONDITION");

	
	if(XML.tagExists("PRECONDITION")){
		for(int i = 0; i < numConds; i++){
			XML.pushTag("PRECONDITION", i);
			
			pairCond preCondition;
			preCondition.first = XML.getValue("NAME", "");
			preCondition.second = XML.getValue("STATE", 1);
			preConditions.push_back(preCondition);
			XML.popTag();
		}
		
		nameToPrecon.insert(pair <string, vector<pairCond> >(actionName,preConditions));
	}
}


void ActionsRegister::MapInsertPostcondition(string actionName){
	vector<pairCond> postConditions;
	int numConds = XML.getNumTags("POSTCONDITION");
	
	if(XML.tagExists("POSTCONDITION")){
		for(int i = 0; i < numConds; i++){
			
			pairCond postCondition;
			
			XML.pushTag("POSTCONDITION");
			postCondition.first = XML.getValue("NAME", "");
			postCondition.second = XML.getValue("STATE", 1);
			postConditions.push_back(postCondition);
			XML.popTag();
		}
		nameToPostcon.insert(pair <string, vector<pairCond> >(actionName,postConditions));
	}
}

void ActionsRegister::MapInsertGoalCondition(string goalName){
	vector<pairCond> goalConditions;
	int numConds = XML.getNumTags("GOALCONDITION");
	
	
	if(XML.tagExists("GOALCONDITION")){
		for(int i = 0; i < numConds; i++){

		pairCond goalCondition;

		XML.pushTag("GOALCONDITION");
		goalCondition.first = XML.getValue("NAME", "");
		goalCondition.second = XML.getValue("STATE", 1);
		goalConditions.push_back(goalCondition);

		XML.popTag();
		}
		
		nameToGoalCon.insert(pair <string, vector<pairCond> >(goalName,goalConditions));
	}
}

void ActionsRegister::LoadActionConditions(){
	for(int i = 0; i < numActionTags; i++){
		XML.pushTag("ACTION", i);
		// set condition name
		//            pairCond preCondition, postCondition;
		
		string actionName = XML.getValue("NAME", "Neutral Action");
		
		
		MapInsertPrecondition(actionName);
		
		MapInsertPostcondition(actionName);
		
		XML.popTag();
		
	}
	
}

void ActionsRegister::LoadGoalConditions(){
	// loop for loading goal conditions
	for(int i = 0; i < numGoalTags; i++){
		XML.pushTag("GOAL", i);
		// set condition name
		//            pairCond goalCondition;
		
		string goalName = XML.getValue("NAME", "Neutral Goal");
		
		//            printf("name: %s\n", actionName.c_str());
		
		
		MapInsertGoalCondition(goalName);
		
		XML.popTag();
		
	}
}