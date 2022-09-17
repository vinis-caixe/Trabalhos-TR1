#include "CamadaEnlace.hpp"
#include "CamadaFisica.hpp"

void CamadaEnlaceDadosTransmissora(std::vector<int> quadro){
    std::vector<int> quadroEnquadrado, quadroControleDeErro;

    quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

    quadroControleDeErro = CamadaEnlaceTransmissoraControleDeErro(quadroEnquadrado);

    CamadaFisicaTransmissora(quadroControleDeErro);

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

std::vector<int> CamadaEnlaceTransmissoraControleDeErro(std::vector<int> quadro) {
    int tipoDeControleDeErro = 0;
    std::vector<int> quadroControleErro;

    switch (tipoDeControleDeErro) {
        case 0: // bit de paridade par
            quadroControleErro = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
            break;
        case 1: // CRC
            quadroControleErro = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
            break;
        case 2: // codigo de hamming
            quadroControleErro = CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(quadro);
            break;
    }

    return quadroControleErro;
}


std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<int> quadro) {
    // implementar
    return quadro;
}

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(std::vector<int> quadro) {
    // implementar // usar polinomio CRC-32(IEEE 802)
    return quadro;
}

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(std::vector<int> quadro) {
    // implementar
    return quadro;
}

void CamadaEnlaceDadosReceptora(std::vector<int> quadro){
    std::vector<int> quadroDesenquadrado, quadroControleDeErro;

    quadroDesenquadrado = CamadaEnlaceReceptoraEnquadramento(quadro);

    quadroControleDeErro = CamadaEnlaceReceptoraControleDeErro(quadroDesenquadrado);

    CamadaDeAplicacaoReceptora(quadroControleDeErro);
}

std::vector<int> CamadaEnlaceReceptoraEnquadramento(std::vector<int> quadro){
    int tipoDeEnquadramento = 0;
    std::vector<int> quadroDesenquadrado;
    
    switch(tipoDeEnquadramento){
        case 0:
            quadroDesenquadrado = CamadaEnlaceReceptoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1:
            quadroDesenquadrado = CamadaEnlaceReceptoraEnquadramentoInsercaoDeBytes(quadro);
            break;
    }

    return quadroDesenquadrado;
}

std::vector<int> CamadaEnlaceReceptoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro){
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

std::vector<int> CamadaEnlaceReceptoraEnquadramentoInsercaoDeBytes(std::vector<int> quadro){
    return quadro;
}

std::vector<int> CamadaEnlaceReceptoraControleDeErro(std::vector<int> quadro) {
    int tipoDeControleDeErro = 0;
    std::vector<int> quadroControleErro;

    switch (tipoDeControleDeErro) {
        case 0: // bit de paridade par
            quadroControleErro = CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
            break;
        case 1: // CRC
            quadroControleErro = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
            break;
        case 2: // codigo de hamming
            quadroControleErro = CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(quadro);
            break;
    }

    return quadroControleErro;
}

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(std::vector<int> quadro) {
    // impementar
    return quadro;
}

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(std::vector<int> quadro) {
    // impementar
    return quadro;
}

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(std::vector<int> quadro) {
    // impementar
    return quadro;
}
