#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include "CamadaEnlace.hpp"

// Converte uma mensagem no formato de string em um quadro de bits,
// e encaminha os dados para a Camada Transmissora.
void CamadaDeAplicacaoTransmissora(std::string mensagem){
    std::vector<int> quadro;
    std::string mensagemBits;

    for(size_t i = 0; i < mensagem.size(); i++){
        mensagemBits = mensagemBits + std::bitset<8>(mensagem.c_str()[i]).to_string();
    }

    for(int i = 0; i < mensagemBits.size(); i++){
        if(mensagemBits[i] == '1'){
            quadro.push_back(1);
        }
        else{
            quadro.push_back(0);
        }
    }

    CamadaEnlaceDadosTransmissora(quadro);
}

// Recebe uma mensagem do usuário no formato de string
// e encaminha a mensagem para a Camada de Transmissão.
void AplicacaoTransmissora(){
    std::string mensagem;
    std::cout << "Digite uma mensagem:" << std::endl;
    std::getline(std::cin, mensagem);

    CamadaDeAplicacaoTransmissora(mensagem);
}

int main(){
    AplicacaoTransmissora();
    return 0;
}
