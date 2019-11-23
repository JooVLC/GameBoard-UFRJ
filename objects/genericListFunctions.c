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

No retornarElementoPorIndice(Indice indice) {

}

No retornarElementoPorValor(void *valor) {

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

}

void removerElementoDaListaPorIndice(Lista lista, Indice indice) {
    
}

void apagarLista(Lista lista) {
    No* noAtual = *lista.inicio;
    lista.inicio = NULL;

    while(noAtual->proximo != NULL) {
        No* temp = noAtual;
        noAtual = noAtual->proximo;
        free(temp->valor);
        free(temp);
    }
}