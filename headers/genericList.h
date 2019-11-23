#ifndef LISTA_XADREZ
    #define LISTA_XADREZ 1

    #ifndef INCLUDE_STDLIB
        #define INCLUDE_STDLIB 1
        #include <stdlib.h>
    #endif

    typedef struct No {
        void* valor;
        struct No* proximo;
    } No;

    typedef No* InicioLista;

    typedef struct {
        InicioLista *inicio;
        size_t tamanhoElementos;
    } Lista;

    typedef unsigned int Indice;

    Lista criarListaDeTipoGenerico(size_t tamanhoElemento);

    No retornarElementoPorIndice(Indice indice);

    No retornarElementoPorValor(void *valor);

    void adicionarElementoAoFinalDaLista(Lista lista, void* novoValor);

    void adicionarElementoAoInicioDaLista(Lista lista, void* novoValor);

    void removerElementoDaListaPorValor(Lista lista, void* valor);

    void removerElementoDaListaPorIndice(Lista lista, Indice indice);

    void apagarLista(Lista lista);
#endif