#ifndef XADREZ_TYPES

//Verifica se a biblioteca stdbool ja foi incluida no projeto
#ifndef __bool_true_false_are_defined
    #include <stdbool.h>
#endif

#ifndef NULL
    #include <stdlib.h>
#endif

#define XADREZ_TYPES 1

#define QTD_CASAS_POR_LINHA 8
#define QTD_CASAS_POR_COLUNA 8
#define QTD_CASAS 64

typedef struct {
    unsigned int x, y;
} Posicao;

typedef enum { BRANCO = 0, PRETO = 1 } CorPeca;

typedef enum { PEAO = 0, TORRE, CAVALO, BISPO, RAINHA, REI } TipoPeca;

typedef struct {
    Posicao posicao;
    CorPeca cor;
    TipoPeca tipo;
    bool emCheque;
    bool evitandoChequeMate;
} Peca;

typedef struct {
    Peca *peca;
} CasaTabuleiro;

typedef CasaTabuleiro Tabuleiro[QTD_CASAS_POR_LINHA][QTD_CASAS_POR_COLUNA];

#endif