#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const int ESC = 27;

int main() {
	VideoCapture cap("videos/ufr_video.mp4");

	std::string main_window = "Original";
	namedWindow(main_window, WINDOW_GUI_NORMAL);
	system("CLS"); 

	
	int total_frames = (int)cap.get(CAP_PROP_FRAME_COUNT);
	int fps = (int)cap.get(CAP_PROP_FPS);
	std::cout << "Total Frames: " << total_frames << "\n";
	std::cout << "FPS: " << fps << "\n";

	Mat frame_capturada;
	while (true) {
		cap >> frame_capturada;

		if (frame_capturada.empty())
		 break;

		imshow(main_window, frame_capturada);

		int key = waitKey(35);
		if (key == ESC)
			break;
	}

	cap.release();
	destroyAllWindows();
}
