#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(){
    vector<String> cor; // vetor de strings com endereços de imagens
    glob("/home/victor/Área de Trabalho/OpenCV_Codes/img/aula1.jpg", cor , false);

    Mat orig = imread(cor[0], CV_LOAD_IMAGE_COLOR);
    Mat canais[3];

    if(!orig.data){
        cout<<"Nao abriu imagem."<<endl;
        return 0;
    }
    split(orig, canais); // split(imagem origem, vetor de imagens destino);

    imshow("B", canais[0]);//Cada imagem resultante é monocromática, mas não é cinza
    imshow("G", canais[1]);//Por exemplo, essa imagem tem apenas tons de verde
    imshow("R", canais[2]);//Porém o OpenCV exibe imagens monocromáticas em escalas de cinza
    waitKey();

    canais[2] = Mat::zeros(canais[2].size(), CV_8UC1); // retira os tons de vermelho

    Mat saida; //Irei mesclar duas imagens monocromáticas e guardar aqui

    merge(canais, 3, saida); // merge(vetor de imagem, tamanho do vetor, imagem destino);

    imshow("Resultado", saida); // 
    waitKey();

    return 0;
}