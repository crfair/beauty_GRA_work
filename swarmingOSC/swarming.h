#pragma once

#include "ofMain.h"
#include <ofxOpenCv.h>
#include <ofxCv/src/ofxCv.h>
#include <ofxOsc/src/ofxOsc.h>

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
	void voronoi();
	void sendCentroidsBundle();

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
	float min_contour_area = 200.0;

	Ptr<BackgroundSubtractor> pBackSub;
	ofVideoPlayer vidPlayer;

	bool isPlaying;

	// Delaunay and Voronoi functionality was based on code from https://learnopencv.com/delaunay-triangulation-and-voronoi-diagram-using-opencv-c-python/

	vector<Point2f> delaunayPoints;
	Mat delaunay;
	Size size;
	Rect rect;
	Subdiv2D subdiv;

	int view = 0;

	vector<vector<Point2f>> facets;
	vector<Point2f> centers;
	Mat voronoiMat;

	ofxOscSender sender;
	ofxOscReceiver receiver;
	ofTrueTypeFont font;
	ofxOscBundle bundle;
	ofxOscMessage m;
	Mat centroids_mat;
	Scalar color_centroids = Scalar(255, 0, 255);
};