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

    void printarTabuleiro(Tabuleiro tabuleiro, CasaTabuleiro casaMovida, ListaCasaTabuleiro* casasPossiveis);

    void printColunas(void);

    void printBordas(bool bordaSuperior);

    void printLinhaIndice(int indice, Tabuleiro tabuleiro, CasaTabuleiro casaMovida, ListaCasaTabuleiro* casasPossiveis);

    Posicao pedirPecaMovidaJogador(void);

    CasaTabuleiro* pedirMovimentoJogador(CasaTabuleiro pecaMovida, ListaCasaTabuleiro *movimentos);

    char letraDoTipoDaPeca(TipoPeca tipoPeca);

    void printc(const char *const str, const char *const color, bool corDeBackground);

    void getPosicaoDoUsuario(int *linha, char *coluna);

    void getNumeroDoUsuario(int *num, int maxNum);

    void limparBuffer(char str[], size_t tamanhoDesejado);
#endif
