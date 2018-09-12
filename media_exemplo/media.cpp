#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void div(Mat im, int d){
  for(int x=0; x<im.rows; x++){
    for(int y=0; y<im.cols; y++){
      im.at<uchar>(x,y)/=d;
    }
  }
}

void somaElement(Mat im, int d){ // Soma cada elemento da matriz por d
  for(int x=0; x<im.rows; x++){
    for(int y=0; y<im.cols; y++){
      im.at<uchar>(x,y)+=d;
    }
  }
}

void somaMatriz(Mat im1, Mat im2){ // im1 e im2 devem obrigatoriamente ter mesmo tamanho
  for(int x=0; x<im1.rows; x++){
    for(int y=0; y<im1.cols; y++){
      im1.at<uchar>() += im2.at<uchar>(x,y);
    }
  }
}

void subtMatriz(Mat im1, Mat im2){
  for(int x=0; x<im1.rows; x++){
    for(int y=0; y<im1.cols; y++){
      im1.at<uchar>(x,y) -= im2.at<uchar>(x,y);
    }
  }
}

int main(){
  Mat image; // Matriz de contúdo temporário
  VideoCapture cap;
  int ind=0, qFrames=120; // Qtd. de frames
  vector<Mat> frames; 
  frames.resize(qFrames, Mat::zeros(480, 640, sizeof(uchar))); // Vetor de matrizes com 30 posições
  Mat media = Mat::zeros(frames[0].size(), sizeof(uchar)); // Matriz com a média dos 30 frames


  cap.open(0);

  for(int i=0; i<qFrames; i++){
    cap >> frames[i];
    cvtColor(frames[i], frames[i], CV_RGB2GRAY); // Transforma "image" numa imagem em escala de cinza
    div(frames[i], qFrames);
  }

  for(int i=0; i<qFrames; i++){
    somaMatriz(media, frames[i]);
  }

  while(1){
    cap >> image;
    cvtColor(image, image, CV_RGB2GRAY); // Transforma "image" numa imagem em escala de cinza

    subtMatriz(media, frames[ind]);
    div(image, qFrames); frames[ind] = image; // entra[ind] = temp/3;
    somaMatriz(media, frames[ind]);
    ind = ind++;
    ind = ind%qFrames;

    imshow("imagem", media);
    if(waitKey(30) >= 0) break;
  }
  
  return 0;
}
