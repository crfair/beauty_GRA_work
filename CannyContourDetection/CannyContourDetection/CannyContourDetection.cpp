#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;

Mat src_gray; // our image to detect contours on in grayscale
int thresh = 100;

static void threshold_callback(int, void*)
{
	Mat canny_output;
	Canny(src_gray, canny_output, thresh, thresh * 2);

	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;
	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		drawContours(drawing, contours, (int)i, Scalar(255, 255, 255), 1, LINE_8, hierarchy, 0);
	}

	imshow("Contours", drawing);
}

int main(int argc, char** argv)
{
	Mat src = imread(samples::findFile("bacteria.jpg"), IMREAD_COLOR);

	if (src.empty())
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
		return -1;
	}

	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	const char* source_window = "Source";
	namedWindow(source_window);
	imshow(source_window, src);

	const int max_thresh = 255;
	createTrackbar("Canny threshold: ", source_window, &thresh, max_thresh, threshold_callback);
	threshold_callback(0, 0);

	waitKey();
	return 0;
}