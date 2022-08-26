#include <iostream>
#include <vector>
#include <string>

void CamadaFisicaTransmissora(std::vector<int> quadro);

std::vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(std::vector<int> quadro);

std::vector<int> CamadaFisicaTransmissoraCodificacaoManchester(std::vector<int> quadro);

std::vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(std::vector<int> quadro);

void MeioDeComunicacao(std::vector<int> fluxoBrutoDeBits);

void CamadaFisicaReceptora(std::vector<int> quadro);

std::vector<int> CamadaFisicaReceptoraDecodificacaoBinaria(std::vector<int> quadro);

std::vector<int> CamadaFisicaReceptoraDecodificacaoManchester(std::vector<int> quadro);

std::vector<int> CamadaFisicaReceptoraDecodificacaoBipolar(std::vector<int> quadro);

void CamadaDeAplicacaoReceptora(std::vector<int> quadro);

void AplicacaoReceptora(std::string mensagem);