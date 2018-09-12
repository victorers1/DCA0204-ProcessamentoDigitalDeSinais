#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void show_histogram(string const& name, Mat const& image){
    // Set histogram bins count
    int bins = 256;
    int histSize[] = {bins};
    // Set ranges for histogram bins
    float lranges[] = {0, 256};
    const float* ranges[] = {lranges};
    // create matrix for histogram
    Mat hist;
    int channels[] = {0};

    // create matrix for histogram visualization
    int const hist_height = 256;
    Mat3b hist_image = Mat3b::zeros(hist_height, bins);

    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);

    double max_val=0;
    minMaxLoc(hist, 0, &max_val);

    // visualize each bin
    for(int b = 0; b < bins; b++) {
        float const binVal = hist.at<float>(b);
        int   const height = cvRound(binVal*hist_height/max_val);
        cv::line
            ( hist_image
            , Point(b, hist_height-height), Point(b, hist_height)
            , Scalar::all(255)
            );
    }
    imshow(name, hist_image);
}

int main (int argc, const char* argv[]){
    // here you can use cv::IMREAD_GRAYSCALE to load grayscale image, see image2
    vector<String> endImg;
    glob("/home/victor/Área de Trabalho/OpenCV_Codes/img/*.png", endImg, false);

    Mat3b const image1 = imread(endImg[0], IMREAD_COLOR);
    Mat image1_gray;
    cvtColor(image1, image1_gray, COLOR_BGR2GRAY);
    imshow("image1", image1_gray);
    show_histogram("image1 hist", image1_gray);

    Mat const image2 = imread(endImg[1], IMREAD_GRAYSCALE);
    imshow("image2", image2);
    show_histogram("image2 hist", image2);

    waitKey();
    return 0;
}