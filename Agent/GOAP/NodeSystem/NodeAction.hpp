//
//  NodeAction.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 19/06/2016.
//
//

#ifndef NodeAction_hpp
#define NodeAction_hpp

#include <stdio.h>
#include "NodeBase.hpp"
class TimedAction;
class NodeAction: public NodeBase{
	TimedAction* action;
public:
	NodeAction(TimedAction*);
};
#endif /* NodeAction_hpp */
