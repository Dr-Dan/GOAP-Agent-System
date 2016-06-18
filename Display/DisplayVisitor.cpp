//
//  DisplayVisitor.cpp
//  AgentGOBGridTest
//
//  Created by D J Clarke on 19/04/2015.
//
//

#include "DisplayVisitor.h"
#include "GridCell.h"
#include "GridValues.h"
#include "GridAgent.h"

void DisplayVisitor::Render(const GridAgent& agent){
	int halfCell = GridValues::CELL_SIZE/2;
	ofSetColor(0,0,220);
	ofFill();
	ofDrawEllipse(halfCell + (agent.moveModule.GetGridPos() * GridValues::CELL_SIZE), agent.agentSize, agent.agentSize);
}


void DisplayVisitor::Render(const GridCell& cell){
	ofVec2f pos = cell.GetPos();
	int cellSize = cell.GetSize();
	ofRectangle cellRect = cell.GetRect();
	ofColor cellColor = cell.cellDisplay.GetColor();
	
	WorldTypes::ItemType cellType = cell.GetType();
	
	if(cellType == WorldTypes::CELL_WOOD){
		ofSetColor(10,200,0);
		ofFill();
		ofDrawEllipse(pos.x+cellSize/2, pos.y+cellSize/2, cellSize/1.5, cellSize/1.5);
	} else {
		ofSetColor(cellColor);
		ofFill();
		ofDrawRectangle(cellRect);
	}
	
	// OUTLINE
	ofSetLineWidth(1);
	ofSetColor(0,0,0,40);
	ofNoFill();
	ofDrawRectangle(cellRect);
	
	if(cellType != WorldTypes::CELL_HOME){
		if(cellType != WorldTypes::CELL_NEUTRAL){
			if(cellType != WorldTypes::CELL_STORAGE &&
			   cellType != WorldTypes::CELL_STORAGE){
				ofSetColor(255);
				ofFill();
				ofDrawBitmapString(ofToString(cell.GetResourceHandler()->GetAmtResource(cellType)), pos + ofVec2f(0, 10));
			} else {
				ofSetColor(255);
				ofFill();
				ofDrawBitmapString(ofToString(cell.GetResourceHandler()->GetAmtResource(WorldTypes::CELL_FOOD)), cell.GetPos() + ofVec2f(0, 10));
			}
		}
	}
}

void DisplayVisitor::Render(const GridCell& cell, bool showNums, bool showingOverlay){
	ofRectangle cellRect = cell.GetRect();
	ofVec2f pos = cellRect.position;
	int cellSize = cellRect.width;
	
	// Colors
	ofColor cellColor = cell.cellDisplay.GetColor();
	ofColor overlayColor = cell.cellDisplay.GetOverlayColor();
	
	WorldTypes::ItemType cellType = cell.GetType();
	
	// draw basic cell
	ofSetColor(cellColor);
	ofFill();
	ofDrawRectangle(cellRect);
	
	// for special cases
	//	if(!showingOverlay){
	// e.g. trees
	if(cellType == WorldTypes::CELL_WOOD){
		int stumpWd = cellSize/4, stumpHt = cellSize/2;
		
		// draw tree object
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofSetColor(120,40,10);
		ofFill();
		ofDrawRectangle(pos.x+cellSize/2, cell.GetPos().y+cellSize/2+5, stumpWd, stumpHt);
		ofSetRectMode(OF_RECTMODE_CORNER);
		
		ofSetColor(10,200,0);
		ofFill();
		ofDrawEllipse(pos.x+cellSize/2, cell.GetPos().y+cellSize/2, cellSize/1.5, cellSize/1.5);
	}
	//	}
	
	if(showingOverlay){
		ofSetColor(overlayColor);
		ofFill();
		ofDrawRectangle(cellRect);
	}
	
	// OUTLINE
	ofSetLineWidth(1);
	ofSetColor(0,0,0,40);
	ofNoFill();
	ofDrawRectangle(cellRect);
	
	if(showNums){
		if(cellType != WorldTypes::CELL_NEUTRAL){
			if(cellType != WorldTypes::CELL_HOME &&
			   cellType != WorldTypes::CELL_STORAGE){
				ofSetColor(255);
				ofFill();
				ofDrawBitmapString(ofToString(cell.GetResourceHandler()->GetAmtResource(cellType)), pos + ofVec2f(0, 10));
			} else {
				ofSetColor(255);
				ofFill();
				ofDrawBitmapString(ofToString(cell.GetResourceHandler()->GetAmtResource(WorldTypes::CELL_FOOD)), pos + ofVec2f(0, 10));
			}
		}
	}
}

void DisplayVisitor::Render(const string& text){
	
	
}