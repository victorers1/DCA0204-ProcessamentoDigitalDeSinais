#include<opencv2/opencv.hpp>
#include <iostream>
#include <stdint.h>

using namespace cv;
using namespace std;

int main(){
    //Carregando uma imagem localizada numa outra pasta qualquer
	vector<String> cinza, cor;
	glob("/home/victor/Área de Trabalho/OpenCV_Codes/img/biel.png", cinza, false);
    glob("/home/victor/Área de Trabalho/OpenCV_Codes/img/aula1.jpg", cor, false);

    Mat orig = imread(cinza[0], CV_LOAD_IMAGE_GRAYSCALE); //carrega imagem monocromática
    Mat modif = imread(cinza[0], CV_LOAD_IMAGE_GRAYSCALE);//carrega mesma imagem, mas essa será modificada
    Mat naoMuda = imread(cor[0], CV_LOAD_IMAGE_COLOR);
    Mat corMuda = imread(cor[0], CV_LOAD_IMAGE_COLOR);
    Vec3b pincel;

    if(!orig.data || !modif.data || !naoMuda.data || !corMuda.data){
        cout<<"Nao abriu uma das imagens\n";
        return 0;
    }

    //Modificando imagem monocromática
    for(int r=0; r<modif.rows; r++){
        for(int c=0; c<modif.cols; c++){
            modif.at<uint8_t>(r,c) = 255 - modif.at<uint8_t>(r,c);
        }
    }

    imshow("Original", orig);
    imshow("Modificado", modif);
    waitKey();
    
    return 0;
}