#ifndef LISTA_XADREZ
    #define LISTA_XADREZ 1
    #include "./genericList.h"
    #include "./typesXadrez.h"
    
    typedef Lista ListaCasaTabuleiro;

    void criarListaCasasTabuleiro(ListaCasaTabuleiro **lista);

    CasaTabuleiro* ListaParaArrayDeCasaTabuleiro(ListaCasaTabuleiro *lista);

    bool listaEstaVazia(ListaCasaTabuleiro *lista);

    void adicionarNovoMovimento(ListaCasaTabuleiro *lista, CasaTabuleiro peca);

    CasaTabuleiro* retornarMovimentoPeloIndice(ListaCasaTabuleiro *lista, Indice indice);

    size_t lenListaCasaTabuleiro(ListaCasaTabuleiro *lista);
#endif
