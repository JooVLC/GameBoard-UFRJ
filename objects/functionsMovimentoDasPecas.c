#include "../headers/typesXadrez.h"
#include "../headers/functionsXadrez.h"
#include "../headers/listXadrez.h"

CasaTabuleiro* movimentosPossiveisPeao(CasaTabuleiro peca, Tabuleiro tabuleiro, Turno turnoAtual) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    #pragma CASAS RELEVANTES AO PEAO
        CasaTabuleiro **casasRelevantes = casasRelevantesAoPeao(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
        CasaTabuleiro *casaAcimaDoPeaoLinha = casasRelevantes[0];
        CasaTabuleiro *casaAcimaDoPeaoLinhaDireita = casasRelevantes[1];
        CasaTabuleiro *casaAcimaDoPeaoLinhaEsquerda = casasRelevantes[2];
    #pragma endregion

    ListaCasaTabuleiro movimentosPossiveis = criarListaCasasTabuleiro();

    //Peao não pode pular pecas
    if( (turnoAtual == 1 && peca.peca->cor == BRANCO) || (turnoAtual == 2 && peca.peca->cor == PRETO) )
    {
        if(casaAcimaDoPeaoLinha != NULL && casaAcimaDoPeaoLinha->peca == NULL)
        {
            CasaTabuleiro movimentoPeaoDuasCasas = tabuleiro[pecaLinhaAtual+2][pecaColunaAtual];
            adicionarNovoMovimento(movimentosPossiveis, movimentoPeaoDuasCasas);
        }
    }

    if(casaAcimaDoPeaoLinhaDireita != NULL && casaAcimaDoPeaoLinhaDireita->peca != NULL && casaAcimaDoPeaoLinhaDireita->peca->cor != peca.peca->cor)
        adicionarNovoMovimento(movimentosPossiveis, *casaAcimaDoPeaoLinhaDireita);

    if(casaAcimaDoPeaoLinhaEsquerda != NULL && casaAcimaDoPeaoLinhaEsquerda->peca != NULL && casaAcimaDoPeaoLinhaEsquerda->peca->cor != peca.peca->cor)
        adicionarNovoMovimento(movimentosPossiveis, *casaAcimaDoPeaoLinhaEsquerda);

    if(casaAcimaDoPeaoLinha != NULL && casaAcimaDoPeaoLinha->peca == NULL)
        adicionarNovoMovimento(movimentosPossiveis, *casaAcimaDoPeaoLinha);
    
    free(casasRelevantes);
    return ListaParaArrayDeCasaTabuleiro(movimentosPossiveis);
}

CasaTabuleiro** casasRelevantesAoPeao(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    CasaTabuleiro *casaAcimaDoPeaoLinha = pecaLinhaAtual + 1 != QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual] : NULL;
    CasaTabuleiro *casaAcimaDoPeaoLinhaDireita = pecaColunaAtual + 1 != QTD_CASAS_POR_LINHA && pecaLinhaAtual + 1 != QTD_CASAS_POR_COLUNA? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual+1] : NULL;
    CasaTabuleiro *casaAcimaDoPeaoLinhaEsquerda = pecaColunaAtual != 0 && pecaLinhaAtual + 1 != QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual-1] : NULL;

    CasaTabuleiro** casasRelevantes = malloc(sizeof(CasaTabuleiro*) * 3);
    casasRelevantes[0] = casaAcimaDoPeaoLinha;
    casasRelevantes[1] = casaAcimaDoPeaoLinhaDireita;
    casasRelevantes[2] = casaAcimaDoPeaoLinhaEsquerda;

    return casasRelevantes;
}