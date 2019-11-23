#include "../headers/typesXadrez.h"
#include "../headers/functionsXadrez.h"

CasaTabuleiro* movimentosPossiveisPeao(CasaTabuleiro peca, Tabuleiro tabuleiro, Turno turnoAtual)
{
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    CasaTabuleiro *movimentosPossiveis = 

    if(turnoAtual == 1 && peca.peca->cor == BRANCO)
    {

    }
    else if (turnoAtual == 2 && peca.peca->cor == PRETO)
    {
    }
    else
    {
        tabuleiro[peca.peca->posicao.linha][]
    }
}