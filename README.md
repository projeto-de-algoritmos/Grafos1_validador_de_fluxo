# Validador de Fluxo

**Número da Lista**: 16<br>
**Conteúdo da Disciplina**: Grafos 1<br>

## Alunos
|Matrícula | Aluno |
| -- | -- |
| 13/0126721  | Matheus Roberto |
| 19/0127708  |  Daniel Oda |

## Sobre 
Esse projeto tem como objetivo identificar ciclos nos fluxogramas de cursos. Caso tenha um ciclo, o fluxograma estará errado. Esses ciclos são identificados a partir de um teste de ordenação topológica, buscas (em largura e profundidade) e pela teoria de componentes fortemente conectados.

## Screenshots
![](https://i.ibb.co/wgVCfYr/Whats-App-Image-2021-08-09-at-22-21-14-2.png)
![](https://i.ibb.co/8cQ6BkN/Whats-App-Image-2021-08-09-at-22-21-14.png)
![](https://i.ibb.co/cKW2Ltv/Whats-App-Image-2021-08-09-at-22-21-14-1.png)

## Instalação 
**Linguagem**: C++<br>

Para compilar: **g++ trabalho_1.cpp -std=c++11**<br>
<br>
Para rodar testes: **./a.out < nome_do_teste.txt**<br>
<br>
Testes: **fluxograma_software.txt**<br>
        **fluxograma_software_errado.txt**<br>
        **fluxograma_software_errado_2.txt**<br>
## Uso 
Após compilar o código, rode os comandos para executar os testes. O comando selecionará um arquivo .txt informando os número de nós, matérias no fluxo e relações de pré-requisitos.





