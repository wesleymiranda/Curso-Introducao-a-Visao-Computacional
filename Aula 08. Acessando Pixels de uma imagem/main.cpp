#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;

void print_pixel_val(int row, int col, const Mat& img) {

	Vec3b valor_pixel =  img.at<Vec3b>(row, col);
	std::cout<<"\n Valor do Pixel("<<row<<","<<col<<")="<<valor_pixel<<std::endl;
}

int main() {

	Mat img = imread("small_img.png", IMREAD_COLOR);
	
	std::cout << "Dimensao:"<<img.size() << std::endl;
	std::cout << "Largura : " << img.size().width << std::endl;
	std::cout << "Altura : " << img.size().height << std::endl << std::endl;

	img.at<Vec3b>(1, 3) = Vec3b(100,100,100);
	std::cout << img << std::endl;

	print_pixel_val(1, 3, img);

	std::cin.get();

	return 0;
}