#include "../headers/includeLibrarys.h"
#include "../headers/genericList.h"


NoLista retornarElementoDaLista(Lista *lista, Indice indice) {
    if(indice >= lista->len)
        return NULL;

    NoLista noAtual = lista->inicio;
    for(ListaLen i = 0; i < indice; i++) {
        noAtual = noAtual->proximo;
    }

    return noAtual;
}

void criarLista(Lista **listaPtr, TamanhoData tamanhoData) {
    *listaPtr = malloc(sizeof *listaPtr); //M
    (*listaPtr)->inicio = NULL;
    (*listaPtr)->len = 0u;
    (*listaPtr)->tamData = tamanhoData;
}

void adicionarPrimeiroItemNaLista(Lista *lista, void* novoItem) {
    lista->inicio = malloc(sizeof *lista->inicio);
    lista->inicio->proximo = NULL;
    lista->inicio->data = novoItem;
    lista->len += 1;
}

void adicionarItemAoInicioDaLista(Lista *lista, void* novoItem) {
    if(lista->inicio == NULL) {
        adicionarPrimeiroItemNaLista(lista, novoItem);
        return;
    }

    NoLista novoNo = criarNovoNo(novoItem/*, lista->tamData*/);
    novoNo->proximo = lista->inicio;
    lista->inicio = novoNo;
    lista->len += 1;
}

void adicionarItemAoFinalDaLista(Lista *lista, void* novoItem) {
    if(lista->inicio == NULL) {
        adicionarPrimeiroItemNaLista(lista, novoItem);
        return;
    }

    NoLista noAtual = lista->inicio;
    for(ListaLen i = 0u; i < (lista->len - 1); i++) {
        noAtual = noAtual->proximo;
    }

    NoLista novoNo = criarNovoNo(novoItem/*, lista->tamData*/);
    noAtual->proximo = novoNo;
    lista->len += 1;
}

NoLista criarNovoNo(void *data/*, TamanhoData tamData*/) {
    NoLista novoNo = malloc(sizeof *novoNo);
    novoNo->proximo = NULL;
    novoNo->data = data;
    return novoNo;   
}

void apagarLista(Lista **listaPtr) {
    NoLista noAtual = (*listaPtr)->inicio;
    for(ListaLen i = 0u; i < (*listaPtr)->len; i++) {
        NoLista proximoNo = noAtual->proximo;
        //free(noAtual->data);
        free(noAtual);
        noAtual = proximoNo;
    }

    free(*listaPtr);
}
