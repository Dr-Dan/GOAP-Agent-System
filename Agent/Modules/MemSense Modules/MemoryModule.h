//
//  MemoryModule.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 20/04/2015.
//
//

#ifndef __AgentGOBGridTest__MemoryModule__
#define __AgentGOBGridTest__MemoryModule__

#include <stdio.h>
#include "AgentFact.h"
//#include "GridValues.h"
#include "Utility.h"
#include "WorldState.h"
#include "WorldTypes.h"
//#include "GridAgent.h"
//#include "GridCell.h"
#include "Resource.h"

// facts should have own id and targetId and can then be stored in map<>

using namespace WorldTypes;
class AgentAttributes;
class GridAgent;
class MemoryModule{

//    could just have fact map using FactType::?
    vector<Fact*> facts;
    vector<CellFact*> cellFacts;
//	vector<CellFact*> cellsByRating;
    vector<AgentFact> agentFacts;
	int homeCellId = -1;
	bool hasHome = false;
	
//    GridAgent* agent;
public:
	typedef void (*CellCompareFunc)();

	~MemoryModule();

	MemoryModule()= default;
	
	// POSITION FUNCTIONS
    // get position of nearest ...
    bool GetPosNearestCell(ofVec2f& targetVec, ofVec2f pos, ItemType cellType);
	bool GetPosNearestCellList(vector<ofVec2f>& targetVec, ofVec2f pos, ItemType cellType);

    bool GetPosNearestResource(ofVec2f& targetVec, ofVec2f pos, ItemType resType);

//	bool GetPosHighestRatingCell(ofVec2f& targetVec, ItemType compType);

	// returns cell of type targetType of highest rating of compType
	bool GetPosHighestRatingCell(ofVec2f& targetVec, ItemType desiredType);
	bool GetPosHighestRatingCell(ofVec2f& targetVec, ItemType desiredType, CellCompareFunc compFunc);

	//	bool GetPosHighestRatingCell(ofVec2f& targetVec, ItemType targetType, ItemType desiredType);

	CellFact* GetFactHighestRatingCellFood(ItemType desiredType);
	CellFact* GetFactHighestRatingCellCombined(ItemType desiredType);
	CellFact* GetFactHighestRatingCell(ItemType desiredType, CellCompareFunc compFunc);

    bool GetPosNearestAgent(ofVec2f& targetVec, ofVec2f pos);
	
	// ---------------------------------------------------------------
	// FACT FUNCTIONS

	// Add facts
    void AddCellFact(CellFact fact);
    
    void AddAgentFact(AgentFact fact);
	
	// update facts
	void UpdateCellFact(int worldId, ItemType cellTypeIn, vector<Resource> cellResources_);
	void UpdateCellFact(int worldId, ItemType cellTypeIn, vector<Resource> cellResources_, mapRat cellRatings_);
	void UpdateCellFact(int worldId, ItemType cellTypeIn, vector<Resource> cellResources_, mapRat cellRatings_, float combinedRating_);

	void UpdatePosAgentFact(int worldId, ofVec2f newPos);
	
	// get facts
    CellFact* GetCellFact(int worldId);
	CellFact* GetCellFact(ofVec2f gridPos);

    AgentFact GetAgentFact(int worldId);
	
	// Check if info is known
	bool IsInMemory(int worldId);
    
    bool KnowsOfCellType(ItemType cellType);
    
    bool KnowsOfResourceType(ItemType cellType);
	
	bool KnowsOfHomeLocation();
	bool KnowsOfUnfilledStorage();

    bool KnowsOfAgent(int agentId);

	void sortCellsByFoodRating();
	void sortCellsByCombinedRating();
	
	void SetHomeCell(int cellId);
	
	int GetCurrentHomeCellId();
	
	int GetBestHomeCellId();
	
	void RemoveHome();
	bool HasHome();
};
#endif /* defined(__AgentGOBGridTest__MemoryModule__) */
