#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;

int main() {

    uchar data[] = {
     2 , 1 , 2 , 3 , 5 , 5,
     3 , 3 , 0 , 0 , 2 , 1,
     6 , 7 , 7 , 3 , 2 , 4,
     4 , 5 , 2 , 1 , 3 , 4,
     5 , 5 , 0 , 0 , 1 , 2,
     0 , 7 , 3 , 4 , 7 , 7
    };

    Mat img(6, 6, CV_8UC1, data);
    Mat hist = Mat::zeros(8, 1, CV_32F);
    
    for (int i = 0; i < img.rows; i++)
        for (int j = 0; j < img.cols; j++) {
            int pixel_value = img.at<uchar>(i, j);
            hist.at<float>(pixel_value)++;
        }
    std::cout << img << std::endl << std::endl;
    std::cout << hist.t() << std::endl;
 
    std::cin.get();
    return 0;
}

