//
//  SensorModule.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 20/04/2015.
//
//

#ifndef __AgentGOBGridTest__SensorModule__
#define __AgentGOBGridTest__SensorModule__

#include <stdio.h>
#include "GridCell.h"
#include "Utility.h"
#include "AgentFact.h"
#include "WorldTypes.h"

using namespace WorldTypes;

class GridAgent;
class MemoryModule;

class SensorModule{
	
	// stores cells for agent
	vector<GridCell*> cellsNear;
	vector<GridAgent*> agentsNear;
	
	GridCell* currentCell = nullptr;
	
public:
	SensorModule() = default;
	
	void SetCurrentCell(GridCell* cellIn); // to BB
	GridCell* GetCurrentCell();
	int GetCurrentCellId();
	
	void UpdateCellMemory(MemoryModule& memoryModule,
						  const vector<GridCell*>& cellsNear_);
	void UpdateAgentMemory(MemoryModule& memoryModule,
						   const vector<GridAgent*>& agentsNear_);
	
//	void UpdateCellInfo(MemoryModule& memoryModule);
	bool ShouldAddCell(const GridCell& cell);
	
	bool AtCell(ItemType itemType);
	bool AtCellWithResource(ItemType itemType);
	
//	void UpdateCellView(const vector<GridCell*>& cellsNear_);
//	void UpdateAgentView(const vector<GridAgent*>& agentsNear_);
	bool CellResourcesChanged(const vector<Resource>& vecKnownCellRes, const vector<Resource>& vecCellNearRes);
//	bool HomeHasChanged(const GridCell& cell, MemoryModule& memoryModule);
};
#endif /* defined(__AgentGOBGridTest__SensorModule__) */
