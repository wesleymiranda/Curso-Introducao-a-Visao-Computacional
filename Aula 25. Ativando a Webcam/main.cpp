#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {

	vector<int> CamerasDisponiveis;
	for (int i = 0; i < 20; i++) {
		VideoCapture cap(i);
		if (cap.isOpened())
			CamerasDisponiveis.push_back(i);
	}
	system("CLS");
	std::cout << "ESTAO DISPONIVEIS AS CAMERAS NOS INDICES: ";
	for(int i = 0; i<CamerasDisponiveis.size(); i++)
		cout << CamerasDisponiveis[i] << ", ";

	enum {WEBCAM = 0, CELULAR = 2};

	VideoCapture cap1(WEBCAM);
	VideoCapture cap2(CELULAR);
	system("CLS");


	Mat frame1, frame2;

	while (waitKey(10)) {
		cap1 >> frame1;
		cap2 >> frame2;

		flip(frame1, frame1, 1);
		cvtColor(frame1, frame1, COLOR_RGB2GRAY);
		cvtColor(frame2, frame2, COLOR_RGB2GRAY);
		

		imshow("WEBCAM", frame1);
		imshow("CELULAR", frame2);
	}

	return 0;

}