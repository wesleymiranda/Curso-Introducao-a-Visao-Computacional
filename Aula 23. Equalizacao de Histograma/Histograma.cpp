#include "Histograma.h"
#include<iostream>
#include<fstream>


void Histograma::plot_hist(std::string nome)
{
    std::string destino = "set out '" + nome + "' \n";

    FILE* pipe = _popen("gnuplot", "w");
    fprintf(pipe,
        "reset session \n"
        "set term pngcairo dashed \n"
        "set style data histograms \n"
        "set border 3 \n"
        "set arrow from 128, graph 0 to 128, graph 1 nohead lw 2.5 lt 2 dt 3 \n"
        "set style fill solid 1.0 noborder \n");
    fprintf(pipe, destino.c_str());
    fprintf(pipe, "set xrange[0:%d]\n", this->level - 1);
    fprintf(pipe, "plot 'myhist.dat' using 1 notitle\n");

    _pclose(pipe);

}

void Histograma::plot_cdf(std::string nome)
{
    std::string destino = "set out '" + nome + "' \n";

    FILE* pipe = _popen("gnuplot", "w");
    fprintf(pipe,
        "reset session \n"
        "set term pngcairo dashed \n"
        "set title 'Cumulative Distribution Function(CDF)' \n"
        "set yrange[0:1]\n"
        "set ytics(1.0, 0.75, 0.5, 0.25, 0.0)\n"
        "set lmargin 9\n"
        "set rmargin 2\n"
        "set grid\n");
    fprintf(pipe, destino.c_str());
    fprintf(pipe, "set xrange[0:%d]\n", this->level - 1);
    fprintf(pipe, "plot 'myCDF.dat' using 1 notitle with lines\n");

    _pclose(pipe);


}

Histograma::Histograma(unsigned L)
{
    this->level = L;
    this->hist = cv::Mat::zeros(this->level, 1, CV_32F);
    this->freq_acumulada = cv::Mat::zeros(this->level, 1, CV_32F);
}

void Histograma::create(const cv::Mat& img)
{

    this->img_src = img.clone();

    std::string hist_name = "histograma_image.jpg";
    std::string cdf_name = "cdf_image.jpg";

    // Criar o histograma 
    for (int i = 0; i < img.rows; i++)
        for (int j = 0; j < img.cols; j++) {
            int pixel_value = img.at<uchar>(i, j);
            this->hist.at<float>(pixel_value)++;
        }

    // Criar Freq. Acumulada
    float soma_acumulada = 0.f;
    for (int i = 0; i < this->hist.rows; i++) {
        float valor = this->hist.at<float>(i);
        soma_acumulada += valor;
        this->freq_acumulada.at<float>(i) = soma_acumulada;
    }

    std::ofstream arq_hist("myhist.dat");
    std::ofstream arq_cdf("myCDF.dat");

    // Normaliza os dados
    float total = (float)(img.rows * img.cols);
    this->hist /= total;
    this->freq_acumulada /= total;

    for (int i = 0; i < this->hist.rows; i++) {
        arq_hist << this->hist.at<float>(i) << "\n";
        arq_cdf << this->freq_acumulada.at<float>(i) << "\n";
    }
    arq_hist.close();
    arq_cdf.close();

    plot_hist(hist_name);
    plot_cdf(cdf_name);

    this->hist_img = cv::imread(hist_name);
    this->cdf_img = cv::imread(cdf_name);

}

cv::Mat Histograma::equalizer()
{
    cv::Mat table(1, this->level, CV_32F);

    for (int i = 0; i < this->level; i++)
        table.at<float>(i) = this->freq_acumulada.at<float>(i) * (this->level - 1);
 
    table.convertTo(table, CV_8UC1);
    cv::Mat result;
    cv::LUT(this->img_src, table, result);

    return result;
}



void Histograma::print()
{
    std::cout << this->hist.t() << std::endl;
}