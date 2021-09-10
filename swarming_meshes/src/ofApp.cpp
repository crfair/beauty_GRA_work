#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	mesh.setMode(OF_PRIMITIVE_LINES); // set the ofPrimitiveMode
	mesh.enableColors();
	mesh.enableIndices();

	ofVec3f eyeLeftTop(50.0, 25.0, 0.0);
	ofVec3f eyeLeftBottom(50.0, 50.0, 0.0);
	ofVec3f eyeRightTop(100.0, 25.0, 0.0);
	ofVec3f eyeRightBottom(100.0, 50.0, 0.0);
	ofVec3f mouthLeft(50.0, 75.0, 0.0);
	ofVec3f mouthMiddle(75.0, 100.0, 0.0);
	ofVec3f mouthRight(100.0, 75.0, 0.0);

	mesh.addVertex(eyeLeftTop);
	mesh.addVertex(eyeLeftBottom);
	mesh.addIndex(0);
	mesh.addIndex(1);
	mesh.addColor(ofFloatColor(0.0, 1.0, 1.0));
	mesh.addColor(ofFloatColor(0.0, 1.0, 1.0));

	mesh.addVertex(eyeRightTop);
	mesh.addVertex(eyeRightBottom);
	mesh.addIndex(2);
	mesh.addIndex(3);
	mesh.addColor(ofFloatColor(0.0, 1.0, 1.0));
	mesh.addColor(ofFloatColor(0.0, 1.0, 1.0));

	mesh.addVertex(mouthLeft);
	mesh.addVertex(mouthMiddle);
	mesh.addVertex(mouthRight);
	mesh.addIndex(4);
	mesh.addIndex(5);
	mesh.addIndex(5);
	mesh.addIndex(6);
	mesh.addColor(ofFloatColor(0.0, 1.0, 0.0));
	mesh.addColor(ofFloatColor(0.0, 1.0, 0.0));
	mesh.addColor(ofFloatColor(0.0, 1.0, 0.0));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0); // sets background to black
	mesh.draw(); // draw the mesh
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
