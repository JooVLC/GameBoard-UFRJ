#ifndef LISTA_GENERICA
    #define LISTA_GENERICA 1
    #include "./includeLibrarys.h"
    
    typedef struct Data {
        struct Data* proximo;
        void* data;
    } Data;

    typedef Data *InicioLista;
    typedef Data *NoLista;
    typedef size_t ListaLen;
    typedef size_t TamanhoData;
    typedef size_t Indice;

    typedef struct Lista {
        InicioLista inicio;
        ListaLen len;
        TamanhoData tamData;
    } Lista;

    void criarLista(Lista **listaPtr, TamanhoData tamanhoData);

    void adicionarPrimeiroItemNaLista(Lista *lista, void* novoItem);

    void adicionarItemAoInicioDaLista(Lista *lista, void* novoItem);

    void adicionarItemAoFinalDaLista(Lista *lista, void* novoItem);

    NoLista criarNovoNo(void *data/*, TamanhoData tamData*/);

    NoLista retornarElementoDaLista(Lista *lista, Indice indice);

    void apagarLista(Lista **listaPtr);
#endif
