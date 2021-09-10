#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	mesh.setMode(OF_PRIMITIVE_LINE_LOOP); // set the ofPrimitiveMode

	ofVec3f top(100.0, 50.0, 0.0); // ofVec3f takes 3 floats for x, y, and z
	ofVec3f left(50.0, 150.0, 0.0);
	ofVec3f right(150.0, 150.0, 0.0);

	mesh.addVertex(top); // add all the vertexes to the mesh
	mesh.addColor(ofFloatColor(1.0, 0.0, 0.0)); // Red

	mesh.addVertex(left);
	mesh.addColor(ofFloatColor(0.0, 1.0, 0.0)); // Green

	mesh.addVertex(right);
	mesh.addColor(ofFloatColor(0.0, 0.0, 1.0)); // Blue
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
