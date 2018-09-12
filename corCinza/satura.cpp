#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main(){
  Mat image;
  VideoCapture cap; 
  cap.open(0);
  Mat canais[3];
  int maior=0;
  Mat saturado = Mat(640, 480, sizeof(uchar)); // Matriz de cinza com a média dos tons RGB
    
  int width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;
  int r=0,g=0,b=0;

  while(1){
    cap >> image;
    split(image, canais); // Separa as cores em 3 matrizes

    for(int y=0; y<saturado.cols; y++){
        for(int x=0; x<saturado.rows; x++){
            b = canais[0].at<uchar>(x,y);
            g = canais[1].at<uchar>(x,y);
            r = canais[2].at<uchar>(x,y);

            if(r>=b && r>=g){ // vermelho é o maior
                canais[0].at<uchar>(x,y) = 0;
                canais[1].at<uchar>(x,y) = 0;
            } else if (b>=r && b>=g){
                canais[2].at<uchar>(x,y) = 0;
                canais[1].at<uchar>(x,y) = 0;
            } else if (g>=r && g>=b){
                canais[0].at<uchar>(x,y) = 0;
                canais[2].at<uchar>(x,y) = 0;
            } else{
                canais[0].at<uchar>(x,y) = 0;
                canais[1].at<uchar>(x,y) = 0;
                canais[2].at<uchar>(x,y) = 0;
            }
            
        }
    }
    merge(canais, 3, saturado); // E guarda na nova imagem
    imshow("freaking ghost", saturado);

    if(waitKey(30) >= 0) break;
  }
  
  return 0;
}
