#ifndef XADREZ_FUNCOES

#define XADREZ_FUNCOES 1

#include "typesXadrez.h"

//Cria o jogo e retorna ele a partir dos nomes pegos do CMD
Jogo inicializarJogo(Nome nomeJogadorBranco, Nome nomeJogadorPreto);

//Cria o tabuleiro e coloca as pecas nele nas posicoes padroes do xadrez
void inicializarTabuleiro(Tabuleiro novoTabuleiro);

//Cria 8 peoes da cor desejada e retorna um ponteiro para o primeiro peao
Peca* criarPeoes(CorPeca corCriada);

//Cria as 8 pecas especiais (nao peoes) (padrao criarPeoes)
Peca* criarPecasEspeciais(CorPeca corCriada);

//Cria um novo jogador a partir do seu nome e cor
Jogador criarJogador(Nome nomeJogador, CorPeca corJogador);

//Testa se houve xequemate, e caso houver, corPeca recebe a cor de quem
//esta recebendo o xeque, caso não, retorna NULL
bool xequeMate(Tabuleiro tabuleiro, CorPeca *corRecebendoCheque);

//Verifica se uma peca esta em cheque em determinado tabuleiro
bool pecaEstaEmXeque(CasaTabuleiro pecaTestada, Tabuleiro tabuleiro);

//Verifica se a peca esta impedindo um xequemate
bool pecaImpedindoXequeMate(CasaTabuleiro pecaTestada, Tabuleiro tabuleiro);

#endif