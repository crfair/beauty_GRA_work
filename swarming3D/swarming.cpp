#include "swarming.h"

void swarming::setup()
{	
	pBackSub = createBackgroundSubtractorKNN(5000, 150.0, false);
	vidPlayer.load("swarming_even_smaller.mp4");
	isPlaying = true;
	vidPlayer.play();
	vidPlayer.setLoopState(OF_LOOP_NORMAL);\

	mesh.setMode(OF_PRIMITIVE_TRIANGLES);
}

void swarming::update()
{
	if (vidPlayer.isPlaying() != isPlaying)
	{
		vidPlayer.setPaused(!isPlaying);
	}

	vidPlayer.update();
	frame = toCv(vidPlayer.getPixels());

	if (frame.empty())
		return;

	backSubKNN(frame);
	edge_detector();
	pointsTo3D();
}

void swarming::draw()
{
	if (isPlaying)
	{
		ofSetHexColor(0xffffff);
		drawMat(frame, 0, 0);
		drawMat(fgMask, 640, 0);
		drawMat(drawing, 0, 480);
		drawMat(meshMat, 640, 480);
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

void swarming::pointsTo3D()
{
	mesh.clear();

	for (std::vector<Point> vec : approx)
	{
		for (Point p : vec)
		{
			ofVec3f pos(p.x, p.y, 0.0);
			mesh.addVertex(pos);
			mesh.addColor(ofColor(0, 0, 0));
		}
	}

	meshMat = toCv(mesh);
}

void swarming::edge_detector()
{
	findContours(fgMask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//hull = std::vector<std::vector<Point>>(contours.size());
	approx = std::vector<std::vector<Point>>(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		//convexHull(Mat(contours[i]), hull[i], false);
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
			drawContours(drawing, approx, int(i), color_hull, 2, LINE_8, hierarchy, 0);
		}
	}
}

void swarming::backSubKNN(Mat frame)
{
	cvtColor(frame, frame, COLOR_BGR2GRAY);
	//frame.convertTo(frame, -1, 0.5, 0);
	//GaussianBlur(frame, frame, Size(3, 3), 0);
	pBackSub->apply(frame, fgMask);
}
