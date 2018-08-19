#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    //Carregando uma imagem localizada numa outra pasta qualquer
	vector<String> fn;
	glob("/home/victor/Área de Trabalho/OpenCV_testes/img/aula1.jpg", fn, false);


    Mat colorida = imread(fn[0],CV_LOAD_IMAGE_COLOR); //carrega imagem com cores
    Mat cinza = imread(fn[0], CV_LOAD_IMAGE_GRAYSCALE); // carrega imagem sem cores

    namedWindow("ajusta", CV_WINDOW_FREERATIO); // define janela ajustável
    namedWindow("fixo", CV_WINDOW_AUTOSIZE); // define janela de tamanho fixo

    imshow("ajusta", colorida); // mostra imagem de nome "colorida" na janela ajustável
    imshow("fixo", cinza); // mostra imagem de nome "cinza" na janela fixa

    resizeWindow("ajusta", colorida.cols/2, colorida.rows/2);
    resizeWindow("fixo", cinza.cols/2, cinza.rows/2);

    waitKey();

    return 0;
}