#include "opencv2/opencv.hpp"
#include <iostream>
#include <cstdio>
#include <string>

using namespace cv;
using namespace std;
// static void help()
// {
//     cout << "\nThis program demonstrates kmeans clustering.\n"
//             "It generates an image with random points, then assigns a random number of cluster\n"
//             "centers and uses kmeans to move those cluster centers to their representitive location\n"
//             "Call\n"
//             "./kmeans\n" << endl;
// }
int main(){
    //INICIALIZAÇÃO
    int K = 45;  // Número de clusters
    vector<String> end;
    glob("/home/victor/Área de Trabalho/OpenCV_Codes/img/letras.jpg", end, false);
    Mat imagem(Size(486, 614), CV_8UC1), segmentada(Size(486, 614), CV_8UC1), aberta(Size(486, 614), CV_8UC1);
    imagem = imread(end[0], CV_LOAD_IMAGE_GRAYSCALE); 
    resize(imagem, imagem, Size(486, 614));
    imshow("original", imagem);

    //SEGMENTAÇÃO
    threshold(imagem, segmentada, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);  //Segmentação por OTSU
    imshow("segmentada", segmentada);

    //ABERTURA (por precaução)
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(3,3), Point(1,1)); // Elemento estruturante é um elipse com raios 3 e 3. Centro do elemento é (0,0)
    morphologyEx(segmentada, aberta, MORPH_OPEN, element, Point(1,1));
    //namedWindow("aberta", CV_WINDOW_FREERATIO);
    imshow("aberta", aberta);
    imwrite("segmentada.jpg", aberta);

    
    // CONTANDO PIXELS PRETOS
    int histSize = 256;  float range[]={0, 256}; const float* histRange = {range};
    Mat histograma;
    calcHist(&aberta, 1, 0, Mat(), histograma, 1, &histSize, &histRange);

    //CLUSTERIZAÇÃO POR KMEANS
    int qtd_pontos = histograma.at<float>(0), qtd_dados=0;  // Quantidade de pixels pretos e quantidade de pontos na lista de dados
    cout<<"pontos pretos= "<<qtd_pontos<<endl;
    Mat centros, rotulos; // Matriz com centros dos clusters, Matriz com rótulos de todos os pontos
    Mat dados(qtd_pontos, 1, CV_32FC2); // pontos do R^2
    Vec2f pincel;
    for(int x=0; x<aberta.rows; x++){  // A matrix é percorrida no sentido de leitura 
        for(int y=0; y<aberta.cols; y++){
            if (aberta.at<uchar>(x,y) == 0){  // Coleta os pontos pretos
                pincel = {(float)x, (float)y}; // X representa a coordenada da linha
                dados.at<Vec2f>(qtd_dados,0) = pincel;
                qtd_dados++;
            }
        }
    }
    cout<<"qtd_dados= "<<qtd_dados<<endl;
    cout<<"lo ultimo pincel= "<<pincel<<endl;
    kmeans(dados, K, rotulos, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), 3, KMEANS_PP_CENTERS, centros);
    //TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0)

    // Recolher vogais e salvá-las
    vector<Mat> vogais;
    
    for(int i=0; i<K; i++){
        cout<<"centro "<<i<<": "<<centros.at<Vec2f>(i,0)<<" ";
        int x = centros.at<Vec2f>(i,0)[1];
        int y = centros.at<Vec2f>(i,0)[0];
        Mat vogal(aberta, Rect(x-29, y-29, 58, 58));
        //vogais.push_back(vogal);
        cout<<"ok\n";

        string str = "vogal " + to_string(i+45)+".jpg";
        resize(vogal, vogal, Size(25,25));
        imwrite(str, vogal);
    }
    
    waitKey();
    return 0;
}

/*
DEPÓSITO DE CÓDIGOS
for(int i=30; i<40; i++){
    cout<<"Ponto "<<i<<"= ("<< dados.at<float>(i,0)<<", "<<dados.at<float>(i,1)<<")\n";
}


//Mapa de cores: clustersID -> cor
    Scalar colorTab[] = {Scalar(0, 0, 255), // Azul
                         Scalar(0,255,0), // Verde
                         Scalar(255,0,0), // Vermelho
                         Scalar(255,0,255), // Rosa
                         Scalar(0,255,255), //Ciano
                         Scalar(255,255,0)}; // Amarelo
*/