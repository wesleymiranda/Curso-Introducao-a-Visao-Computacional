#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

//CONVOLUÇÃO!!

enum class conv { SAME, FULL };

void convolve1D(cv::Mat src, cv::Mat& dst, cv::Mat kernel, conv type = conv::SAME) {

    cv::flip(kernel, kernel, 1);
    int border = CV_HAL_BORDER_CONSTANT;
    cv::Point anchor(-1, -1);

    if (type == conv::SAME)
        cv::filter2D(src, dst, src.depth(), kernel, anchor, 0.0, border);
    else if (type == conv::FULL) {
        unsigned extra = kernel.cols - 1;
        cv::copyMakeBorder(src, src, 0, 0, extra / 2, extra / 2, border, cv::Scalar(0));
        cv::filter2D(src, dst, src.depth(), kernel, anchor, 0.0, border);
    }
}

void convolve2D(cv::Mat src, cv::Mat& dst, cv::Mat kernel, conv type = conv::SAME) {

    cv::flip(kernel, kernel, -1);
    int border = CV_HAL_BORDER_CONSTANT;
    cv::Point anchor(-1, -1);

    if (type == conv::SAME)
        cv::filter2D(src, dst, src.depth(), kernel, anchor, 0.0, border);
    else if (type == conv::FULL) {
        unsigned extra_rows = kernel.rows - 1;
        unsigned extra_cols = kernel.cols - 1;
        cv::copyMakeBorder(src, src, extra_rows/2, extra_rows/2, extra_cols / 2, extra_cols / 2, border, cv::Scalar(0));
        cv::filter2D(src, dst, src.depth(), kernel, anchor, 0.0, border);
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    float src_data[] = { 2, 3, 1, 1, 7, 2, 1, 3, 0};
    float kernel_data[] = {2, 0, 3, 1, 0, 1, 0, 2, 2};

    cv::Mat src(3, 3, CV_32FC1, src_data);
    cv::Mat kernel(3, 3, CV_32FC1, kernel_data);

    cv::Mat result;
    //cv::filter2D(src, result, src.depth(), kernel);
    convolve2D(src, result, kernel, conv::FULL);

    src.convertTo(src, CV_8U);
    kernel.convertTo(kernel, CV_8U);
    result.convertTo(result, CV_8U);

    std::string janelas[] = { "Imagem","Kernel", "Convolution" };
    cv::namedWindow(janelas[0], cv::WINDOW_GUI_NORMAL);
    cv::namedWindow(janelas[1], cv::WINDOW_GUI_NORMAL);
    cv::namedWindow(janelas[2], cv::WINDOW_NORMAL);

    cv::imshow(janelas[0], src);
    cv::imshow(janelas[1], kernel);
    cv::imshow(janelas[2], result);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;

}
