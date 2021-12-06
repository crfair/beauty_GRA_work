#include "swarming.h"

void swarming::setup()
{	
	pBackSub = createBackgroundSubtractorKNN(5000, 150.0, false);
	vidPlayer.load("swarming_even_smaller.mp4");
	isPlaying = true;
	vidPlayer.play();
	vidPlayer.setLoopState(OF_LOOP_NORMAL);

	//mesh.setMode(OF_PRIMITIVE_LINES);
}

void swarming::update()
{
	if (vidPlayer.isPlaying() != isPlaying)
	{
		vidPlayer.setPaused(!isPlaying);
	}

	if (isPlaying)
	{
		vidPlayer.update();
		frame = toCv(vidPlayer.getPixels());

		if (frame.empty())
			return;

		backSubKNN(frame);
		edge_detector();
		//pointsTo3D();
		triangulation();
	}
}

void swarming::draw()
{
	if (isPlaying)
	{
		ofSetHexColor(0xffffff);
		drawMat(frameBW, 0, 0);
		drawMat(fgMask, 640, 0);
		drawMat(drawing, 0, 480);
		drawMat(delaunay, 640, 480);
		//drawMat(meshMat, 640, 480);
		//mesh.draw();
	}
}

void swarming::keyPressed(int key)
{
	switch (key)
	{
	case ' ':
		isPlaying = !isPlaying;
		ofSetBackgroundAuto(isPlaying);
		break;
	}
}

void swarming::triangulation()
{
	Size size = frame.size();
	Rect rect(0, 0, size.width, size.height);
	Subdiv2D subdiv(rect);

	delaunay = Mat::zeros(frame.size(), CV_8UC3);
	delaunayPoints.clear();

	Mat approxMat = Mat(frame.size(), CV_8UC3, &approx);

	for (vector<Point> vec : approx)
	{
		for (Point p : vec)
		{
			delaunayPoints.push_back(p);
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

void swarming::pointsTo3D()
{
	//mesh.clear();
	//meshMat = Mat::zeros(fgMask.size(), CV_8UC3);

	//for (int i = 0; i < approx.size(); i++)
	//{
	//	for (int j = 0; j < approx[i].size(); j++)
	//	{
	//		ofVec3f pos(approx[i][j].x, approx[i][j].y, 0.0);
	//		mesh.addVertex(pos);
	//		mesh.addColor(ofColor::white);
	//	}
	//}	
}

void swarming::edge_detector()
{
	findContours(fgMask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	hull = std::vector<std::vector<Point>>(contours.size());
	approx = std::vector<std::vector<Point>>(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], false);
		double epsilon = 0.01 * arcLength(contours[i], true);
		approxPolyDP(contours[i], approx[i], epsilon, true);
	}

	drawing = Mat::zeros(fgMask.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++)
	{
		bounds = boundingRect(contours[i]);

		if (contourArea(contours[i]) > 200.0)
		{
			rectangle(drawing, bounds, color_bounds);
			//drawContours(drawing, contours, int(i), color_contours, 2, LINE_8, hierarchy, 0);
			//drawContours(drawing, hull, int(i), color_hull, 2, LINE_8, hierarchy, 0);
			drawContours(drawing, approx, int(i), color_approx, 2, LINE_8, hierarchy, 0);
		}
	}
}

void swarming::backSubKNN(Mat frame)
{
	cvtColor(frame, frameBW, COLOR_BGR2GRAY);
	//frame.convertTo(frame, -1, 0.5, 0);
	//GaussianBlur(frame, frame, Size(3, 3), 0);
	pBackSub->apply(frameBW, fgMask);
}
