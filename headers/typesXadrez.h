#ifndef XADREZ_TYPES
    #define XADREZ_TYPES 1

    #ifndef __bool_true_false_are_defined
        #include <stdbool.h>
    #endif

    #ifndef NULL
        #include <stdlib.h>
    #endif

    #define QTD_CASAS_POR_LINHA 8
    #define QTD_CASAS_POR_COLUNA 8
    #define QTD_CASAS 64
    #define NOME_LEN 51
    #define QTD_JOGADORES 2

    typedef struct {
        unsigned int x, y;
    } Posicao;

    typedef enum { BRANCO = 0, PRETO = 1 } CorPeca;

    typedef enum { PEAO = 0, TORRE, CAVALO, BISPO, RAINHA, REI } TipoPeca;

    typedef struct {
        Posicao posicao;
        CorPeca cor;
        TipoPeca tipo;
        bool emXeque;
        bool evitandoXequeMate;
    } Peca;

    typedef char Nome[NOME_LEN];

    typedef struct {
        Nome nome;
        CorPeca corDasPecas;
    } Jogador;

    typedef struct {
        Peca *peca;
    } CasaTabuleiro;

    typedef CasaTabuleiro Tabuleiro[QTD_CASAS_POR_LINHA][QTD_CASAS_POR_COLUNA];

    typedef struct {
        Tabuleiro tabuleiro;
        CorPeca corAtual;
        Jogador jogadores[QTD_JOGADORES];
    } Jogo;
#endif