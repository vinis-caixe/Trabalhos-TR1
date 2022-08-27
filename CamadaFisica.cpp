#include "CamadaFisica.hpp"

void CamadaFisicaTransmissora(std::vector<int> quadro){
    int tipoDeCodificacao = 1; //alterar de acordo com o teste 
    std::vector<int> fluxoBrutoDeBits; //atenção: trabalhar com bits!

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
std::vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(std::vector<int> quadro){
    std::vector<int> fluxoBrutoDeBits;
    fluxoBrutoDeBits = quadro;

    return fluxoBrutoDeBits;
}

std::vector<int> CamadaFisicaTransmissoraCodificacaoManchester(std::vector<int> quadro){
    std::vector<int> fluxoBrutoDeBits;

    for(int i = 0; i < quadro.size(); i++){
        fluxoBrutoDeBits.push_back(quadro[i] ^ 0);
        fluxoBrutoDeBits.push_back(quadro[i] ^ 1);
    }

    return fluxoBrutoDeBits;
}

std::vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(std::vector<int> quadro){
    std::vector<int> fluxoBrutoDeBits;
    int polaridade = 1;

    for (int i = 0; i < quadro.size(); i++){
        if (quadro[i] == 1){
            fluxoBrutoDeBits.push_back(quadro[i] * polaridade);
            polaridade = polaridade * (-1);
        }
        else if (quadro[i] == 0){
            fluxoBrutoDeBits.push_back((quadro[i]));
        }
    }
    

    return fluxoBrutoDeBits;
}

void MeioDeComunicacao(std::vector<int> fluxoBrutoDeBits){
    //OBS IMPORTANTE: trabalhar com BITS e nao com BYTES
    std::vector<int>  fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;
    int i;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    for(i = 0; i < fluxoBrutoDeBitsPontoA.size(); i++){
        fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]);
    }

    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}

void CamadaFisicaReceptora(std::vector<int> quadro){
    int tipoDeDecodificacao = 0; //alterar de acordo com o teste
    std::vector<int> fluxoBrutoDeBits;

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
std::vector<int> CamadaFisicaReceptoraDecodificacaoBinaria(std::vector<int> quadro){
    std::vector<int> fluxoBrutoDeBits;

    fluxoBrutoDeBits = quadro;

    return fluxoBrutoDeBits;
}

std::vector<int> CamadaFisicaReceptoraDecodificacaoManchester(std::vector<int> quadro){
    std::vector<int> fluxoBrutoDeBits;
    int bit1, bit2;

    for(int i = 0; i < quadro.size(); i = i + 2){
        bit1 = quadro[i];
        bit2 = quadro[i+1];

        if(bit1 == 0 && bit2 == 1){
            fluxoBrutoDeBits.push_back(0);
        }

        if(bit1 == 1 && bit2 == 0){
            fluxoBrutoDeBits.push_back(1);
        }
    }

    return fluxoBrutoDeBits;
}

std::vector<int> CamadaFisicaReceptoraDecodificacaoBipolar(std::vector<int> quadro){
    std::vector<int> fluxoBrutoDeBits;

    for (int i = 0; i < quadro.size(); i++){
        if (quadro[i] == 1 || quadro[i] == -1){
            fluxoBrutoDeBits.push_back(1);
        }
        else if (quadro[i] == 0){
            fluxoBrutoDeBits.push_back(0);
        }
    }

    return fluxoBrutoDeBits;
}

void CamadaDeAplicacaoReceptora(std::vector<int> quadro){
    std::string mensagem;

    for(int i = 0; i < quadro.size(); i++){
        quadro[i] ? mensagem = mensagem + '1' : mensagem = mensagem + '0';
    }

    //TODO transformar vetor de inteiros para string original

    AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(std::string mensagem){
    std::cout << "A mensagem recebida foi: " << mensagem << std::endl;
}
