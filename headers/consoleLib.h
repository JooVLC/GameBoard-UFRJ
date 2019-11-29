#ifndef CONSOLE_LIB
    #define CONSOLE_LIB 1

    #include "./typesXadrez.h"
    #include "./listXadrez.h"

    
    #if defined(win32) || defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(__CYGWIN32__) || defined(__CYGWIN64__)
        #define CLEAR "cls"
    #else
        #define CLEAR "clear"
    #endif

    void iniciarJogoConsole(Nome jogadorBranco, Nome jogadorPreto);

    void printarTabuleiro(Tabuleiro tabuleiro);

    void printColunas(void);

    void printLinhaIndice(int indice, Tabuleiro tabuleiro);

    Posicao pedirPecaMovidaJogador(void);

    CasaTabuleiro* pedirMovimentoJogador(CasaTabuleiro pecaMovida, ListaCasaTabuleiro *movimentos);

    char letraDoTipoDaPeca(TipoPeca tipoPeca);
#endif
