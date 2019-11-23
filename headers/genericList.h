#ifndef LISTA_GENERICA
    #define LISTA_GENERICA 1

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

    No* retornarElementoPorIndice(Lista lista, Indice indice);

    No* retornarElementoPorValor(Lista lista, void *valor);

    No* adicionarElementoAoFinalDaLista(Lista lista, void* novoValor);

    No* adicionarElementoAoInicioDaLista(Lista lista, void* novoValor);

    No* adicionarElementoPorIndice(Lista lista, void* novoValor, Indice indice);

    No* adicionarElementoPorValor(Lista lista, void* novoValor, void* valor);

    void removerElementoDaListaPorValor(Lista lista, void* valor);

    void removerElementoDaListaPorIndice(Lista lista, Indice indice);

    void apagarNo(No **no);

    void apagarLista(Lista lista);

    size_t listalen(Lista lista);
#endif