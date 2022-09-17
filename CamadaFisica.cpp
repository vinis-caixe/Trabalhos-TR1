#include "CamadaFisica.hpp"
#include "CamadaEnlace.hpp"

// Realiza a codificação do quadro de bits, e encaminha os dados
// para o Meio de Comunicação.
//
// Tipo de codificação:
//      1 - Binária
//      2 - Manchester
//      3 - Bipolar
void CamadaFisicaTransmissora(std::vector<int> quadro){
    int tipoDeCodificacao = 2; // Tipo de Codificação
    std::vector<int> fluxoBrutoDeBits; // Trabalhando com bits, e não bytes

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

// Realiza a codificação Binária no quadro de bits, e retorna o resultado.
std::vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(std::vector<int> quadro){
    std::vector<int> fluxoBrutoDeBits;
    fluxoBrutoDeBits = quadro;

    return fluxoBrutoDeBits;
}

// Realiza a codificação Manchester no quadro de bits, e retorna o resultado.
std::vector<int> CamadaFisicaTransmissoraCodificacaoManchester(std::vector<int> quadro){
    std::vector<int> fluxoBrutoDeBits;

    for(int i = 0; i < quadro.size(); i++){
        fluxoBrutoDeBits.push_back(quadro[i] ^ 0);
        fluxoBrutoDeBits.push_back(quadro[i] ^ 1);
    }

    return fluxoBrutoDeBits;
}

// Realiza a codificação Bipolar no quadro de bits, e retorna o resultado.
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

// Simula o meio físico de comunicação, e encaminha os dados para
// a Camada Receptora.
void MeioDeComunicacao(std::vector<int> fluxoBrutoDeBits){
    std::vector<int>  fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;
    int i;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    for(i = 0; i < fluxoBrutoDeBitsPontoA.size(); i++){
        fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]);
    }

    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}

// Realiza a decodificação do quadro de bits recebido,
// e encaminha os dados para o Camada Receptora.
//
// Tipo de decodificação:
//      1 - Binária
//      2 - Manchester
//      3 - Bipolar
void CamadaFisicaReceptora(std::vector<int> quadro){
    int tipoDeDecodificacao = 2; // Tipo de Decodificação
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

    CamadaEnlaceDadosReceptora(fluxoBrutoDeBits);
}

// Realiza a decodificação Binária no quadro de bits, e retorna o resultado.
std::vector<int> CamadaFisicaReceptoraDecodificacaoBinaria(std::vector<int> quadro){
    std::vector<int> fluxoBrutoDeBits;

    fluxoBrutoDeBits = quadro;

    return fluxoBrutoDeBits;
}

// Realiza a decodificação Manchester no quadro de bits, e retorna o resultado.
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

// Realiza a decodificação Bipolar no quadro de bits, e retorna o resultado.
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

// Transforma o quadro de bits em uma string binária,
// e mostra os caracteres da mensagem original na tela.
void CamadaDeAplicacaoReceptora(std::vector<int> quadro){
    std::string mensagem;

    for(int i = 0; i < quadro.size(); i++){
        quadro[i] ? mensagem = mensagem + '1' : mensagem = mensagem + '0';
    }

    std::bitset<8> byte;
    std::string mensagem_original;

    for (int i = 0; i < quadro.size(); i += 8){
        for (int j = 0; j < 8; j++){
            byte[7 - j] = quadro[i + j];
        }
        mensagem_original += char(byte.to_ulong());
    }

    std::cout << "A mensagem recebida traduzida foi: " << mensagem_original << std::endl;

    AplicacaoReceptora(mensagem);
}

// Mostra a mensagem recebida em bits na tela.
void AplicacaoReceptora(std::string mensagem){
    std::cout << "A mensagem recebida foi: " << mensagem << std::endl;
}
