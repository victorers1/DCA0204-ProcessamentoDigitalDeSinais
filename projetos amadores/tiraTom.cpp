#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main(){
  Mat image =Mat(480, 640, sizeof(uchar));
  VideoCapture cap; 
  cap.open(0);
  Mat canais[3];
  Mat descolor = Mat(480, 640, sizeof(uchar)); // Matriz de cinza com a média dos tons RGB
    
  int width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;

  while(1){
    cap >> image;

    split(image, canais); // Separa as cores em 3 matrizes

    //canais[0] = Mat::zeros(canais[0].size(), CV_8UC1); // retira os tons de azul
    canais[1] = Mat::zeros(canais[1].size(), CV_8UC1); // retira os tons de verde
    canais[2] = Mat::zeros(canais[2].size(), CV_8UC1); // retira os tons de vermelho


    merge(canais,3, descolor);

    imshow("freaking ghost", descolor);

    if(waitKey(30) >= 0) break;
  }
  
  return 0;
}
