#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

using namespace cv;

Mat frame, fgMask;
int thresh = 200;

void edge_detector()
{
	/*Mat canny_output;
	Canny(fgMask, canny_output, thresh, thresh * 2);

	imshow("Canny", canny_output);*/

	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;
	findContours(fgMask, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	//std::vector<std::vector<Point>> hull(contours.size());
	//for (int i = 0; i < contours.size(); i++)
	//	convexHull(Mat(contours[i]), hull[i], false);
	Mat drawing = Mat::zeros(fgMask.size(), CV_8UC3);
	
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color_contours = Scalar(0, 255, 0);
		//Scalar color_hull = Scalar(255, 0, 0);
		Scalar color_bounds = Scalar(0, 0, 255);

		Rect bounds = boundingRect(contours[i]);

		if (contourArea(contours[i]) > 150.0)
		{
			rectangle(drawing, bounds, color_bounds);
			drawContours(drawing, contours, int(i), color_contours, 2, LINE_8, hierarchy, 0);
			//drawContours(drawing, hull, int(i), color_hull, 2, LINE_8, hierarchy, 0);
		}
	}

	imshow("Contours", drawing);
}

void backSubMOG2KNN(std::string model)
{
	Ptr<BackgroundSubtractor> pBackSub;
	if (model == "MOG2")
		pBackSub = createBackgroundSubtractorMOG2(50, 100, false);
	else if (model == "KNN")
		pBackSub = createBackgroundSubtractorKNN(500, 100.0, false);
	VideoCapture capture("backgroundSubtraction/swarming_even_smaller.mp4");

	while (true)
	{
		capture >> frame;
		if (frame.empty())
			break;

		cvtColor(frame, frame, COLOR_BGR2GRAY);
		GaussianBlur(frame, frame, Size(3, 3), 0);
		pBackSub->apply(frame, fgMask);

		rectangle(frame, Point(10, 2), Point(100, 20), Scalar(255, 255, 255), -1);
		std::stringstream ss;
		ss << capture.get(CAP_PROP_POS_FRAMES);
		std::string frameNumberString = ss.str();
		putText(frame, frameNumberString.c_str(), Point(15, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));

		const char* src_window = "Frame";
		namedWindow("Frame");
		imshow(src_window, frame);
		imshow("FG Mask", fgMask);

		edge_detector();

		int keyboard = waitKey(30);
		if (keyboard == 'q' || keyboard == 27)
			break;
	}
}

int main(int argc, char* argv[]) 
{
	backSubMOG2KNN("KNN");
	return 0;
}