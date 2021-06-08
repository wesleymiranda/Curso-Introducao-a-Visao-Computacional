#include<iostream>
#include<locale>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


std::string tipo_em_string(int tipo) {

	std::string result;
	int bits_per_pixel = tipo & CV_MAT_DEPTH_MASK;

	switch (bits_per_pixel) {
	case CV_8U:  result = "8U"; break;
	case CV_8S:  result = "8S"; break;
	case CV_16U: result = "16U"; break;
	case CV_16S: result = "16S"; break;
	case CV_32S: result = "32S"; break;
	case CV_32F: result = "32F"; break;
	case CV_64F: result = "64F"; break;
	default:     result = "User"; break;
	}

	result += "C";

	int canais = 1 + (tipo >> CV_CN_SHIFT);
	result += to_string(canais);

	return result;
}



int main() {

	setlocale(LC_ALL, "Portuguese");
	std::string filePath = "imagens/carro.jpg";
	
	Mat img = imread(filePath,0);

	if (img.data == nullptr) {
		cerr << "ERRO::Não foi possivel carregar a imagem "<< filePath<<" \n\n";
	}


	std::cout << tipo_em_string(62) << std::endl;

	imshow("Imagem", img);

	waitKey(0);

	return 0;
}