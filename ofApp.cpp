#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	tM.AddTimer("world_timer", 250);
	
	agentManager = AgentManager();
	agentManager.AddAgentsRandomPos(GridValues::NUM_AGENTS);
	grid = Grid();
	grid.Update();
	
	grid.RandomizeGrid();
	
	dUI = DebugUI(&agentManager);
	
}

//--------------------------------------------------------------
void ofApp::update(){
	
	tM.SetFromSystem();
	
	if(isPlaying){
		
		grid.Update();
		
		agentManager.UpdateAgents();
		
		//		if(tM.IsNextStep("change")){
		//			cout<<"change: "<<tM.GetCurrentTime()<<endl;
		//			grid.SetCellsIsChanged(true);
		//		}
		
		if(tM.IsNextStep("world_timer")){
			agentManager.UpdateAgentsGridView(grid);
			agentManager.UpdateStepTime();
			
			grid.UpdateRatings();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(220);
	grid.Display(showResAmts);
	agentManager.DisplayAgents();
	
	dUI.Display();
	dUI.DisplayFPS();
	
	gameUI.Display();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		case '1':
			plcType = WorldTypes::CELL_NEUTRAL;
			break;
		case '2':
			plcType = WorldTypes::CELL_FOOD;
			break;
		case '3':
			plcType = WorldTypes::CELL_HOME;
			break;
		case '4':
			plcType = WorldTypes::CELL_WOOD;
			break;
		case '5':
			plcType = WorldTypes::CELL_STORAGE;
			break;
		default:
			plcType = WorldTypes::CELL_NEUTRAL;
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if(key == ' '){
		isPlaying = !isPlaying;
	} else if(key == 'z'){
		grid.RandomizeGrid();
	} else if(key == 'x'){
		grid.ClearGrid();
	}
	else if(key == 'q'){
		grid.overlayType = WorldTypes::OVERLAY_FOOD;
	} else if(key == 'w'){
		grid.overlayType = WorldTypes::OVERLAY_WOOD;
	} else if(key == 'e'){
		grid.overlayType = WorldTypes::OVERLAY_HOME;
	} else if(key == 'r'){
		grid.overlayType = WorldTypes::OVERLAY_AVG;
	} else if(key == 'a'){
		grid.overlayType = WorldTypes::NO_OVERLAY;
	} else if(key == 's'){
		showResAmts = !showResAmts;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if(button == 0){
		GridCell* gCell = grid.GetCell(Utility::GetGridPos(ofVec2f(x,y), grid.GetCells()));
		
		if(gCell != NULL){
			//			gCell->SetupType(plcType);
			grid.ChangeCellType(gCell->GetId(), plcType, GridValues::CELL_CHANGE_DIST);
			//			grid.ChangeCellType(gCell->GetId(), plcType);
			
			//			grid.UpdateRatings();
			//			grid.SetCellsIsChanged(true);
			
		}
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if(button == 0){
		GridCell* gCell = grid.GetCell(Utility::GetGridPos(ofVec2f(x,y), grid.GetCells()));
		
		if(gCell != NULL){
			//			gCell->SetupType(plcType);
			grid.ChangeCellType(gCell->GetId(), plcType, GridValues::CELL_CHANGE_DIST);
			//			grid.ChangeCellType(gCell->GetId(), plcType);
			
			//			grid.UpdateRatings();
			//			grid.SetCellsIsChanged(true);
			
		}
	}
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
	
}
