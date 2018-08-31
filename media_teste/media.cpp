#include<iostream>

using namespace std;

int main(){
    int entra[3]={0,0,0};
    int temp=0, tempAnt=0;
    int media=0;
    int ind=0;
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