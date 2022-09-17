#include <iostream>
#include <vector>
#include <bitset>
#include <string>

void CamadaEnlaceDadosTransmissora(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::vector<int> quadro);

std::vector<int> CamadaEnlaceTransmissoraControleDeErro(std::vector<int>);

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<int>);

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(std::vector<int>);

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(std::vector<int>);

void CamadaEnlaceDadosReceptora(std::vector<int> quadro);

std::vector<int> CamadaEnlaceReceptoraEnquadramento(std::vector<int> quadro);

std::vector<int> CamadaEnlaceReceptoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro);

std::vector<int> CamadaEnlaceReceptoraEnquadramentoInsercaoDeBytes(std::vector<int> quadro);

std::vector<int> CamadaEnlaceReceptoraControleDeErro(std::vector<int>);

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(std::vector<int>);

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(std::vector<int>);

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(std::vector<int>);

