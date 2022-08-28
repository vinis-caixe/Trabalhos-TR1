# Camada Física

Implementação da Camada Física com 3 protocolos de Codificação:

* Binário
* Manchester
* Bipolar

## Arquivos

- [CamadaFisica.cpp](CamadaFisica.cpp): Funções relativas a Codificação, Decodificação e Transmissão de dados.

- [Simulador.cpp](Simulador.cpp): Interface com o usuário.

## Compilação e Execução

Para compilar e executar os arquivos:
  ```Batchfile
  g++ -std=c++17 Simulador.cpp CamadaFisica.hpp CamadaFisica.cpp
  ./a.out
  ```
  
Para executar o simulador de arquivos binários:
  ```Batchfile
  g++ -std=c++17 SimuladorFiles.cpp CamadaFisica.hpp CamadaFisica.cpp
  ./a.out file.png
  ```
 OBS: O módulo SimuladorFiles.cpp não vai compilar caso você não faça a variável `mensagem_original` ser retornada pelas funções da camada física, essa alteração é necessaria para acessar o dado final.
