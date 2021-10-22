#include "swarming.h"

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

	imshow("Contours", drawing);
}

void swarming::backSubKNN()
{
	pBackSub = createBackgroundSubtractorKNN(5000, 150.0, false);
	//VideoCapture capture("../bin/data/swarming_even_smaller.mp4");
	vidPlayer.load("swarming_even_smaller.mp4");
	// vidPlayer.setLoopState(OF_LOOP_NORMAL);

	while (true)
	{
		vidPlayer.update();

		frame = toCv(vidPlayer.getPixels()).clone();

		if (frame.empty())
			break;

		imshow("Frame", frame);

		cvtColor(frame, frame, COLOR_BGR2GRAY);
		//frame.convertTo(frame, -1, 0.5, 0);
		//GaussianBlur(frame, frame, Size(3, 3), 0);
		pBackSub->apply(frame, fgMask);

		rectangle(frame, Point(10, 2), Point(100, 20), Scalar(255, 255, 255), -1);
		ss << capture.get(CAP_PROP_POS_FRAMES);
		putText(frame, frameNumberString.c_str(), Point(15, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));

		imshow("Frame", frame);
		imshow("FG Mask", fgMask);

		edge_detector();

		int keyboard = waitKey(30);
		if (keyboard == 'q' || keyboard == 27)
			break;
	}
}
