#include "../headers/typesXadrez.h"
#include "../headers/functionsXadrez.h"

#ifndef INCLUDE_STRING
    #define INCLUDE_STRING 1
    #include <string.h>
#endif

#ifndef INCLUDE_STDLIB
        #define INCLUDE_STDLIB 1
        #include <stdlib.h>
#endif

#include <stdio.h>

Jogador criarJogador(Nome nomeJogador, CorPeca corJogador) {
    Jogador jogador;
    jogador.corDasPecas = corJogador;
    strcpy(jogador.nome, nomeJogador);
    return jogador;
}

Peca* criarPeoes(CorPeca corCriada) {
    static const int QTD_PEOES = QTD_CASAS_POR_COLUNA;
    Peca* peoes = malloc(sizeof(Peca) * QTD_PEOES);

    for(int i = 0; i < QTD_PEOES; i++)
    {
        Peca novoPeao;
        novoPeao.emXeque = false;
        novoPeao.evitandoXequeMate = false;
        novoPeao.tipo = PEAO;
        novoPeao.cor = corCriada;
        
        peoes[i] = novoPeao;
    }

    return peoes;
}

Peca* criarPecasEspeciais(CorPeca corCriada) {
    static const int QTD_PECAS = QTD_CASAS_POR_COLUNA;
    Peca* pecas = malloc(QTD_PECAS * sizeof(Peca));

    for(int i = 0; i < QTD_PECAS; i++)
    {
        Peca novaPeca;
        novaPeca.cor = corCriada;
        novaPeca.emXeque = false;
        novaPeca.evitandoXequeMate = false;

        pecas[i] = novaPeca;
    }

    pecas[0].tipo = TORRE;
    pecas[1].tipo = CAVALO;
    pecas[2].tipo = BISPO;
    pecas[3].tipo = RAINHA;
    pecas[4].tipo = REI;
    pecas[5].tipo = BISPO;
    pecas[6].tipo = CAVALO;
    pecas[7].tipo = TORRE;

    return pecas;
}

Jogo inicializarJogo(Nome nomeJogadorBranco, Nome nomeJogadorPreto) {
    Jogo novoJogo;

    Jogador jogadorBranco = criarJogador(nomeJogadorBranco, BRANCO);
    Jogador jogadorPreto = criarJogador(nomeJogadorPreto, PRETO);

    //Jogador Branco vai primeiro:
    novoJogo.jogadores[0] = jogadorBranco;
    novoJogo.jogadores[1] = jogadorPreto;
    novoJogo.corJogando = BRANCO;
    novoJogo.turno = 1;
    novoJogo.jogando = true;
    puts("j");
    inicializarTabuleiro(novoJogo.tabuleiro);
    puts("2");
    inicializarPecas(novoJogo.tabuleiro);
    puts("3");

    return novoJogo;
}

void inicializarTabuleiro(Tabuleiro novoTabuleiro) {
    static const CorPeca COR_INICIAL = PRETO; //Cor da casa [0][0]

    CorPeca corDaCasa = COR_INICIAL;
    for(int i = 0; i < QTD_CASAS_POR_LINHA; i++)
    {
        for(int j = 0; j < QTD_CASAS_POR_COLUNA; j++)
        {
            CasaTabuleiro novaCasa;
            novaCasa.cor = corDaCasa;
            novaCasa.peca = NULL;
            novoTabuleiro[i][j] = novaCasa;

            corDaCasa = !corDaCasa;
        }

        //proxima linha a cor da casa é igual a cor da casa da ultima coluna da linha anterior
        corDaCasa = !corDaCasa;
    }
}

void inicializarPecas(Tabuleiro novoTabuleiro) {
    static const int QTD_LINHAS_COM_PECAS = 2;
    Peca *peoes, *outrasPecas;

    peoes = criarPeoes(BRANCO);
    puts("peoes");
    outrasPecas = criarPecasEspeciais(BRANCO);
    puts("outras pecas");
    for(int i = 0; i < QTD_LINHAS_COM_PECAS; i++)
    {
        for(int j = 0; j < QTD_CASAS_POR_COLUNA; j++)
        {
            if(i == 0)
                novoTabuleiro[i][j].peca = &outrasPecas[j];
            else
                novoTabuleiro[i][j].peca = &peoes[j];
        }    
    }
    puts("vai free");
    free(peoes);
    free(outrasPecas);
    puts("foi free");

    peoes = criarPeoes(PRETO);
    puts("peoes pretos");
    outrasPecas = criarPecasEspeciais(PRETO);
    puts("pecas pretas");
    for(int i = QTD_CASAS_POR_LINHA - 1; i >= QTD_CASAS_POR_LINHA - QTD_LINHAS_COM_PECAS; i--)
    {
        for(int j = 0; j < QTD_CASAS_POR_COLUNA; j++)
        {
            if(i == QTD_CASAS_POR_LINHA - 1)
                novoTabuleiro[i][j].peca = &outrasPecas[j];
            else
                novoTabuleiro[i][j].peca = &peoes[j];
        }    
    }
    puts("quase no fim");
    free(peoes);
    free(outrasPecas);
}

void proximoTurno(Jogo *jogo) {
    jogo->turno += 1;
    jogo->corJogando = !(jogo->corJogando);
}

Posicao converterPosicaoTelaParaCartesiano(Posicao posicaoTela) {
    Posicao posicaoPlano;

    posicaoPlano.linha = posicaoTela.linha + QTD_CASAS_POR_LINHA - (1 + 2 * posicaoTela.linha);
    posicaoPlano.coluna = posicaoTela.coluna;

    return posicaoPlano;
}

