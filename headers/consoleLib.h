#ifndef CONSOLE_LIB
    #define CONSOLE_LIB 1

    #include "./typesXadrez.h"
    #include "./listXadrez.h"

    void iniciarJogoConsole(Nome jogadorBranco, Nome jogadorPreto);

    void printarTabuleiro(Tabuleiro tabuleiro);

    void printColunas(void);

    void printLinhaIndice(int indice, Tabuleiro tabuleiro);

    Posicao pedirPecaMovidaJogador(void);

    CasaTabuleiro* pedirMovimentoJogador(CasaTabuleiro pecaMovida, ListaCasaTabuleiro movimentos);

    char letraDoTipoDaPeca(TipoPeca tipoPeca);
#endif