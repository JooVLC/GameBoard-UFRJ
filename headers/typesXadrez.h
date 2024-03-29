#ifndef XADREZ_TYPES
    #define XADREZ_TYPES 1

    #ifndef INCLUDE_STDBOOL
        #define INCLUDE_STDBOOL 1
        #include <stdbool.h>
    #endif

    #ifndef INCLUDE_STDLIB
        #define INCLUDE_STDLIB 1
        #include <stdlib.h>
    #endif

    #define QTD_CASAS_POR_LINHA 8
    #define QTD_CASAS_POR_COLUNA 8
    #define QTD_CASAS 64
    #define NOME_LEN 51
    #define QTD_JOGADORES 2

    #define MOVIMENTOS_POSSIVEIS_PEAO 3
    #define MOVIMENTOS_POSSIVEIS_CAVALO 8
    #define MOVIMENTOS_POSSIVEIS_TORRE 14
    #define MOVIMENTOS_POSSIVEIS_BISPO 13
    #define MOVIMENTOS_POSSIVEIS_RAINHA 27
    #define MOVIMENTOS_POSSIVEIS_REI 8

    typedef int Coordenada;

    typedef struct {
        Coordenada linha, coluna;
    } Posicao;

    typedef enum { 
        BRANCO = 0, 
        PRETO = 1,
        EMPATE = 2, 
    } CorPeca;

    typedef enum { 
        PEAO = 0, 
        TORRE, 
        CAVALO, 
        BISPO, 
        RAINHA, 
        REI 
    } TipoPeca;

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
        CorPeca cor;
        Posicao localizacao;
    } CasaTabuleiro;

    typedef CasaTabuleiro Tabuleiro[QTD_CASAS_POR_LINHA][QTD_CASAS_POR_COLUNA];

    typedef unsigned int Turno;

    typedef unsigned int QtdMovimentosPossiveis;

    typedef struct {
        Tabuleiro tabuleiro;
        Jogador jogadores[QTD_JOGADORES];
        CorPeca corJogando;
        Turno turno;
        bool jogando;
    } Jogo;   
#endif
