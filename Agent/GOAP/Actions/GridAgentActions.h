//
//  GridActions.h
//  AgentGridActions
//
//  Created by D J Clarke on 03/03/2015.
//
//

#ifndef __AgentGridActions__GridAgentActions__
#define __AgentGridActions__GridAgentActions__

#include <stdio.h>
#include "AgentAction.h"
#include "ofMain.h"
#include "WorldTypes.h"
class GridAgent;

class ActionGoto: public TimedAction{
protected:
    WorldTypes::ItemType gotoType;
    WorldTypes::GotoSpec gotoSpec;
    
public:
    ActionGoto(string name_, float expiryTime_, ItemType gotoType_, GotoSpec gotoSpec_):
    TimedAction(name_, expiryTime_),
    gotoType(gotoType_),
    gotoSpec(gotoSpec_)
    {
        //SetConditions(name);
    }
    
    ActionGoto(string name_, float expiryTime_, float cost_, ItemType gotoType_, GotoSpec gotoSpec_):
    TimedAction(name_, expiryTime_, cost_),
    gotoType(gotoType_),
    gotoSpec(gotoSpec_)
    {
        //SetConditions(name);
    }
    
	void Execute(GridAgent* agent);
    
	bool TaskComplete(GridAgent* agent);
    
};

class ActionUseCell: public TimedAction{
protected:
    WorldTypes::ItemType cellType;
    
public:
    ActionUseCell(string name_, float expiryTime_, ItemType cellType_):
    TimedAction(name_, expiryTime_),
    cellType(cellType_)
    {
        //SetConditions(name);
    }
    
    ActionUseCell(string name_, float expiryTime_, float cost_, ItemType cellType_):
    TimedAction(name_, expiryTime_, cost_),
    cellType(cellType_)
    {
        //SetConditions(name);
    }
    
     void Execute(GridAgent* agent);
    
     bool TaskComplete(GridAgent* agent);
};

class ActionChangeCell: public TimedAction{
protected:
	WorldTypes::ItemType targetType;
	
public:
	ActionChangeCell(string name_, float expiryTime_, ItemType targetType_):
	TimedAction(name_, expiryTime_),
	targetType(targetType_)
	{
	}
	
	ActionChangeCell(string name_, float expiryTime_, float cost_, ItemType targetType_):
	TimedAction(name_, expiryTime_, cost_),
	targetType(targetType_)
	{
	}
	
	void Execute(GridAgent* agent);
	
	bool TaskComplete(GridAgent* agent);
};

class ActionUseCarriedResource: public TimedAction{
protected:
    WorldTypes::ItemType cellType;

public:
    ActionUseCarriedResource(string name_, float expiryTime_, ItemType cellType_):
    TimedAction(name_, expiryTime_),
    cellType(cellType_)
    {
        //SetConditions(name);
    }
    
    ActionUseCarriedResource(string name_, float expiryTime_, float cost_, ItemType cellType_):
    TimedAction(name_, expiryTime_, cost_),
        cellType(cellType_)
    {
        //SetConditions(name);
    }
    
     void Execute(GridAgent* agent);
    
     bool TaskComplete(GridAgent* agent);
};

class ActionPickupResource: public TimedAction{
protected:
    WorldTypes::ItemType resType;
    
public:
    ActionPickupResource(string name_, float expiryTime_, ItemType resType_):
    TimedAction(name_, expiryTime_),
    resType(resType_)
    {
        //SetConditions(name);
    }
    
    ActionPickupResource(string name_, float expiryTime_, float cost_, ItemType resType_):
    TimedAction(name_, expiryTime_, cost_),
    resType(resType_)
    {
        //SetConditions(name);
    }
    
     void Execute(GridAgent* agent);
    
     bool TaskComplete(GridAgent* agent);
};

class ActionDropResource: public TimedAction{
protected:
    WorldTypes::ItemType resType;
    
public:
    ActionDropResource(string name_, float expiryTime_, ItemType resType_):
    TimedAction(name_, expiryTime_),
    resType(resType_)
    {
        //SetConditions(name);
    }
    
    ActionDropResource(string name_, float expiryTime_, float cost_, ItemType resType_):
    TimedAction(name_, expiryTime_, cost_),
    resType(resType_)
    {
        //SetConditions(name);
    }
    
     void Execute(GridAgent* agent);
    
     bool TaskComplete(GridAgent* agent);
};

class ActionWander:public TimedAction{

public:
    ActionWander()
    :TimedAction("Wander", 2){
        
    }
    
    ActionWander(int cost_)
    :TimedAction("Wander", 2,cost_){
   
    }
    
    ActionWander(string name_,int cost_)
    :TimedAction(name_, 2,cost_){
        
    }
    
     void Execute(GridAgent* agent);

     bool TaskComplete(GridAgent* agent);
};

#endif /* defined(__AgentGridActions__GridAgentActions__) */
