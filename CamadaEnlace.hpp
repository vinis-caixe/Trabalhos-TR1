#include <iostream>
#include <vector>
#include <bitset>
#include <string>

void CamadaEnlaceDadosTransmissora(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::vector<int> quadro);

void CamadaEnlaceDadosReceptora(std::vector<int> quadro);

std::vector<int> CamadaDeEnlaceReceptoraEnquadramento(std::vector<int> quadro);

std::vector<int> CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro);

std::vector<int> CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes(std::vector<int> quadro);