#include <iostream>
#include <opencv2/opencv.hpp>
#include <stack>
#include <string>

using namespace std;
using namespace cv;

/**
 * floodfill recebe uma imagem, um ponto e uma escala de cinza.
 * A função pinta a imagem com a cor dada a partir do ponto dado.
 * A extensão da pintura é definida pela região de mesma cor em 
 * que o ponto se encontra antes da execução do algoritmo.
 */
Rect floodfill(Mat im, Point p, int cor){
    stack<Point> pilha;
    pilha.push(p); // Inicia pilha de pontos com o passado no 3º parâmetro
    int corAnt = im.at<uchar>(p);  // Salva cor anterior
    Point temp; // Ponto temporário. Representa sempre o que está sendo processado atualmente.

    int esquer=im.cols, direit=0, cima=im.rows, baixo=0; // Coordenadas dos pontos acima
    
    while(!pilha.empty()){ // Atualiza pilha 
        temp = pilha.top(); // Recupera  topo
        pilha.pop(); // Remove topo

        esquer=im.cols; direit=0; cima=im.rows; baixo=0;
        temp.x < cima   ? cima  =temp.x : true;
        temp.x > baixo  ? baixo =temp.x : true;
        temp.y < esquer ? esquer=temp.y : true;
        temp.y > direit ? direit=temp.y : true;
        
        if (im.at<uchar>(temp)==corAnt){
            im.at<uchar>(temp) = cor; // Recebe nova cor
            if(temp.x >= 1)        pilha.push(Point(temp.x-1, temp.y)); // Vizinho de cima
            if(temp.x+1 < im.rows) pilha.push(Point(temp.x+1, temp.y)); // Vizinho de baixo
            if(temp.y >= 1)        pilha.push(Point(temp.x,   temp.y-1)); // Vizinho da esquerda
            if(temp.y+1 < im.cols) pilha.push(Point(temp.x,   temp.y+1)); // Vizinho da direita
        }
    }
    cout<<"Superior esquerdo: x="<< cima <<", y= "<< esquer <<endl;
    cout<<"Inferior direiro: x="<< baixo <<", y= "<< direit <<endl;

    Point supesq(cima, esquer), infdir(baixo, direit); // Pontos superior esquerdo e inferior direito
    return Rect(supesq, infdir);
}

int main(){
    int qtdLetras=0;
    Rect regiao;
    string nomeJanela = "letra ";
    vector<String> end;
    glob("/home/victor/Área de Trabalho/OpenCV_Codes/img/letras.jpg", end, false);
    Mat imagem = imread(end[0], CV_LOAD_IMAGE_GRAYSCALE);
    resize(imagem, imagem, Size(243,307));
    
    threshold(imagem, imagem, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
    imshow("imagem", imagem); 
    waitKey();
    for(int y=0; y<imagem.cols; y++){
        for(int x=0; x<imagem.rows; x++){
            if(imagem.at<uchar>(x,y)!=255){ 
                cout<<"Achei pixel ("<<x<<", "<<y<<") preto\n";
                qtdLetras++;
                regiao = floodfill(imagem, Point(x,y), qtdLetras*5);
                Mat letra(imagem, regiao);
                //nomeJanela = "letra: "; nomeJanela += (char) qtdLetras; nomeJanela += "\0";
                imshow("letra", letra);
                waitKey();
            }
        }
    }
    waitKey();
    return 0;
}