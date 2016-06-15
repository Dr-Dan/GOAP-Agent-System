//
//  Player.cpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 09/06/2016.
//
//

#include "Player.hpp"

void Player::SetTargetPosition(ofVec2f targetPos){
	navModule.SetTarget(targetPos);
}

void Player::Move(){
	if(navModule.HasTarget()){
		moveModule.DoMovement();
	}
}