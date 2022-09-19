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
    int tipoDeControleDeErro = 1;
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

// Realiza controle de erro da transmissão utilizando método de Bit de Paridade Par
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<int> quadro) {
    bool bitParidade = 0;
    for (int i = 0; i < quadro.size(); i++) {
        bitParidade ^= quadro[i];
    }
    quadro.push_back(bitParidade);

    return quadro;
}

// Realiza controle de erro da transmissão utilizando o Código de Redundância Cíclica
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(std::vector<int> quadro) {
    // Polinomio CRC-32(IEEE 802)
    std::vector<int> crc32 = {1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1,1};
    int crc_size = crc32.size();
    std::vector<int> remainder;
    // Bits extras para comportar o resto da divisão.
    for (int i = 0; i < crc_size; i++) {
        quadro.push_back(0);
        remainder.push_back(quadro[i]);
    }

    // Função de XOR entre dois vetores.
    auto vector_xor = [](std::vector<int> &a, std::vector<int> &b) {
        std::vector<int> c(a.size());
        for (int i = 0; i < a.size(); i++) {
            c[i] = a[i] ^ b[i];
        }
        return c;
    };

    // Realiza a divisão do quadro pelo crc32.
    int quadro_size = quadro.size();
    for (int i = crc_size; i < quadro_size; i++) {
        if (remainder[0] != 0) {
            remainder = vector_xor(remainder, crc32);
        }
        assert(remainder[0] == 0);
        remainder.erase(remainder.begin());
        remainder.push_back(quadro[i]);
    }

    // Insere o resto da divisão no quadro.
    for (int i = quadro_size - crc_size, j = 0; i < quadro_size; i++, j++) {
        quadro[i] ^= remainder[j];
    }

    return quadro;
}

// Realiza controle de erro da transmissão utilizando o Código de Hamming
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(std::vector<int> quadro) {
    int bitsVerificacao = 2, bitsDados = 1, posicao = 1;

    while(quadro.size() >= bitsDados){
        bitsVerificacao++;
        bitsDados = (round(pow(2, bitsVerificacao)) - bitsVerificacao) - 1;
    }

    for(int i = 0; i < bitsVerificacao; i++){
        quadro.insert((quadro.begin() + posicao - 1), 0);
        posicao *= 2;
    }

    std::vector<bool> bitsParidade(bitsVerificacao, 0);

    for(int i = 0; i < quadro.size(); i++){
        std::bitset<8> byte(i+1);
        std::string byteMensagem = byte.to_string();
        std::reverse(byteMensagem.begin(), byteMensagem.end());

        for(int j = 0; j < byteMensagem.size(); j++){
            if(byteMensagem[j] == '1' && bitsVerificacao >= (j-1)){
                bitsParidade[j] = bitsParidade[j] ^ quadro[i];
            }
        }
    }

    posicao = 1;
    for(int i = 0; i < bitsParidade.size(); i++){
        quadro[posicao - 1] = bitsParidade[i];
        posicao *= 2;
    }

    return quadro;
}

void CamadaEnlaceDadosReceptora(std::vector<int> quadro){
    std::vector<int> quadroDesenquadrado, quadroControleDeErro;

    quadroControleDeErro = CamadaEnlaceReceptoraControleDeErro(quadro);

    quadroDesenquadrado = CamadaEnlaceReceptoraEnquadramento(quadroControleDeErro);

    CamadaDeAplicacaoReceptora(quadroDesenquadrado);
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
    int tipoDeControleDeErro = 1;
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
    bool bitParidade = 0;
    for (int i = 0; i < quadro.size(); i++) {
        bitParidade ^= quadro[i];
    }
    if (bitParidade) {
        std::cout << "Erro identificado utilizando método de Bit de Paridade!" << std::endl;
    }
    quadro.pop_back();
    return quadro;
}

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(std::vector<int> quadro) {
    std::vector<int> crc32 = {1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1,1};
    int crc_size = crc32.size();

    std::vector<int> remainder;
    for (int i = 0; i < crc_size; i++) {
        remainder.push_back(quadro[i]);
    }

    // Função de XOR entre dois vetores.
    auto vector_xor = [](std::vector<int> &a, std::vector<int> &b) {
        std::vector<int> c(a.size());
        for (int i = 0; i < a.size(); i++) {
            c[i] = a[i] ^ b[i];
        }
        return c;
    };

    // Realiza a divisão do quadro pelo crc32.
    int quadro_size = quadro.size();
    for (int i = crc_size; i < quadro_size; i++) {
        if (remainder[0] != 0) {
            remainder = vector_xor(remainder, crc32);
        }
        assert(remainder[0] == 0);
        remainder.erase(remainder.begin());
        remainder.push_back(quadro[i]);
    }

    // Verifica se o resto é igual a 0.
    bool equalToZero = true;
    for (int i = 0; i < crc_size; i++) {
        equalToZero &= (remainder[i] == 0);
    }

    if (!equalToZero) {
        std::cout << "Erro identificado utilizando método de Código de Redundância Cíclica!" << std::endl;
    }

    // Remove os bits extras contendo o resto da divisão.
    for (int i = 0; i < crc_size; i++) {
        quadro.pop_back();
    }
    return quadro;
}

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(std::vector<int> quadro) {
    int bitsVerificacao = 2, bitsDados = 3, posicao;

    while(quadro.size() >= bitsDados){
        bitsVerificacao++;
        bitsDados = round(pow(2, bitsVerificacao)) - 1;
    }

    std::vector<bool> bitsParidade(bitsVerificacao, 0);

    for(int i = 0; i < quadro.size(); i++){
        std::bitset<8> byte(i+1);
        std::string byteMensagem = byte.to_string();
        std::reverse(byteMensagem.begin(), byteMensagem.end());

        for(int j = 0; j < byteMensagem.size(); j++){
            if(byteMensagem[j] == '1' && bitsVerificacao >= (j-1)){
                bitsParidade[j] = bitsParidade[j] ^ quadro[i];
            }
        }
    }

    posicao = 0;
    if(std::find(bitsParidade.begin(), bitsParidade.end(), 1) != bitsParidade.end()){
        for(int i = 0; i < bitsParidade.size(); i++){
            if(bitsParidade[i] == 1){
                posicao += round(pow(2, i));
            }
        }
        std::cout << "Erro! Detectado troca de bit na posição " << posicao << ". Corrigindo erro...\n";
        if(quadro[posicao-1] == 1){
            quadro[posicao-1] = 0;
        }
        else{
            quadro[posicao-1] = 1;
        }
    }

    for(int i = 0; i < bitsVerificacao; i++){
        quadro.erase(quadro.begin() + (round(pow(2, i)) - (1+i)));
    }

    return quadro;
}
