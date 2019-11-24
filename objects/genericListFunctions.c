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

No* adicionarElementoAoFinalDaLista(Lista lista, void* novoValor) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = novoValor;
    novoNo->proximo = NULL;

    No* noAtual = *lista.inicio;
    while(noAtual->proximo != NULL) noAtual = noAtual->proximo;

    noAtual->proximo = novoNo;
    return novoNo;
}

No* adicionarElementoAoInicioDaLista(Lista lista, void* novoValor) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = novoValor;
    novoNo->proximo = *lista.inicio;

    lista.inicio = &novoNo;
    return novoNo;
}

No* adicionarElementoPorIndice(Lista lista, void* novoValor, Indice indice) {
    No* noAlterado = retornarElementoPorIndice(lista, indice);

    if(noAlterado == NULL)
        return NULL;
    
    noAlterado->valor = novoValor;
    return noAlterado;
}

No* adicionarElementoPorValor(Lista lista, void* novoValor, void* valor) {
    No* noAlterado = retornarElementoPorValor(lista, valor);

    if(noAlterado == NULL)
        return NULL;
    
    noAlterado->valor = novoValor;
    return noAlterado;
}

void removerElementoDaListaPorValor(Lista lista, void* valor, bool valorFoiAlocado) {
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
            apagarNo(&noApagado, valorFoiAlocado);
        }
    }
}

void removerElementoDaListaPorIndice(Lista lista, Indice indice, bool valorFoiAlocado) {
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
            apagarNo(&noApagado, valorFoiAlocado);
        }
    }
}

void apagarLista(Lista lista, bool valorFoiAlocado) {
    No* noAtual = *lista.inicio;
    lista.inicio = NULL;

    while(noAtual->proximo != NULL) {
        No* temp = noAtual;
        noAtual = noAtual->proximo;
        apagarNo(&temp, valorFoiAlocado);
    }
}

void apagarNo(No **no, bool valorFoiAlocado) {
    if(valorFoiAlocado)
        free((*no)->valor);
        S
    free((*no));
}

size_t listalen(Lista lista) {
    size_t len = 0;
    No* noAtual = *lista.inicio;
    while (noAtual != NULL)
    {
        noAtual = noAtual->proximo;
        len++;
    }
    return len;
}