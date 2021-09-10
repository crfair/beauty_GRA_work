#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	image.load("bacteria.jpg"); // load in image from bin/data
	background.load("bacteria_background.jpg");

	threshold = 60;

	colorImg.allocate(1440, 900);
	grayImg.allocate(1440, 900);
	grayBg.allocate(1440, 900);
	grayDiff.allocate(1440, 900);

	colorImg = image;
	grayImg = colorImg;
	grayBg = background;
	grayDiff.absDiff(grayBg, grayImg);
	grayDiff.threshold(threshold);

	contourFinder.findContours(grayDiff, 20, (1440 * 900) / 3, 10, true);

	mesh.setMode(OF_PRIMITIVE_LINES); // set mode to create points only
	mesh.enableColors();

	float intensityThreshold = 200.0;
	int w = image.getWidth();
	int h = image.getHeight();

	// for each pixel in the image...
	for (int x = 0; x < w; ++x) {
		for (int y = 0; y < h; ++y) {
			ofColor c = image.getColor(x, y); // get the pixel's color
			float intensity = c.getLightness(); // and it's lightness
			if (intensity >= intensityThreshold) { // if the pixel is sufficiently light...
				ofVec3f pos(x, y, 0.0); // add it to the mesh
				mesh.addVertex(pos);
				mesh.addColor(c); // the mesh will autoconvert the ofColor to an ofFloatColor
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetHexColor(0xffffff);
	ofFill();
	ofSetHexColor(0x333333);
	ofDrawRectangle(0, 0, 1440, 900);
	ofSetHexColor(0xffffff);

	for (int i = 0; i < contourFinder.nBlobs; i++) {
		contourFinder.blobs[i].draw(0, 0);
		ofSetColor(255);
		if (contourFinder.blobs[i].hole) {
			ofDrawBitmapString("hole",
				contourFinder.blobs[i].boundingRect.getCenter().x,
				contourFinder.blobs[i].boundingRect.getCenter().y);
		}
	}

	mesh.draw();
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
