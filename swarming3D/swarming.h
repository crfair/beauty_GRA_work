#pragma once

#include "ofMain.h"
#include <ofxOpenCv.h>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/video.hpp>
#include <iostream>

using namespace cv;

class swarming {

public:
	void backSubMOG2KNN(std::string model);

private:

	void edge_detector();
	void pointsTo3D();

	Mat frame;
	Mat fgMask;
	int thresh = 200;

	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;
	std::vector<std::vector<Point>> hull;
	Mat drawing;

	Scalar color_contours = Scalar(0, 255, 0);
	Scalar color_hull = Scalar(255, 0, 0);
	Scalar color_bounds = Scalar(0, 0, 255);
	Rect bounds;

	Ptr<BackgroundSubtractor> pBackSub;
	VideoCapture capture;

	std::stringstream ss;
	std::string frameNumberString = ss.str();
};