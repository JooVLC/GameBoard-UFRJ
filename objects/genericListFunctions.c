#include "../headers/genericList.h"

#ifndef INCLUDE_STRING
    #define INCLUDE_STRING 1
    #include <string.h>
#endif

#ifndef INCLUDE_STDLIB
        #define INCLUDE_STDLIB 1
        #include <stdlib.h>
#endif


void criarListaDeTipoGenerico(Lista **novaLista, size_t tamanhoElemento, void* primeiroValor) {
    InicioLista inicio = malloc(sizeof(No));
    inicio->proximo = NULL;
    if(primeiroValor != NULL)
    {
        inicio->valor = malloc(tamanhoElemento);
        memmove(inicio->valor, primeiroValor, tamanhoElemento);
    }
    else
        inicio->valor = NULL;

    (*novaLista)->tamanhoElementos = tamanhoElemento;
    (*novaLista)->inicio = &inicio;
}

No* retornarElementoPorIndice(Lista lista, Indice indice) {
    Indice count = 0;
    No* noAtual = *lista.inicio;
    while (noAtual != NULL)
    {
        if(count == indice) break;
        count += 1;
        noAtual = noAtual->proximo;
    }
    //noAtual representa o buscado

    return noAtual;;
}

No* retornarElementoPorValor(Lista lista, void *valor) {
    No* noAtual = *lista.inicio;
    while (noAtual != NULL)
    {
        if(noAtual->valor == valor) break;
        noAtual = noAtual->proximo;
    }
    //noAtual representa o buscado

    return noAtual;
}

No* adicionarElementoAoFinalDaLista(Lista lista, void* novoValor) {
    No *novoNo = malloc(sizeof(No));
    novoNo->valor = malloc(lista.tamanhoElementos);
    memmove(novoNo->valor, novoValor, lista.tamanhoElementos);
    novoNo->proximo = NULL;

    No* noAtual = *lista.inicio;
    while(noAtual->proximo != NULL) noAtual = noAtual->proximo;

    noAtual->proximo = novoNo;
    return novoNo;
}

No* adicionarElementoAoInicioDaLista(Lista lista, void* novoValor) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = malloc(lista.tamanhoElementos);
    memmove(novoNo->valor, novoValor, lista.tamanhoElementos);
    novoNo->proximo = *lista.inicio;

    *lista.inicio = novoNo;
    return novoNo;
}

No* adicionarElementoPorIndice(Lista lista, void* novoValor, Indice indice) {
    No* noAlterado = retornarElementoPorIndice(lista, indice);

    if(noAlterado == NULL)
        return NULL;
    
    free(noAlterado->valor);
    noAlterado->valor = malloc(lista.tamanhoElementos);
    memmove(noAlterado->valor, novoValor, lista.tamanhoElementos);
    return noAlterado;
}

No* adicionarElementoPorValor(Lista lista, void* novoValor, void* valor) {
    No* noAlterado = retornarElementoPorValor(lista, valor);

    if(noAlterado == NULL)
        return NULL;
    
    free(noAlterado->valor);
    noAlterado->valor = malloc(lista.tamanhoElementos);
    memmove(noAlterado->valor, novoValor, lista.tamanhoElementos);
    return noAlterado;
}

void removerElementoDaListaPorValor(Lista lista, void* valor) {
    if((*lista.inicio)->valor == valor)
    {
        *lista.inicio = (*lista.inicio)->proximo;
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
            apagarNo(&noApagado);
        }
    }
}

void removerElementoDaListaPorIndice(Lista lista, Indice indice) {
    if(indice == 0)
    {
        *lista.inicio = (*lista.inicio)->proximo;
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
            apagarNo(&noApagado);
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
    free(*no);
}

size_t listalen(Lista lista) {
    size_t len = 0;
    No* noAtual = *lista.inicio;
    while (noAtual != NULL)
    {
        noAtual = noAtual->proximo;
        len += 1;
    }
    return len;
}
