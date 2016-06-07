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
	
	GridCell* currentCell = NULL;
	
public:
    SensorModule() = default;
	
	void SetCurrentCell(GridCell* cellIn);
	GridCell* GetCurrentCell();
	int GetCurrentCellId();
	
    void UpdateCellMemory(MemoryModule& memoryModule);
    void UpdateAgentMemory(MemoryModule& memoryModule);

    bool AtCell(ItemType itemType);
    bool AtCellWithResource(ItemType itemType);

	void UpdateCellView(vector<GridCell*> cellsNear_);
	void UpdateAgentView(vector<GridAgent*> agentsNear_);
};
#endif /* defined(__AgentGOBGridTest__SensorModule__) */
