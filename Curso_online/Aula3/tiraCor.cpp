#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    vector<String> endImg;
   	glob("/home/victor/Área de Trabalho/OpenCV_Codes/img/aula1.jpg", endImg, false); // define o endereço global da imagem

    Mat corMuda = imread(endImg[0], CV_LOAD_IMAGE_COLOR);
    Mat original = imread(endImg[0], CV_LOAD_IMAGE_COLOR);

    cout<< corMuda.at<Vec3b>(0,0)[1]<<endl;

    for(int r=0; r<corMuda.rows; r++){
        for(int c=0; c<corMuda.cols; c++){
            corMuda.at<cv::Vec3b>(r,c)[0] = 0; // Retira tons de azul
            
            //corMuda.at<cv::Vec3b>(r,c)[1] = 0; // Retira tons de Verde
            //corMuda.at<cv::Vec3b>(r,c)[2] = 0; // Retira tons de Vermelho
        }
    }
    imshow("Original", original);
    imshow("Modificada", corMuda);
    waitKey();


    return 0;
}