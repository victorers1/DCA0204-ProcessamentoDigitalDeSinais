#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(){
	
	//Carregando uma imagem localizada numa outra pasta qualquer
	vector<String> fn;
	glob("/home/victor/Área de Trabalho/OpenCV_Codes/img/aula1.jpg", fn, false); // primeiro argumento é o endereço da imagem

	Mat imagem = imread(fn[0], CV_LOAD_IMAGE_UNCHANGED);
	Mat cinza = imread(fn[0], CV_LOAD_IMAGE_GRAYSCALE);
	imshow("cores",imagem);
	imshow("cinza",cinza);

	imwrite("cinza.jpg", cinza);
	waitKey();

	return 0;
}
