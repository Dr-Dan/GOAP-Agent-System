//
//  NavigationModule.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 19/04/2015.
//
//

#include "NavigationModule.h"
#include "GridAgent.h"

// private
bool NavigationModule::IsAtTarget(ofVec2f posIn){
	if(targetDestination == posIn){
		//            targetDestination = ofVec2f();
		return true;
	}
	return false;
}

// public
bool NavigationModule::AgentAtTarget(GridAgent* agent){
    if(IsAtTarget(agent->moveModule.GetGridPos())){
        return true;
    }
    return false;
}

ofVec2f NavigationModule::GetTargetDestination(){
	return targetDestination;
}

bool NavigationModule::HasTarget(){
	if(hasTarget){
		return true;
	}
	return false;
}

void NavigationModule::ClearTarget(){
	hasTarget = false;
	targetDestination = ofVec2f();
}

void NavigationModule::SetTarget(ofVec2f posIn){
	targetDestination = posIn;
	hasTarget = true;
}