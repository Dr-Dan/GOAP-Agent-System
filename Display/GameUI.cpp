//
//  GameUI.cpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 18/06/2016.
//
//

#include "GameUI.hpp"


GameUI::GameUI(){
	gotoButton.set("GOTO", false);
	nearestButton.set("NEAREST", false);
	//	testButton.addListener(this, &GameUI::TestPrint);
	//	testButton2.addListener(this, &GameUI::TestPrint);
	
	panelBaseAction.setName("MAIN");
	panelBaseAction.add(gotoButton);
	
	panelModifier.setName("MODIFIER");
//	panelModifier.add(nearestButton);
	//	panelBaseAction.add(testButton.setup("SPECIFIC"));
	
	gui.setup(panelBaseAction);
}

void GameUI::Display(){
	//	if(testButton == 1){
	//		printf("PRESSED #%d\n", a);
	//		a++;
	//	}
	
	//	panelBaseAction.draw();

//	for(pair<ofParameterGroup*, bool> p: panels){
//		if(p.second){
//			p.first->draw();
//		}
//	}
//	
//	panels[&panelModifier] = gotoButton;
//
	gui.draw();
	if(gotoButton){
		panelBaseAction.add(panelModifier);
//		ofVec2f pos = panelBaseAction.getPosition() + ofVec2f(panelBaseAction.getWidth(), 0);
//		panelModifier.setPosition(pos);
		printf("GOTO\n");

	}
}

void GameUI::TestPrint(){
	printf("GOTO\n");
	
}