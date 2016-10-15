//
//  AgentAction.h
//  AgentGridActions
//
//  Created by D J Clarke on 03/03/2015.
//
//

#ifndef __AgentGridActions__AgentAction__
#define __AgentGridActions__AgentAction__

#include <stdio.h>
//#include "ofMain.h"
#include "ActionsRegister.h"
#include "WorldTypes.h"
#include "Utility.h"

class GridAgent;
class WorldState;
using namespace WorldTypes;

class TimedAction{
public:
	vector<pairCond> preConditions;
	vector<pairCond> postConditions;
    string name;
    
    virtual ~TimedAction(){}
	
	// shouldn't have this var? Move to next in hieracrchy
	int cost;
	float startTime, totalTime, expiryTime;
	
//	TimedAction(pairCond effect):
//	expiryTime(1),
//	startTime(ofGetElapsedTimef()),
//	cost(1)
//	{
//		AddEffect(effect);
//	}
	
	TimedAction(string name):
	expiryTime(1),
	startTime(ofGetElapsedTimef()),
	cost(1),
	name(name)
	{
		SetConditions(name);
//		AddEffect(effect);
	}


    // must be declared with the actual action implementation
    // and the effects on the agent
    virtual void Execute(GridAgent* agent) = 0;
    
    virtual bool TaskComplete(GridAgent* agent) = 0;
	
//    virtual bool IsComplete(GridAgent* agent) = 0;
	
	virtual bool IsValid(GridAgent* agent){
		return true;
	}
	
	// TODO: could be static and take action as arg also??
	virtual void GetWorldStateEffect(WorldState& state);
	
	// take function pointer?
	//	virtual void CalculateCost(){}
	
	// TODO: replace ofGet... with strategy?
	bool TimeComplete(){
		totalTime = ofGetElapsedTimef()-startTime;
		if(totalTime >= expiryTime){
			return true;
		}
		return false;
	}
	
	virtual bool IsComplete(GridAgent* agent){
		if(TaskComplete(agent) || TimeComplete()){
			return true;
		}
		return false;
	}
	
//	virtual bool CanSolveCondition(
	
	bool PostconsInState(WorldState& state) const;
	
//	int GetNumPrecons() const{
//		return preConditions.size();
//	}
	
	int GetNumPostcons() const{
		return postConditions.size();
	}
	
//	pairCond GetPrecon(int num) const{
//		pairCond pC = pairCond();
//		if(num < GetNumPrecons()){
//		pC = preConditions.at(num);
//		}
//		return pC;
//	}
	
	pairCond GetPostcon(int num) const{
		pairCond pC = pairCond();
		if(num < GetNumPostcons()){
			pC = postConditions.at(num);
		}
		return pC;
	}
	
	void AddEffect(pairCond effect);
    
    virtual void PrintConditions(){
//		int numPreCons = ActionsRegister::Instance()->ActionCountPreconditions(name);
		int numPostCons = ActionsRegister::Instance()->ActionCountPostconditions(name);
		
//		for(int i = 0; i < numPreCons; i++){
//        cout<<"PreCondition: "<<GetPrecon(i).first<<endl;
//		}
		for(int i = 0; i < numPostCons; i++){
        cout<<"PostCondition: "<<GetPostcon(i).first<<endl;
		}
    }
	
	
	void ClearConditions(){
//		preConditions.clear();
		postConditions.clear();
	}
	
private:
	// set action conditions from xml file
	// means conditions will not have to be written in new class
	// once specified in the XML with a matching ACTION:NAME field
	void SetConditions(string nameIn){
		ClearConditions();
		int numPreCons = ActionsRegister::Instance()->ActionCountPreconditions(nameIn);
		int numPostCons = ActionsRegister::Instance()->ActionCountPostconditions(nameIn);

		for(int i = 0; i < numPreCons; i++){
			preConditions.push_back(ActionsRegister::Instance()->GetPrecondition(nameIn.c_str(), i));
		}
		for(int i = 0; i < numPostCons; i++){
			postConditions.push_back(ActionsRegister::Instance()->GetPostcondition(nameIn.c_str(), i));
		}
	}

};

#endif /* defined(__AgentGridActions__AgentAction__) */
