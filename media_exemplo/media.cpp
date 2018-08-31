#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
/*
Mat mediaMat(vector<Mat> frames){
  int larg = frames[0].cols;
  int alt = frames[0].rows;
  int soma=0; 
  Mat media; // Média é uma matriz de inteiros

  for(int y=0; y<larg; y++){
    for(int x=0; x<alt; x++){
      soma=0;
      for(int i=0; i<frames.size(); i++){
        soma += frames[i].at<uchar>(x, y);
      }
      soma /= 30;
      media.at<uchar>(x,y) = soma;
    }
  }
  return Mat(1,1,sizeof(uchar));
}*/

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

Mat somaMatriz(Mat im1, Mat im2){ // im1 e im2 devem obrigatoriamente ter mesmo tamanho
  for(int x=0; x<im1.rows; x++){
    for(int y=0; y<im1.cols; y++){
      im1.at<uchar>() += im2.at<uchar>(x,y);
    }
  }
  return im1;
}

int main(){
  Mat image; // Matriz de contúdo temporário
  VideoCapture cap;
  int ind=0, qFrames=30; // Qtd. de frames
  vector<Mat> frames; 
  frames.resize(qFrames, Mat(640, 480, sizeof(uchar), 0)); // Vetor de matrizes com 30 posições
  Mat media = Mat(640, 480, sizeof(uchar), 0); // Matriz com a média dos 30 frames
  cap.open(0);
/*
  for(int i=0; i<qFrames; i++){
    cap >> frames[i];
    cvtColor(frames[i], frames[i], CV_RGB2GRAY); // Tramsforma "image" numa imagem em escala de cinza
    div(frames[i], qFrames);
  }*/
  /*for(int i=0; i<qFrames; i++){
    media = somaMatriz(media, frames[i]);
  }*/
  //imshow("media", media);
  //waitKey();
  while(1){
    cap >> image;
    cvtColor(image, image, CV_RGB2GRAY); // Tramsforma "image" numa imagem em escala de cinza
    imshow("imagem", image);
    if(waitKey(30) >= 0) break;
  }
  
  return 0;
}
