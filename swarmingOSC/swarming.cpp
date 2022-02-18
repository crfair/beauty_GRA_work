#include "swarming.h"
#include <iostream>

/*
* This code runs at the beginning of the program before any other code runs.
*/
void swarming::setup()
{
	pBackSub = createBackgroundSubtractorKNN(5000, 150.0, false);
	vidPlayer.load("swarming_even_smaller.mp4");
	isPlaying = true;
	vidPlayer.play();
	vidPlayer.setLoopState(OF_LOOP_NORMAL);

	sender.setup("localhost", 12345);
	receiver.setup(12345);

	font.load("futura_book.otf", 12);
	ofBackground(150);
}

/*
* Runs in a loop every tick
*/
void swarming::update()
{
	// If the video player should be (un)paused, do so
	if (vidPlayer.isPlaying() != isPlaying)
	{
		vidPlayer.setPaused(!isPlaying);
	}

	// Update only if the player is playing; this allows the user to pause and inspect individual frames
	if (isPlaying)
	{
		vidPlayer.update();
		frame = toCv(vidPlayer.getPixels());

		if (frame.empty())
			return;

		size = frame.size();
		rect = Rect(0, 0, size.width, size.height);
		subdiv = Subdiv2D(rect);

		backSubKNN(frame);
		edge_detector();
		triangulation();
		voronoi();
		sendCentroidsBundle();
	}
}

/*
* Runs directly after update, draws things to the screen
*/
void swarming::draw()
{
	if (isPlaying)
	{
		ofSetHexColor(0xffffff);
	//	drawMat(frameBW, 0, 0);
	//	drawMat(fgMask, 640, 0);
	//	drawMat(drawing, 0, 480);

	//	if (isDelaunay)
	//		drawMat(delaunay, 640, 480);
	//	else
	//		drawMat(voronoiMat, 640, 480);
		drawMat(centroids_mat, 640, 0);
	}

	ofxOscMessage m;
	string message = "";
	while (receiver.hasWaitingMessages())
	{
		receiver.getNextMessage(m);
		message += "x: " + std::to_string(m.getArgAsFloat(0)) + ", y: " + std::to_string(m.getArgAsFloat(1)) + "\n";
	}
	font.drawString(message, 50, 50);
}

void swarming::keyPressed(int key)
{
	switch (key)
	{
	// If the user presses the spacebar, pause the application.
	case ' ':
		isPlaying = !isPlaying;
		ofSetBackgroundAuto(isPlaying);
		break;
	// Allow the player to switch between the Delaunay triangulation and voronoi diagram
	case 'v':
		isDelaunay = !isDelaunay;
		break;
	}
}

/*
* Send a bundle of the contour's center points via OSC
*/
void swarming::sendCentroidsBundle()
{
	centroids_mat = drawing;
	bundle.clear();

	vector<Moments> mmnts(approx.size());

	vector<Point2f> centroids(approx.size());
	for (int i = 0; i < approx.size(); i++)
	{
		if (contourArea(contours[i]) >= min_contour_area)
		{
			mmnts[i] = moments(approx[i], false);
			centroids[i] = Point2f(mmnts[i].m10 / mmnts[i].m00, mmnts[i].m01 / mmnts[i].m00);
			circle(centroids_mat, centroids[i], 4, color_centroids, -1, 8, 0);
		}
	}

	for (Point2f p : centroids)
	{
		if (p != Point2f(0, 0))
		{
			m.clear();
			m.addFloatArg(p.x);
			m.addFloatArg(p.y);
			bundle.addMessage(m);
		}
	}
	sender.sendBundle(bundle);
}

/*
* Create a Voronoi diagram based on the contour points
*/
void swarming::voronoi()
{
	voronoiMat = Mat::zeros(size, CV_8UC3);
	facets.clear();
	centers.clear();

	Mat approxMat = Mat(frame.size(), CV_8UC3, &approx);

	vector<Point> ifacet;
	vector<vector<Point>> ifacets(1);

	subdiv.getVoronoiFacetList(vector<int>(), facets, centers);

	for (size_t i = 0; i < facets.size(); i++)
	{
		ifacet.resize(facets[i].size());
		for (size_t j = 0; j < facets[i].size(); j++)
		{
			ifacet[j] = facets[i][j];
		}

		Scalar color;
		color[0] = rand() & 255;
		color[1] = rand() & 255;
		color[2] = rand() & 255;
		fillConvexPoly(voronoiMat, ifacet, color, 8, 0);

		ifacets[0] = ifacet;
		polylines(voronoiMat, ifacets, true, Scalar(), 1, CV_AA, 0);
		circle(voronoiMat, centers[i], 3, Scalar(), CV_FILLED, CV_AA, 0);
	}
}

/*
* Perform Delaunay triangulation on the contour points
*/
void swarming::triangulation()
{
	delaunay = Mat::zeros(size, CV_8UC3);
	delaunayPoints.clear();

	Mat approxMat = Mat(frame.size(), CV_8UC3, &approx);

	for (size_t i = 0; i < approx.size(); i++)
	{
		for (size_t j = 0; j < approx[i].size(); j++)
		{
			if (contourArea(contours[i]) >= min_contour_area)
				delaunayPoints.push_back(approx[i][j]);
		}
	}

	for (vector<Point2f>::iterator it = delaunayPoints.begin(); it != delaunayPoints.end(); it++)
	{
		subdiv.insert(*it);
	}

	vector<Vec6f> triangleList;
	subdiv.getTriangleList(triangleList);
	vector<Point> pt(3);

	for (size_t i = 0; i < triangleList.size(); i++)
	{
		Vec6f t = triangleList[i];
		pt[0] = Point(cvRound(t[0]), cvRound(t[1]));
		pt[1] = Point(cvRound(t[2]), cvRound(t[3]));
		pt[2] = Point(cvRound(t[4]), cvRound(t[5]));

		if (rect.contains(pt[0]) && rect.contains(pt[1]) && rect.contains(pt[2]))
		{
			line(delaunay, pt[0], pt[1], color_delaunay, 1, CV_AA, 0);
			line(delaunay, pt[1], pt[2], color_delaunay, 1, CV_AA, 0);
			line(delaunay, pt[2], pt[0], color_delaunay, 1, CV_AA, 0);
		}
	}

	for (vector<Point2f>::iterator it = delaunayPoints.begin(); it != delaunayPoints.end(); it++)
	{
		circle(delaunay, *it, 2, color_delaunay_points, CV_FILLED, CV_AA, 0);
	}
}

/*
* Finds and draws the contours, convex hull, and approximated contours of the swarms
*/
void swarming::edge_detector()
{
	findContours(fgMask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	hull = std::vector<std::vector<Point>>(contours.size());
	approx = std::vector<std::vector<Point>>(contours.size());
	// for each of the contours, find the convex hull and approximate curve
	for (size_t i = 0; i < contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], false);
		double epsilon = 0.01 * arcLength(contours[i], true); //determine the number of lines in the polygon as a function of the contour's arc length
		approxPolyDP(contours[i], approx[i], epsilon, true);
	}

	// Create empty Mat to draw on
	drawing = Mat::zeros(fgMask.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++)
	{
		// Get the bounds of the contours
		bounds = boundingRect(contours[i]);

		// If a contour is below a certain size, don't draw it; this prevents the inclusion of very small contours 
		// for small amounts of bacteria residue in the frame and instead allows us to focus on the swirls and snakes
		if (contourArea(contours[i]) >= min_contour_area)
		{
			rectangle(drawing, bounds, color_bounds);
			//drawContours(drawing, contours, int(i), color_contours, 2, LINE_8, hierarchy, 0);
			//drawContours(drawing, hull, int(i), color_hull, 2, LINE_8, hierarchy, 0);
			drawContours(drawing, approx, int(i), color_approx, 2, LINE_8, hierarchy, 0);
		}
	}
}

/*
* Settings for the background subtraction are managed here. The image passed to background subtraction can be
* set to black and white, scaled, and blurred by commenting or uncommenting lines of code.
*/
void swarming::backSubKNN(Mat frame)
{
	cvtColor(frame, frameBW, COLOR_BGR2GRAY);
	frame.convertTo(frame, -1, 0.5, 0);
	//GaussianBlur(frame, frame, Size(3, 3), 0);
	pBackSub->apply(frameBW, fgMask);
}
