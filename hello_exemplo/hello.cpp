#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  //Carregando uma imagem localizada numa outra pasta qualquer
	vector<String> fn;
	glob("/home/victor/Área de Trabalho/OpenCV_Codes/img/biel.png", fn, false); // primeiro argumento é o endereço da imagem


  Mat image;
  image = imread(fn[0],CV_LOAD_IMAGE_GRAYSCALE);
  imshow("image", image);
  waitKey();
  return 0;
}