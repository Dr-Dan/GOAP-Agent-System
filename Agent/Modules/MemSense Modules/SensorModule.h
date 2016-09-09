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
	GridCell* currentCell = nullptr;
	
public:
	SensorModule() = default;
	
	void SetCurrentCell(GridCell* cellIn); // to BB
	GridCell* GetCurrentCell();
	int GetCurrentCellId();
	
	void UpdateCellMemory(MemoryModule& memoryModule,
						  const vector<GridCell*>& cellsNear);
	void UpdateAgentMemory(MemoryModule& memoryModule,
						   const vector<GridAgent*>& agentsNear);
	
	bool ShouldAddCell(const GridCell& cell);
	
	// should be in BB or similar
	bool AtCell(ItemType itemType);
	bool AtCellWithResource(ItemType itemType);

};
#endif /* defined(__AgentGOBGridTest__SensorModule__) */
