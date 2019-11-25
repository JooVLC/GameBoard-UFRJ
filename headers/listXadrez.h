#ifndef LISTA_XADREZ
    #define LISTA_XADREZ 1
    #include "./genericList.h"
    #include "./typesXadrez.h"
    
    typedef Lista ListaCasaTabuleiro;

    ListaCasaTabuleiro* criarListaCasasTabuleiro();

    CasaTabuleiro* ListaParaArrayDeCasaTabuleiro(ListaCasaTabuleiro lista);

    void adicionarNovoMovimento(ListaCasaTabuleiro *lista, CasaTabuleiro peca);
#endif