#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

using namespace cv;

void backSubMOG2KNN(std::string model)
{
	Ptr<BackgroundSubtractor> pBackSub;
	if (model == "MOG2")
		pBackSub = createBackgroundSubtractorMOG2();
	else if (model == "KNN")
		pBackSub = createBackgroundSubtractorKNN();
	VideoCapture capture("swarming_even_smaller.mp4");
	Mat frame, fgMask;
	Mat thresh;

	while (true)
	{
		capture >> frame;
		if (frame.empty())
			break;

		//cvtColor(frame, frame, COLOR_BGR2GRAY);
		//GaussianBlur(frame, frame, Size(1, 1), 0);
		pBackSub->apply(frame, fgMask);

		rectangle(frame, Point(10, 2), Point(100, 20), Scalar(255, 255, 255), -1);
		std::stringstream ss;
		ss << capture.get(CAP_PROP_POS_FRAMES);
		std::string frameNumberString = ss.str();
		putText(frame, frameNumberString.c_str(), Point(15, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));

		imshow("Frame", frame);
		imshow("FG Mask", fgMask);

		int keyboard = waitKey(30);
		if (keyboard == 'q' || keyboard == 27)
			break;

		thresh = threshold(fgMask, thresh, 150, 255, THRESH_BINARY);

		std::vector<std::vector<Point>> contours;
		std::vector<Vec4i> hierarchy;
		findContours(thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

		Mat image_copy = fgMask.clone();
		drawContours(image_copy, contours, -1, Scalar(0, 255, 0), 2);
		imshow("None approximation", contours);
	}
}



int main(int argc, char* argv[]) 
{
	backSubMOG2KNN("KNN");
	return 0;
}