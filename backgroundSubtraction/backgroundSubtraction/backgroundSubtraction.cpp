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

	while (true)
	{
		capture >> frame;
		if (frame.empty())
			break;

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
	}
}

int main(int argc, char* argv[]) 
{
	backSubMOG2KNN("KNN");
	return 0;
}