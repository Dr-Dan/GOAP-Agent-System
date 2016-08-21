//
//  AgentFact.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 20/04/2015.
//
//

#ifndef __AgentGOBGridTest__AgentFact__
#define __AgentGOBGridTest__AgentFact__

#include <stdio.h>
//#include "ofMain.h"
#include "ofVec2f.h"
//#include <vector>
#include "WorldTypes.h"
#include "Resource.h"
#include "GridValues.h"

// consider: factId, ownerId...
// Also some fact type class or more specific e.g. enum{CELL_FOOD}
using namespace WorldTypes;
//using namespace std;

// ------------------------------------------------------------------
class Fact{
	int targetId;
	ofVec2f gridPos;
	
protected:
	
public:
//	virtual ~Fact(){}
	
	Fact():
	targetId(-1),
	gridPos(ofVec2f()){
		
	}
	
	Fact(int targetId_, ofVec2f gridPos_) {
		targetId = targetId_;
		gridPos = gridPos_;
	}
	
	ofVec2f GetGridPos(){
		return gridPos;
	}
	
	void SetGridPos(ofVec2f& pos){
		gridPos = pos;
	}
	
	int GetTargetId(){
		return targetId;
	}
	
};

// ------------------------------------------------------------------
// Should this be a fact or its own class???
//class ResourceFact{
//	vector<Resource> cellResources;
//	mapRat cellRatings;
//	
//public:
//	ResourceFact():
//	cellResources(),
//	cellRatings(){
//		
//	}
//	
//	ResourceFact(vector<Resource> cellResources_, mapRat cellRatings_):
//	cellResources(cellResources_),
//	cellRatings(cellRatings_)
//	{
//	}
//	
//};

// ------------------------------------------------------------------
class CellFact : public Fact{
	ItemType itemType;
	vector<Resource> cellResources;
	mapRat cellRatings;
	float combinedRating;
	bool isHome;
	
public:
//	~CellFact(){
//		if(!cellResources.empty()){
//			cellResources.clear();
//		}
//		if(!cellRatings.empty()){
//			cellRatings.clear();
//		}
//	}
	
	CellFact():
	Fact(),
	itemType(),
	cellResources(),
	cellRatings(),
	isHome(false),
	combinedRating(0)
	{
		
	}
	
	CellFact(int targetId_, ItemType itemType_, ofVec2f gridPos_, vector<Resource> cellResources_):
	Fact(targetId_, gridPos_),
	cellResources(cellResources_),
	cellRatings(),
	itemType(itemType_),
	isHome(false),
	combinedRating(0)
	{
		
	}
	
	CellFact(int targetId_, ItemType itemType_, ofVec2f gridPos_, vector<Resource> cellResources_, mapRat cellRatings_):
	Fact(targetId_, gridPos_),
	cellResources(cellResources_),
	cellRatings(cellRatings_),
	itemType(itemType_),
	isHome(false),
	combinedRating(0)
	{
	}
	
	
	CellFact(int targetId_, ItemType itemType_, ofVec2f gridPos_, vector<Resource> cellResources_, mapRat cellRatings_, float combinedRating_):
	Fact(targetId_, gridPos_),
	cellResources(cellResources_),
	cellRatings(cellRatings_),
	itemType(itemType_),
	isHome(false),
	combinedRating(combinedRating_)
	{
	}
	
	
	void SetHome(bool isHomeIn){
		if(itemType == CELL_HOME && isHomeIn){
			isHome = true;
		} else{
			isHome = false;
		}
	}
	
	bool IsCellHome(){
		return isHome;
	}
	
	void SetType(ItemType newItemType){
			itemType = newItemType;
	}
	
	ItemType GetFactType(){
		return itemType;
	}
	
	void UpdateResources(vector<Resource> newResources){
		cellResources = newResources;
	}
	
	vector<Resource> GetResourceVec(){
		return cellResources;
	}
	
	// TODO - implement this for multiple types in same cell
	// could add all up? Will need to do this also in resource/cell class?
	bool IsFull(){
		for(int i = 0; i < cellResources.size(); i++){
			if(cellResources[i].GetAmtResource() > GridValues::MAX_RESOURCES){
				return true;
			}
		}
		return false;
	}
	
	int GetResourceAmt(ItemType resType) const{
		int amt = 0;
		for(Resource r : cellResources){
			if(r.GetType() == resType){
				amt = r.GetAmtResource();
			}
		}

		return amt;
	}
	
	void SetCombinedRating(float newCombinedRating){
		combinedRating = newCombinedRating;
	}
	
	float GetCombinedRating(){
		return combinedRating;
	}
	
	void UpdateRatings(mapRat newRatings){
		cellRatings = newRatings;
	}
	
	mapRat GetRatingsMap(){
		return cellRatings;
	}
	
	float GetRatingAmt(ItemType ratingType) const{
		float amt = 0;
		if(cellRatings.count(ratingType)){
			amt = cellRatings.at(ratingType);
		}
		return amt;
	}
};

// ------------------------------------------------------------------
class AgentFact : public Fact{
	void SetType(ItemType newItemType){}
public:
	//    float respectForAgent;
	//    mapRes resources;
	AgentFact(int targetId_, ofVec2f gridPos_):
	Fact(targetId_, gridPos_){
	}
};

// describes a fact related to property ownership
class OwnerFact: public CellFact{
		vector<int> ownedIds;
//	int ownerId;
	
public:
	OwnerFact():
	CellFact()
	{
	}
	
	OwnerFact(int agentId){
		ownedIds.push_back(agentId);
//		ownerId = agentId;
	}
	
	bool isOwned(int ownedId){
		if(count(ownedIds.begin(), ownedIds.end(), ownedId)){
//		if(agentId == ownerId){
			return true;
		}
		return false;
	}
};

#endif /* defined(__AgentGOBGridTest__AgentFact__) */
