#include "CamadaEnlace.hpp"
#include "CamadaFisica.hpp"

void CamadaEnlaceDadosTransmissora(std::vector<int> quadro){
    std::vector<int> quadroEnquadrado;

    quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

    CamadaFisicaTransmissora(quadroEnquadrado);

}

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<int> quadro){
    int tipoDeEnquadramento = 0;
    std::vector<int> quadroEnquadrado;

    switch(tipoDeEnquadramento){
        case 0:
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1:
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
            break;
    }

    return quadroEnquadrado;
}

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro){
    int quantidade;

    quantidade = quadro.size() / 8;

    std::bitset<8> byte(quantidade);

    std::string byteMensagem = byte.to_string();

    for(int i = (byteMensagem.size()-1); i >= 0; i--){
        if(byteMensagem[i] == '1'){
            quadro.insert(quadro.begin(), 1);
        }
        else{
            quadro.insert(quadro.begin(), 0);
        }
    }

    return quadro;
}

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::vector<int> quadro){
    return quadro;
}

void CamadaEnlaceDadosReceptora(std::vector<int> quadro){
    std::vector<int> quadroDesenquadrado;

    quadroDesenquadrado = CamadaDeEnlaceReceptoraEnquadramento(quadro);

    CamadaDeAplicacaoReceptora(quadroDesenquadrado);
}
std::vector<int> CamadaDeEnlaceReceptoraEnquadramento(std::vector<int> quadro){
    int tipoDeEnquadramento = 0;
    std::vector<int> quadroDesenquadrado;
    
    switch(tipoDeEnquadramento){
        case 0:
            quadroDesenquadrado = CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1:
            quadroDesenquadrado = CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes(quadro);
            break;
    }

    return quadroDesenquadrado;
}

std::vector<int> CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro){
    std::bitset<8> byte;
    int tamanho;
    int j = 7;

    for(int i = 0; i < 8; i++){
        byte[i] = quadro[j];
        j--;
    }

    tamanho = (int)(byte.to_ulong());
    
    if(((quadro.size() / 8) - 1) != tamanho){
        std::cout << "Quadro recebido é diferente do enviado!\n";
        exit(1);
    }

    quadro.erase(quadro.begin(), quadro.begin() + 8);

    return quadro;
}

std::vector<int> CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes(std::vector<int> quadro){
    return quadro;
}