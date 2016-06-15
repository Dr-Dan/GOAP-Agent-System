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
#include "ofMain.h"
#include "ActionsRegister.h"
#include "WorldTypes.h"
#include "Utility.h"

class GridAgent;
class WorldState;
using namespace WorldTypes;

class Action{
public:
	vector<pairCond> preConditions;
	vector<pairCond> postConditions;
    string name;
    
    virtual ~Action(){}
    
	Action():
	name("neutral action")
	{
        SetConditions(name);
    }
    
    Action(string name_):
    name(name_)
	{
	SetConditions(name);  // Load conditions from file
    }
    
    // must be declared with the actual action implementation
    // and the effects on the agent
    virtual void Execute(GridAgent* agent) = 0;
    
    virtual bool TaskComplete(GridAgent* agent) = 0;
    
    virtual bool IsComplete(GridAgent* agent) = 0;
	
	virtual bool IsValid(GridAgent* agent){
		return true;
	}
	
	virtual void GetWorldStateEffect(WorldState& state);
	
//	virtual bool CanSolveCondition(
	
	bool PostconsInState(WorldState& state) const;
	
	int GetNumPrecons() const{
		return preConditions.size();
	}
	
	int GetNumPostcons() const{
		return postConditions.size();
	}
	
	pairCond GetPrecon(int num) const{
		pairCond pC = pairCond();
		if(num < GetNumPrecons()){
		pC = preConditions.at(num);
		}
		return pC;
	}
	
	pairCond GetPostcon(int num) const{
		pairCond pC = pairCond();
		if(num < GetNumPostcons()){
			pC = postConditions.at(num);
		}
		return pC;
	}
    
    virtual void PrintConditions(){
		int numPreCons = ActionsRegister::Instance()->ActionCountPreconditions(name);
		int numPostCons = ActionsRegister::Instance()->ActionCountPostconditions(name);
		
		for(int i = 0; i < numPreCons; i++){
        cout<<"PreCondition: "<<GetPrecon(i).first<<endl;
		}
		for(int i = 0; i < numPostCons; i++){
        cout<<"PostCondition: "<<GetPostcon(i).first<<endl;
		}
    }
	
	
	void ClearConditions(){
		preConditions.clear();
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

class TimedAction: public Action{
	
public:
	// shouldn't have this var? Move to next in hieracrchy
    int cost;
    float startTime, totalTime, expiryTime;

    TimedAction(string name_, float expiryTime_):
    Action(name_),
    expiryTime(expiryTime_),
    startTime(ofGetElapsedTimef()),
    cost(1)
    {
    }
    
    TimedAction(string name_, float expiryTime_, int cost_):
    Action(name_),
    expiryTime(expiryTime_),
    startTime(ofGetElapsedTimef()),
    cost(cost_)
    {
    }

    virtual void Execute(GridAgent* agent) = 0;
    
    virtual bool TaskComplete(GridAgent* agent) = 0;
	
	// take function pointer?
//	virtual void CalculateCost(){}
	
	bool TimeComplete(){
        totalTime = ofGetElapsedTimef()-startTime;
        if(totalTime >= expiryTime){
            return true;
        }
        return false;
    }
    
	bool IsComplete(GridAgent* agent){
        if(TaskComplete(agent) || TimeComplete()){
            return true;
        }
        return false;
    }
};

//class LocationAction: public TimedAction{
//	float distance;
//	
//public:
//LocationAction(string name_, float expiryTime_):
//	TimedAction(name_, expiryTime_)
//	{
//	}
//	
//LocationAction(string name_, float expiryTime_, int cost_):
//	TimedAction(name_, expiryTime_, cost_)
//	{
//	}
//	
//	void SetDistance(ofVec2f agentPos, ofVec2f targetPos){
//		distance = Utility::GetGridDistance(agentPos, targetPos);
//	}
//	
//	//	void CalculateCost(){}
//
//};
#endif /* defined(__AgentGridActions__AgentAction__) */
