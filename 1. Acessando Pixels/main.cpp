#include<iostream>
#include <locale>
#include<cstdlib>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main() {
	setlocale(LC_ALL, "Portuguese");
	std::string filePath = "imagens/carro.jpg";
	Mat img = imread(filePath, IMREAD_UNCHANGED);

	if (img.data == nullptr) {
		cerr << "ERRO::Não podemos carregar a imagem " << filePath << "\n\n";
		exit(EXIT_FAILURE);
	}


	imshow("Imagem", img);

	waitKey(0);

	return 0;

}