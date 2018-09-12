#include<iostream>
#include <vector>

using namespace std;

void vetor(){
    cout<<"Entrou na func. vetor.\n";
    vector<int> z;
    if(z.size()==0){
        cout<<"Tamanho de z: " <<z.size()<<endl;
        z.resize(10, 1);
        cout<<"Tamanho de z: "<< z.size()<<endl;
    }
    z[20] = 2; // Não interferiu no tamanho do vetor
    cout<<"Tamanho de z: "<<z.size()<<endl;
    for(int i=0; i<z.size(); i++){
        cout<<z[i]<<" ";
    }
}

int main(){
    int entra[3]={0,0,0};
    int temp=0, tempAnt=0;
    int media=0;
    int ind=0;

    vetor();

    for(int i=0; i<3; i++){
        cin>>entra[i];
        entra[i]/=3;
    }
    media = entra[0]+entra[1]+entra[2];
    cout<<"Média: "<<media<<endl;
    cout<<"entra: "<<entra[0]<<" "<<entra[1]<<" "<<entra[2]<<endl;
    while(1){
        cin>>temp;
        media -= entra[ind];
        entra[ind] = temp/3;
        media += entra[ind];
        ind = ++ind%3;
        cout<<"Média: "<<media<<endl;
        cout<<"entra: "<<entra[0]<<" "<<entra[1]<<" "<<entra[2]<<endl;
    }
    return 0;
}