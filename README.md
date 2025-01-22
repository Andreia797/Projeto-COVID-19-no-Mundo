# Projeto: COVID-19 no Mundo  

## Descrição  
Este programa em C permite aos usuários acompanhar a evolução da pandemia COVID-19 no mundo. Utilizando listas ligadas, o programa gerencia informações sobre países, incluindo números de casos, recuperados, óbitos e casos ativos.  

## Funcionalidades  
- Estrutura chamada `covid19` com os membros:  
  - `país`  
  - `casos`  
  - `recuperados`  
  - `óbitos`  
  - `casos_ativos`  
- Funções disponíveis:  
  - CriarLista  
  - InserirNoInicio  
  - InserirNoMeio  
  - InserirNoFinal  
  - ImprimirLista  
  - PesquisarElemento (através do nome do país)  
  - Calcular total de casos  
  - Calcular total de mortes  
  - Calcular total de recuperados  
  - Ordenar países em ordem ascendente (mais casos de COVID-19)  
  - Calcular casos ativos de cada país e enviar para o arquivo `CasosAtivos.txt`  
  - Enviar todos os nós para o arquivo `elementos.txt`  
  - RemoverNoInicio  
  - RemoverNoFinal  
  - RemoverQualquerElemento  

## Tela Inicial 
![1](https://github.com/user-attachments/assets/a722e60c-658e-45cd-8cd7-20faddb4d733)



## Requisitos  
- Um compilador C (como gcc)  
- Sistema operacional compatível (Windows, Linux ou macOS)  

## Como Compilar  
Para compilar o programa, utilize um compilador C, como `gcc`. Execute o seguinte comando no terminal:  

```bash  
gcc main.c -o covid19
