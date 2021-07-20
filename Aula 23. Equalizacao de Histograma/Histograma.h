#pragma once
#include<opencv2/opencv.hpp>
#include<string>

class Histograma
{
private:
	cv::Mat img_src;
	cv::Mat hist;
	cv::Mat freq_acumulada;
	cv::Mat hist_img;
	cv::Mat cdf_img;
	unsigned level;
	void plot_hist(std::string nome);
	void plot_cdf(std::string nome);
public:
	Histograma(unsigned L);
	void create(const cv::Mat& img);
	cv::Mat equalizer();
	void print();
	inline cv::Mat get_hist() { return this->hist_img; }
	inline cv::Mat get_cdf() { return this->cdf_img; }
};

