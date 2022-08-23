#include "CamadaFisica.hpp"

void CamadaFisicaTransmissora(std::vector<bool> quadro){
    int tipoDeCodificacao = 0; //alterar de acordo com o teste 
    std::vector<bool> fluxoBrutoDeBits; //atenção: trabalhar com bits!

    switch(tipoDeCodificacao){
        case 0:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case 2:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
            break;
    }

    MeioDeComunicacao(fluxoBrutoDeBits);
}

// FUNCOES DE CODIFICACAO
std::vector<bool> CamadaFisicaTransmissoraCodificacaoBinaria(std::vector<bool> quadro){
    std::vector<bool> fluxoBrutoDeBits;



    return fluxoBrutoDeBits;
}

std::vector<bool> CamadaFisicaTransmissoraCodificacaoManchester(std::vector<bool> quadro){
    std::vector<bool> fluxoBrutoDeBits;

    

    return fluxoBrutoDeBits;
}

std::vector<bool> CamadaFisicaTransmissoraCodificacaoBipolar(std::vector<bool> quadro){
    std::vector<bool> fluxoBrutoDeBits;

    

    return fluxoBrutoDeBits;
}

void MeioDeComunicacao(std::vector<bool> fluxoBrutoDeBits){
    //OBS IMPORTANTE: trabalhar com BITS e nao com BYTES
    std::vector<bool>  fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;
    int i;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    for(i = 0; i < fluxoBrutoDeBitsPontoA.size(); i++){
        fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]);
    }

    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}

void CamadaFisicaReceptora(std::vector<bool> quadro){
    int tipoDeDecodificacao = 0; //alterar de acordo com o teste
    std::vector<bool> fluxoBrutoDeBits;

    switch(tipoDeDecodificacao){
        case 0:
            fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBinaria(quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchester(quadro);
            break;
        case 2:
            fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBipolar(quadro);
            break;
    }

    CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}

// FUNCOES DE DECODIFICACAO
std::vector<bool> CamadaFisicaReceptoraDecodificacaoBinaria(std::vector<bool> quadro){
    std::vector<bool> fluxoBrutoDeBits;

    

    return fluxoBrutoDeBits;
}

std::vector<bool> CamadaFisicaReceptoraDecodificacaoManchester(std::vector<bool> quadro){
    std::vector<bool> fluxoBrutoDeBits;

    

    return fluxoBrutoDeBits;
}

std::vector<bool> CamadaFisicaReceptoraDecodificacaoBipolar(std::vector<bool> quadro){
    std::vector<bool> fluxoBrutoDeBits;

    

    return fluxoBrutoDeBits;
}

void CamadaDeAplicacaoReceptora(std::vector<bool> quadro){
    std::string mensagem;
    int i;

    for(i = 0; i < quadro.size(); i++){
        quadro[i] ? mensagem + '1' : mensagem + '0';
    }

    AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(std::string mensagem){
    std::cout << "A mensagem recebida foi: " << mensagem << std::endl;
}
