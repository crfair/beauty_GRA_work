#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	vidPlayer.load("swarming_trim.mp4"); // stored in bin/data
	vidPlayer.play();
	vidPlayer.setLoopState(OF_LOOP_NORMAL); // sets the player to loop the video end to beginning

	colorImg.allocate(320, 240); // set width and height of the images based on the target video
	grayImg.allocate(320, 240);
	grayBg.allocate(320, 240);
	grayDiff.allocate(320, 240);

	bLearnBakground = true; // the 'background' is considered to be the first frame of the video, but the user can also press space to set it manually
	threshold = 80; // threshold is used in absolute differencing operations to determine how different pixels have to be from their background to be considered foreground
					// this value can be changed while the video is running
}

//--------------------------------------------------------------
void ofApp::update() {
	ofBackground(100, 100, 100); // set background to given rgb value

	bool bNewFrame = false;

	vidPlayer.update(); // updates the player's internal state to continue playback; usually called once per frame
	bNewFrame = vidPlayer.isFrameNew(); // checks if any of the pixels are different from the last frame

	// if the frame does have different pixels...
	if (bNewFrame) {
		colorImg.setFromPixels(vidPlayer.getPixels()); // save current frame

		grayImg = colorImg;
		
		// if we want to save the background
		if (bLearnBakground == true) {
			grayBg = grayImg; // copies the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImg);
		grayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well
		contourFinder.findContours(grayDiff, 20, (340 * 240) / 3, 10, true); // find holes
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);
	colorImg.draw(20, 20);
	grayImg.draw(360, 20);
	grayBg.draw(20, 280);
	grayDiff.draw(360, 280);

	// then draw the contours:

	ofFill();
	ofSetHexColor(0x333333);
	ofDrawRectangle(360, 540, 320, 240);
	ofSetHexColor(0xffffff);

	// we could draw the whole contour finder
	//contourFinder.draw(360,540);

	// or, instead we can draw each blob individually from the blobs vector,
	// this is how to get access to them:
	for (int i = 0; i < contourFinder.nBlobs; i++) {
		contourFinder.blobs[i].draw(360, 540);

		// draw over the centroid if the blob is a hole
		ofSetColor(255);
		if (contourFinder.blobs[i].hole) {
			ofDrawBitmapString("hole",
				contourFinder.blobs[i].boundingRect.getCenter().x + 360,
				contourFinder.blobs[i].boundingRect.getCenter().y + 540);
		}
	}

	// finally, a report:
	ofSetHexColor(0xffffff);
	stringstream reportStr;
	reportStr << "bg subtraction and blob detection" << endl
		<< "press space to capture bg" << endl
		<< "threshold " << threshold << " (press: +/-)" << endl
		<< "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
	ofDrawBitmapString(reportStr.str(), 20, 600);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	switch (key) {
	case ' ':
		bLearnBakground = true;
		break;
	case '+':
		threshold++;
		if (threshold > 255) threshold = 255;
		break;
	case '-':
		threshold--;
		if (threshold < 0) threshold = 0;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}