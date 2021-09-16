//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <iostream>
//
//using namespace cv;
//
//// The Mat class represents an n-dimensional dense numerical single-channel or multi-channel array
//// It can be used to store real or complex-valued vectors and matrices, grayscale or color images, voxel volumes, etc. etc. etc.
//// In this case, these Mats store the source image, the source image in grayscale, a destination output array, and the image of the detected edges
//Mat src, src_gray;
//Mat dst, detected_edges;
//
//// here we establish the max bounds of the threshold variable and the lower:upper threshold of 3:1 with the ratio variable
//// kernel size set to three for the sobel operations performed by the canny function
//int lowThreshold = 0;
//const int max_lowThreshold = 100;
//const int ratio = 3;
//const int kernel_size = 3;
//const char* window_name = "Edge Map";
//
//static void CannyThreshold(int, void*) 
//{
//	blur(src_gray, detected_edges, Size(3, 3)); // blur the image with a filter of kernel size 3
//
//	 // takes (source image in grayscale, output of the detector, user threshold value, high threshold (rec 3 times low threshold), kernel size)
//	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size);
//
//	dst = Scalar::all(0); // fills dst with zeros (completely black image)
//
//	src.copyTo(dst, detected_edges); // maps ONLY the areas of the given image that are identified as edges onto the black background
//
//	imshow(window_name, dst); // display results
//}
//
//int main(int argc, char** argv)
//{
//	// CommandLineParser parser(argc, argv, "{@input | bacteria.jpg | input image}");
//	src = imread(samples::findFile("bacteria.jpg", IMREAD_COLOR));
//
//	// if file could not be found, exit with error
//	if (src.empty())
//	{
//		std::cout << "Could not open or find the image!\n" << std::endl;
//		std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
//		return -1;
//	}
//
//	dst.create(src.size(), src.type()); // set destination as a matrix of the same type and size as src
//
//	// convert src to grayscale, save in src_gray
//	cvtColor(src, src_gray, COLOR_BGR2GRAY);
//
//	// create the window to display our results
//	namedWindow(window_name, WINDOW_AUTOSIZE);
//
//	// create a trackbar that the user can use to enter the lower threshold for the canny detector
//	createTrackbar("Min Threshold: ", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
//
//	// do some edge detection
//	CannyThreshold(0, 0);
//
//	// this function waits for the user to manually end the program
//	waitKey(0);
//
//	return 0;
//}

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