#pragma once

#include "ofMain.h"
#include <ofxOpenCv.h>
#include <ofxCv/src/ofxCv.h>

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
	void triangulation();

	Mat frame;
	Mat frameBW;
	Mat fgMask;

	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;
	std::vector<std::vector<Point>> hull;
	std::vector<std::vector<Point>> approx;
	Mat drawing;

	Scalar color_contours = Scalar(0, 255, 0);
	Scalar color_hull = Scalar(255, 0, 0);
	Scalar color_bounds = Scalar(0, 0, 255);
	Scalar color_approx = Scalar(0, 255, 255);
	Scalar color_delaunay = Scalar(255, 255, 255);
	Scalar color_delaunay_points = Scalar(255, 255, 0);
	Rect bounds;

	Ptr<BackgroundSubtractor> pBackSub;
	ofVideoPlayer vidPlayer;

	bool isPlaying;

	vector<Point2f> delaunayPoints;
	Mat delaunay;
};