#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include "CamadaFisica.hpp"

// Converte uma mensagem no formato de string em um quadro de bits,
// e encaminha os dados para a Camada Transmissora.
std::string CamadaDeAplicacaoTransmissora(std::string mensagem){
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

    return CamadaFisicaTransmissora(quadro);
}

// Recebe um arquivo qualquer, encaminha seus dados binários
// para construir um quadro de bits na Camada Transmissora.
int main(int argc, char** argv){
    if (argc != 2) {
        std::cout << "Arquivo deve ser incluído como argumento de linha de comando." << std::endl;
        std::cout << "Exemplo: ./a.out file.png" << std::endl;
    } else {
        std::string file_name = argv[1];

        std::ifstream input_file(file_name, std::ios::binary);
        if (!input_file) {
            std::cout << "Arquivo não encontrado" << std::endl;
            return 1;
        }

        // Tamanho do arquivo
        input_file.seekg(0, std::ios::end);
        int file_size = input_file.tellg();
        input_file.seekg(0, std::ios::beg);

        // Lê o arquivo
        std::vector<char> data_input(file_size);
        input_file.read((char*) &data_input[0], file_size);
        input_file.close();

        // Envia os bytes para a camada transmissora
        std::string str_input(data_input.begin(), data_input.end());
        std::string str_output = CamadaDeAplicacaoTransmissora(str_input);
        // std::string str_output = str_input;
        std::vector<char> data_output;
        std::copy( str_output.begin(), str_output.end(), std::back_inserter(data_output));

        std::cout << "n = " << data_output.size() << std::endl;

        // Salva o arquivo gerado
        std::ofstream output_file("output_" + file_name, std::ios::binary);
        for (int i=0;i<file_size;i++) {
            output_file.write((char *) &data_output[i], sizeof(char));
        }
        output_file.close();
    }
    return 0;
}
