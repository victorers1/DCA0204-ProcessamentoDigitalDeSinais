#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main(){
  Mat image;
  VideoCapture cap; 
  cap.open(0);
  Mat canais[3];
  int media=0;
  Mat descolor = Mat(480, 640, sizeof(uchar)); // Matriz de cinza com a média dos tons RGB
    
  int width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;

  while(1){
    cap >> image;
    split(image, canais); // Separa as cores em 3 matrizes

    for(int y=0; y<descolor.rows; y++){
        for(int x=0; x<descolor.cols; x++){
            media = (canais[0].at<uchar>(y,x) + canais[1].at<uchar>(y,x) + canais[2].at<uchar>(y,x))/3; // Faz a média dos tons RGB
            descolor.at<uchar>(y,x) = media; // E guarda na nova imagem
        }
    }

    imshow("freaking ghost", descolor);

    if(waitKey(30) >= 0) break;
  }
  
  return 0;
}
