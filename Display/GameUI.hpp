//
//  GameUI.hpp
//  grid_agent_refactor
//
//  Created by D J Clarke on 18/06/2016.
//
//

#ifndef GameUI_hpp
#define GameUI_hpp

#include <stdio.h>
#include "ofxGUI.h"
#include <map>
#include "ofMain.h"
#include "ofParameter.h"

class GameUI{
	
	ofParameterGroup parameters;

	ofParameterGroup panelBaseAction;
	ofParameterGroup panelModifier;
	ofParameterGroup panelModifierType;
	ofParameterGroup panelModifierObject;
	
	ofxGuiGroup g;
	
	std::map<ofParameterGroup*, bool> panels = {
		std::make_pair(&panelBaseAction, true),
		std::make_pair(&panelModifier, false),
		std::make_pair(&panelModifierType, false),
		std::make_pair(&panelModifierObject, false)
	};
	
	ofParameter<bool> gotoButton;
	ofParameter<bool> nearestButton;
	ofParameter<bool> cellButton;
	
	ofxPanel gui;
	int a = 0;
public:
	GameUI();
	void Display();
	void TestPrint();
};
#endif /* GameUI_hpp */
