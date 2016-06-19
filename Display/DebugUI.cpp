//
//  DebugUI.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 27/04/2015.
//
//

#include "DebugUI.h"
//#include "WorldTypes.h"
#include "AgentManager.h"

DebugUI::DebugUI(){
    
}

DebugUI::DebugUI(AgentManager* aM){
	agentManager = aM;
}

void DebugUI::Display(){
	ofVec2f offset = ofVec2f();
	
	//    for(int i = 0; i < agentManager->GetNumAgents(); i++){
	for(int i = 0; i < 1; i++){
		string displayString = "";
		
		GridAgent* agent = agentManager->GetAgent(i);
		mapCond mC = agent->stateModule.GetCurrentState()->GetConditionsMap();
		string currentGoal = agent->motiveModule.GetTopGoal().GetName();
		Action* currentAction = agent->actionsModule->GetCurrentAction();
		string currentActionName = currentAction ? currentAction->name : "None";
		
		displayString += "ID: " + ofToString(agent->GetId()) + "\n";
		
		for(pairCond pC : mC){
			
			displayString += pC.first;
			displayString += " : ";
			displayString += ofToString(pC.second);
			displayString += "\n";
			
		}
		displayString += "Current Goal: " + currentGoal;
		displayString += " \nCurrent Action: " + currentActionName;
		displayString += " \nFood Held: " + ofToString(agent->attributes.GetResourceAmt(CELL_FOOD));
		displayString += " \nWood Held: " + ofToString(agent->attributes.GetResourceAmt(CELL_WOOD));
		displayString += " \nHunger: " + ofToString(agent->attributes.GetNeedAmt(CELL_FOOD));
		displayString += " \nTiredness: " + ofToString(agent->attributes.GetNeedAmt(CELL_HOME));
		
		ofDrawBitmapString(displayString, ofVec2f(500, 50 + offset.y));
		
		// draw goal planning 
		
		ofDrawBitmapString(agent->actionsModule->GetTree()->ToString(), ofVec2f(750,  offset.y));
		offset.y += 20* mC.size();
		//			cout<<agent->actionsModule->GetTree()->GetTreeString()<<endl;
		
	}
}


void DebugUI::DisplayFPS(){
	ofSetColor(0);
	ofFill();
	ofDrawBitmapString(ofToString(ofGetFrameRate(), 2), ofGetWindowWidth()-50, 20);
}