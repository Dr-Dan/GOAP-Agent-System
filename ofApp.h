#pragma once

#include "ofMain.h"
#include "Grid.h"
#include "AgentManager.h"
#include "GridValues.h"
#include "WorldSetupValues.hpp"
#include "TimeMaster.h"
#include "DebugUI.h"
#include "WorldTypes.h"
#include "GameUI.hpp"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	Grid grid;
	AgentManager agentManager;
	
	TimeMaster tM;
	
	DebugUI dUI;
	WorldTypes::ItemType plcType;
	
	bool isPlaying = true;
	bool showResAmts = false;
	
	GameUI gameUI;
};
