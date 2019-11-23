#include "../headers/genericList.h"

Lista criarListaDeTipoGenerico(size_t tamanhoElemento, void* primeiroValor) {
    Lista novaLista;

    InicioLista inicio = (InicioLista)malloc(tamanhoElemento);
    inicio->proximo = NULL;
    inicio->valor = primeiroValor;

    novaLista.tamanhoElementos = tamanhoElemento;
    novaLista.inicio = &inicio;

    return novaLista;
}

No* retornarElementoPorIndice(Lista lista, Indice indice) {
    Indice count = 0;
    No* noAtual = *lista.inicio;
    while (noAtual != NULL)
    {
        count += 1;
        if(count == indice) break;
        noAtual = noAtual->proximo;
    }
    //noAtual representa o nó anterior ao buscado

    if(noAtual == NULL || noAtual->proximo == NULL)
        return NULL;
    else
        return noAtual->proximo;
}

No* retornarElementoPorValor(Lista lista, void *valor) {
    No* noAtual = *lista.inicio;
    while (noAtual != NULL)
    {
        if(noAtual->valor == valor) break;
        noAtual = noAtual->proximo;
    }
    //noAtual representa o nó anterior ao buscado

    if(noAtual == NULL || noAtual->proximo == NULL)
        return NULL;
    else
        return noAtual->proximo;
}

void adicionarElementoAoFinalDaLista(Lista lista, void* novoValor) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = novoValor;
    novoNo->proximo = NULL;

    No* noAtual = *lista.inicio;
    while(noAtual->proximo != NULL) noAtual = noAtual->proximo;

    noAtual->proximo = novoNo;
}

void adicionarElementoAoInicioDaLista(Lista lista, void* novoValor) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = novoValor;
    novoNo->proximo = *lista.inicio;

    lista.inicio = &novoNo;
}

void removerElementoDaListaPorValor(Lista lista, void* valor) {
    if((*lista.inicio)->valor == valor)
    {
        lista.inicio = &(*lista.inicio)->proximo;
    }
    else
    {
        No* noAtual = *lista.inicio;
        while(noAtual != NULL)
        {
            if(noAtual->valor == valor) break;
            noAtual = noAtual->proximo;
        }
        //noAtual representa o nó anterior ao excluido

        //se houver um nó indice-1 && se houver um proximo nó...
        if(noAtual != NULL && noAtual->proximo != NULL)
        {
            No* noApagado = noAtual->proximo;
            noAtual->proximo = noApagado->proximo;
            apagarNo(noApagado);
        }
    }
}

void removerElementoDaListaPorIndice(Lista lista, Indice indice) {
    if(indice == 0)
    {
        lista.inicio = &(*lista.inicio)->proximo;
    }
    else
    {
        Indice count = 0;
        No* noAtual = *lista.inicio;
        while(noAtual != NULL)
        {
            count += 1;
            if(count == indice) break;
            noAtual = noAtual->proximo;
        }
        //noAtual representa o nó anterior ao excluido

        //se houver um nó indice-1 && se houver um proximo nó...
        if(noAtual != NULL && noAtual->proximo != NULL)
        {
            No* noApagado = noAtual->proximo;
            noAtual->proximo = noApagado->proximo;
            apagarNo(noApagado);
        }
    }
}

void apagarLista(Lista lista) {
    No* noAtual = *lista.inicio;
    lista.inicio = NULL;

    while(noAtual->proximo != NULL) {
        No* temp = noAtual;
        noAtual = noAtual->proximo;
        apagarNo(&temp);
    }
}

void apagarNo(No **no) {
    free((*no)->valor);
    free((*no));
}