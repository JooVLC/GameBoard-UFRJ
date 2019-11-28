#ifndef CONSOLE_LIB
    #define CONSOLE_LIB 1

    #include "./typesXadrez.h"
    #include "./listXadrez.h"

    void iniciarJogoConsole(Nome jogadorBranco, Nome jogadorPreto);

    void printarTabuleiro(Tabuleiro tabuleiro, CasaTabuleiro casaMovida, CasaTabuleiro* casasPossiveis);

    void printColunas(void);

    void printBordas(bool bordaSuperior);

    void printLinhaIndice(int indice, Tabuleiro tabuleiro, CasaTabuleiro casaMovida, CasaTabuleiro* casasPossiveis);

    Posicao pedirPecaMovidaJogador(void);

    CasaTabuleiro* pedirMovimentoJogador(CasaTabuleiro pecaMovida, ListaCasaTabuleiro *movimentos);

    char letraDoTipoDaPeca(TipoPeca tipoPeca);

    void printc(const char *const str, const char *const color, bool corDeBackground);
#endif
