#include <iostream>
#include <string>
#include <vector>
#include "CamadaFisica.hpp"

using namespace std;

void CamadaDeAplicacaoTransmissora(string mensagem){
    int i, mensagemDecimal = stoi(mensagem); // trabalhar com bits!
    vector<bool> quadro;

    for(i = 0; mensagemDecimal > 0; i++){
        quadro.push_back(mensagemDecimal % 2);
        mensagemDecimal = mensagemDecimal / 2;
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
