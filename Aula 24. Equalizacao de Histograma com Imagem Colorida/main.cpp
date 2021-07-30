#include <opencv2/opencv.hpp>

using namespace cv;

Mat eq_RGB(Mat img_src) {
	
	std::vector<Mat> canais, canais_eq;
	split(img_src, canais);

	for (int i = 0; i < 3; i++) {
		Mat dst(img_src.rows, img_src.cols, CV_8UC1);
		equalizeHist(canais[i], dst);
		canais_eq.push_back(dst);
	}

	Mat result;
	merge(canais_eq, result);
	return result;
}

Mat eq_HSV(Mat img_src) {
	std::vector<Mat> canais;
	Mat img_HSV;
	cvtColor(img_src, img_HSV, COLOR_BGR2HSV);
	split(img_HSV, canais);

	equalizeHist(canais[2], canais[2]);

	merge(canais, img_HSV);

	Mat result;
	cv::cvtColor(img_HSV, result, COLOR_HSV2BGR);
	return result;
}


int main() {

	std::string janelas[] = { "Imagem Original", "Imagem Equalizada RGB", "Imagem Equalizada HSV"};
	Mat img = imread("imagens/noite.jpg");
	
	Mat img_equalized_RGB = eq_RGB(img);
	Mat img_equalized_HSV = eq_HSV(img);

	namedWindow(janelas[0], WINDOW_GUI_NORMAL);
	namedWindow(janelas[1], WINDOW_GUI_NORMAL);
	namedWindow(janelas[2], WINDOW_GUI_NORMAL);

	imshow(janelas[0], img);
	imshow(janelas[1], img_equalized_RGB);
	imshow(janelas[2], img_equalized_HSV);

	waitKey(0);

	return 0;
}