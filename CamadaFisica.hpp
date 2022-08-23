#include <iostream>
#include <vector>
#include <string>

void CamadaFisicaTransmissora(std::vector<bool> quadro);

std::vector<bool> CamadaFisicaTransmissoraCodificacaoBinaria(std::vector<bool> quadro);

std::vector<bool> CamadaFisicaTransmissoraCodificacaoManchester(std::vector<bool> quadro);

std::vector<bool> CamadaFisicaTransmissoraCodificacaoBipolar(std::vector<bool> quadro);

void MeioDeComunicacao(std::vector<bool> fluxoBrutoDeBits);

void CamadaFisicaReceptora(std::vector<bool> quadro);

std::vector<bool> CamadaFisicaReceptoraDecodificacaoBinaria(std::vector<bool> quadro);

std::vector<bool> CamadaFisicaReceptoraDecodificacaoManchester(std::vector<bool> quadro);

std::vector<bool> CamadaFisicaReceptoraDecodificacaoBipolar(std::vector<bool> quadro);

void CamadaDeAplicacaoReceptora(std::vector<bool> quadro);

void AplicacaoReceptora(std::string mensagem);