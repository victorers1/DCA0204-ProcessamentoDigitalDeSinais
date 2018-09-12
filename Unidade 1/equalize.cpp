/**
 * Descrição do exercício: https://agostinhobritojr.github.io/tutorial/pdi/#_exerc%C3%ADcios_3
 */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat criaHist(Mat const imagem, int bins){
    int histSize[] = {bins}; // 

    float lranges[] = {0, 256}; // Vetor de float com os valores lranges[0] = 0.0 e lranges[1] = 256.0
    const float* ranges[] = {lranges}; // Ponteiro para um vetor de float inicializado com o valor ranges[0] = &lranges

    Mat hist;
    int channels[]={0}; // Vetor de inteiros inicializado com channels[0] = 0 e só

    
    calcHist(&imagem, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);
    return hist;
}

Mat3b histImage(Mat const hist, int bins){
    int const hist_height = 256;
    Mat3b hist_image = Mat3b::zeros(hist_height, bins); // Matriz na qual cada pixels tem 3 Bytes inicializada com 0 em todas posições
                                               //bins = largura do histograma

    double max_val = 0;
    minMaxLoc(hist, 0, &max_val);

    // Imprimindo cada retângulo no fundo preto
    for(int b=0; b<256; b++){
        float const binVal = hist.at<float>(b);
        int const height = cvRound(binVal*hist_height/max_val);
        line(hist_image, Point(b, hist_height-height),
         Point(b, hist_height), Scalar::all(255));  
    }
    return hist_image;
}

float* operaVetor(float vet1[], float vet2[], int tam, int op){
    float* res = new float[tam];
    if(op==0){
        for(int i=0; i<tam; i++){
            res[i] = vet1[i]+vet2[i];
        }
    } else if(op==1){
        for(int i=0; i<tam; i++){
            res[i] = vet1[i]-vet2[i];
        }
    } else if(op==2){
        for(int i=0; i<tam; i++){
            res[i] = vet1[i]*vet2[i];
        }
    } else if(op==3){
        for(int i=0; i<tam; i++){
            res[i] = vet1[i]/vet2[i]; // OBS.: Divisão inteira
        }
    } else{
        return NULL;
    }
    return res;
}

float* operaElement(float vet[], int tam, float elem, int op){
    float* res = new float[tam];
    if(op==0){
        for(int i=0; i<tam; i++){
            res[i] = vet[i]+elem;
        }
    } else if(op==1){
        for(int i=0; i<tam; i++){
            res[i] = vet[i]-elem;
        }
    } else if(op==2){
        for(int i=0; i<tam; i++){
            res[i] = vet[i]*elem;
        }
    } else if(op==3){
        for(int i=0; i<tam; i++){
            res[i] = vet[i]/elem; // OBS.: Divisão inteira
        }
    } else{
        return NULL;
    }
    return res;

}

int* histAcum(Mat const hist, int t){ // Retorna o histograma acumulado. Recebe um vetor de inteiros e seu tamanho
    int* vetor = new int[t]; // Aloca dinamicamente um vetor de inteiros com tamanho 't'
    vetor[0] = hist.at<float>(0);
    for(int i=1; i<t; i++) vetor[i] = (int) hist.at<float>(i) + vetor[i-1];
    
    return vetor;
}

Mat equaliza(Mat const& imagem, Mat const hist, int tamHist){
    Mat equalizado(imagem.size(), sizeof(uchar));
    double hist_acum[tamHist], qtdPixels = imagem.rows*imagem.cols; // qtdPixels pode ser 'int' ou 'float'
    hist_acum[0] = hist.at<float>(0);
    for(int i=1; i<tamHist; i++){
        hist_acum[i] = hist.at<float>(i) + hist_acum[i-1]; // histograma de probabilidades acumuladas
    }
    cout<<"hist.prob= ";
    for(int i=0; i<tamHist; i++){
        cout<<hist.at<float>(i)<<" ";
    }
    cout<<"\n\nacum= ";
    for(int i=0; i<tamHist; i++){
        hist_acum[i] = hist_acum[i]/hist_acum[tamHist-1];
        cout<<hist_acum[i]<<" ";
    }

    for(int x = 0; x<imagem.rows; x++){
        for(int y = 0; y<imagem.cols; y++){
            equalizado.at<uchar>(x,y) = (int) hist_acum[imagem.at<uchar>(x,y)];
        }
    }
    return equalizado;
}

int main(){
    vector<String> end;
    glob("/home/victor/Área de Trabalho/OpenCV_Codes/img/Ursos.jpg", end, false);

    Mat imagem = imread(end[0], CV_LOAD_IMAGE_GRAYSCALE);
    Mat hist_original = criaHist(imagem, 256);
    Mat equalizado = equaliza(imagem, hist_original, 256);

    imshow("Original", imagem);
    imshow("Histograma do original", histImage(hist_original, 256));
    imshow("Imagem Equalizada", equalizado);
    imshow("Histograma da equalizada", histImage(equalizado, 256));
    waitKey();
    return 0;
}