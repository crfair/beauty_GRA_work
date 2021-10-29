#pragma once

#include "ofMain.h"
#include <ofxOpenCv.h>
#include <ofxCv/src/ofxCv.h>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/video.hpp>

using namespace cv;
using namespace ofxCv;

class swarming : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();
	void keyPressed(int key);

private:

	void backSubKNN(Mat frame);
	void edge_detector();
	void pointsTo3D();

	Mat frame;
	Mat fgMask;
	int thresh = 200;

	ofImage ofFrame;
	ofImage ofMask;

	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;
	std::vector<std::vector<Point>> hull;
	std::vector<std::vector<Point>> approx;
	Mat drawing;

	Scalar color_contours = Scalar(0, 255, 0);
	Scalar color_hull = Scalar(255, 0, 0);
	Scalar color_bounds = Scalar(0, 0, 255);
	Rect bounds;

	Ptr<BackgroundSubtractor> pBackSub;
	ofVideoPlayer vidPlayer;

	bool isPlaying;
};