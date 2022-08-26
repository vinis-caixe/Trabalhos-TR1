#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include "CamadaFisica.hpp"

using namespace std;

void CamadaDeAplicacaoTransmissora(string mensagem){
    vector<int> quadro; // trabalhar com bits!
    string mensagemBits;

    for(size_t i = 0; i < mensagem.size(); i++){
        mensagemBits = mensagemBits + bitset<8>(mensagem.c_str()[i]).to_string();
    }

    for(int i = 0; i < mensagemBits.size(); i++){
        if(mensagemBits[i] == '1'){
            quadro.push_back(1);
        }
        else{
            quadro.push_back(0);
        }
    }

    CamadaFisicaTransmissora(quadro);
}

void AplicacaoTransmissora(){
    string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;

    CamadaDeAplicacaoTransmissora(mensagem);
}

int main(){
    AplicacaoTransmissora();

    return 0;
}
