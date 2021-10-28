#include "swarming.h"

void swarming::setup()
{	
	pBackSub = createBackgroundSubtractorKNN(5000, 150.0, false);
	//VideoCapture capture("../bin/data/swarming_even_smaller.mp4");
	vidPlayer.load("swarming_even_smaller.mp4");
	vidPlayer.play();
	vidPlayer.setLoopState(OF_LOOP_NORMAL);

	ofFrame.allocate(640, 480, OF_IMAGE_COLOR);
	ofFrame.allocate(640, 480, OF_IMAGE_COLOR);
}

void swarming::update()
{	
	vidPlayer.update();
	frame = toCv(vidPlayer.getPixels());

	if (frame.empty())
		return;

	backSubKNN(frame);
	edge_detector();
}

void swarming::draw()
{
	ofSetHexColor(0xffffff);
	drawMat(frame, 0, 0);
	drawMat(fgMask, 640, 0);
	drawMat(drawing, 0, 480);
}

void swarming::pointsTo3D()
{

}

void swarming::edge_detector()
{
	findContours(fgMask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	hull = std::vector<std::vector<Point>>(contours.size());
	for (int i = 0; i < contours.size(); i++)
		convexHull(Mat(contours[i]), hull[i], false);
	drawing = Mat::zeros(fgMask.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++)
	{
		bounds = boundingRect(contours[i]);

		if (contourArea(contours[i]) > 200.0)
		{
			rectangle(drawing, bounds, color_bounds);
			drawContours(drawing, contours, int(i), color_contours, 2, LINE_8, hierarchy, 0);
			drawContours(drawing, hull, int(i), color_hull, 2, LINE_8, hierarchy, 0);
		}
	}
}

void swarming::backSubKNN(Mat frame)
{
	//cvtColor(frame, frame, COLOR_BGR2GRAY);
	//frame.convertTo(frame, -1, 0.5, 0);
	//GaussianBlur(frame, frame, Size(3, 3), 0);
	pBackSub->apply(frame, fgMask);
}
