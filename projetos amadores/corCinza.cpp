#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    vector<String> end;
    glob("/home/victor/Área de Trabalho/OpenCV_Codes/img/aula1.jpg", end, false);
    Vec3b pincel;

    Mat cinza = imread(end[0], CV_LOAD_IMAGE_GRAYSCALE);
    Mat cor = imread(end[0], CV_LOAD_IMAGE_COLOR);
    Mat descolor = Mat(cor.rows, cor.cols, sizeof(uchar));
    int azul, verm, verd, media;
    
    for(int y=0; y<cor.cols; y++){
        for(int x=0; x<cor.rows; x++){
            azul = cor.at<cv::Vec3b>(x,y)[0]; // Azul
            verm = cor.at<cv::Vec3b>(x,y)[1]; // Vermelho
            verd = cor.at<cv::Vec3b>(x,y)[2]; // Verde
            
            media = (azul+verm+verd)/3; // Faz a média dos tons RGB
            descolor.at<uchar>(x,y) = media; // E guarda na nova imagem
        }
    }

    imshow("Original", cor);
    imshow("Cinza", cinza);
    imshow("Descolorida", descolor);
    waitKey();


    return 0;
}