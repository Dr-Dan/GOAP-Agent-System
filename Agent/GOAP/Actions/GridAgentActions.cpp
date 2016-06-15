//
//  GridAgentActions.cpp
//  AgentGridActions
//
//  Created by D J Clarke on 03/03/2015.
//
//

#include "GridAgentActions.h"
#include "GridAgent.h"
#include "ResourceUtility.h"

// -----------------------------------------------------------------
// ActionSleep

void ActionSleep::Execute(GridAgent* agent){
	agent->moveModule.StopMovement();
	
//	GridCell* currentCell = agent->sensorModule.GetCurrentCell(); // get agent's cell
	if(IsValid(agent)){
		agent->attributes.SatisfyNeed(CELL_HOME);
	}
}

bool ActionSleep::TaskComplete(GridAgent* agent){
	if(agent->attributes.NeedIsSatisfied(CELL_HOME)){
		return true;
	}
	return false;
}

bool ActionSleep::IsValid(GridAgent* agent){
	GridCell* currentCell = agent->sensorModule.GetCurrentCell(); // get agent's cell
		if(currentCell->GetType() == CELL_HOME){
			return true;
		}
	return false;
}



// -----------------------------------------------------------------
// ActionFindFood
// currently just wander, needs real implementation

void ActionWander::Execute(GridAgent* agent){
	//    agent->spd = ofVec2f((int)ofRandom(-2,2), (int)ofRandom(-2,2));
	/*
	 float tm = ofGetElapsedTimef();
	 
	 int noiseX = (ofNoise(tm * ofRandom(10)) - 0.5)*25;
	 int noiseY = (ofNoise(-tm * ofRandom(10)) - 0.5)*25;
	 
	 noiseX = ofClamp(noiseX, -1, 1);
	 noiseY = ofClamp(noiseY, -1, 1);
	 
	 //        cout<<"nX: "<< noiseX<<endl;
	 //        cout<<"nY: "<< noiseY<<endl<<endl;
	 
	 agent->moveModule.SetSpd(ofVec2f(noiseX, noiseY));
	 //    cout<<"Doing wander action"<<endl;
	 */
	
	ofVec2f targetCell = Utility::GetRandomGridPos();
	agent->moveModule.HeadTowardsGridPos(targetCell);
	
}

bool ActionWander::TaskComplete(GridAgent* agent){
	return false;
}
