#include<iostream>
#include<opencv2/opencv.hpp>
#include"Histograma.h"

using namespace cv;

int main() {

    Mat img = imread("imagens/garota.png", IMREAD_GRAYSCALE);

    std::string janela[] = { "Imagem Original", "Histograma da Imagem", "Freq. Acumulada",
                             "Nova Imagem", "Novo Histograma", "Nova Freq. Acumulada"};

    Histograma histograma(256);
    histograma.create(img);
    Mat hist_img = histograma.get_hist();
    Mat cdf_img = histograma.get_cdf();

    Mat img_eq = histograma.equalizer();
    histograma.create(img_eq);
    Mat new_hist = histograma.get_hist();
    Mat new_cdf = histograma.get_cdf();

    namedWindow(janela[0], WINDOW_GUI_NORMAL);
    namedWindow(janela[1], WINDOW_GUI_NORMAL);
    namedWindow(janela[2], WINDOW_GUI_NORMAL);

    namedWindow(janela[3], WINDOW_GUI_NORMAL);
    namedWindow(janela[4], WINDOW_GUI_NORMAL);
    namedWindow(janela[5], WINDOW_GUI_NORMAL);

    imshow(janela[0], img);
    imshow(janela[1], hist_img);
    imshow(janela[2], cdf_img);

    imshow(janela[3], img_eq);
    imshow(janela[4], new_hist);
    imshow(janela[5], new_cdf);

    waitKey(0);

    return 0;
}

