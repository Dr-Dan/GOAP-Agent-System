//
//  TimeMaster.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 02/05/2015.
//
//

#include "TimeMaster.h"

long long TimeMaster::curMilli = 0;
long long TimeMaster::prevMilli = 0;
int TimeMaster::bufferIndex = 0;

void TimeMaster:: AddTimer(string name, int stepTimeMillis_){
	timers.insert(pairTimer(name, stepTimeMillis_));
	pMilliMap.insert(pairTimer(name, 0));
	Update(name);
}

//void TimeMaster::SetStepTime(int stepTimeMillis_){
//    stepTimeMillis = stepTimeMillis_;
//}

void TimeMaster::SetStepTime(string tmrName, int stepTimeMillis_){
	if(timers.count(tmrName)){
	timers[tmrName] = stepTimeMillis_;
	}
}

void TimeMaster::SetFromSystem(){
    curMilli = ofGetSystemTime();
}


long long TimeMaster:: GetCurrentTime(){
	SetFromSystem();
	return curMilli;
}


void TimeMaster:: Update(string tmrName){
	pMilliMap[tmrName] = curMilli;
}


bool TimeMaster::IsNextStep(string tmrName){
	if(pMilliMap[tmrName] + timers[tmrName] < curMilli){
		Update(tmrName);
		return true;
	}
	return false;
}

int TimeMaster::nextBufferIndex(){
	return 1 - bufferIndex;
}

//bool TimeMaster::IsNextStep(){
//    if(prevMilli+stepTimeMillis < curMilli){
//        Update();
//        return true;
//    }
//    return false;
//}

//void TimeMaster::Update(){
//	// update time counter
//	prevMilli = curMilli;
//}

