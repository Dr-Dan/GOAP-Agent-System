//
//  Entity.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 20/04/2015.
//
//

#ifndef __AgentGOBGridTest__Entity__
#define __AgentGOBGridTest__Entity__

#include <stdio.h>
#include "Utility.h"

class Entity{
    int worldId;

public:
    Entity(){
        worldId = Utility::GetWorldId();
    }
    
    int GetId(){
//		cout<< worldId<<endl;

        return worldId;
    }
};
#endif /* defined(__AgentGOBGridTest__Entity__) */
