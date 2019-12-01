#include "../headers/includeLibrarys.h"
//#include "../headers/genericList.h"


/*void criarListaDeTipoGenerico(Lista **novaLista, size_t tamanhoElemento, void* primeiroValor) {
    *novaLista = calloc(1, sizeof **novaLista);
    InicioLista inicio = calloc(1, sizeof *inicio);
    inicio->proximo = NULL;
    puts("gay");
    if(primeiroValor != NULL) {
        puts("valor existe");
        inicio->valor = calloc(1, tamanhoElemento);
        memcpy(inicio->valor, primeiroValor, tamanhoElemento);
    }
    else {
        inicio->valor = NULL;
        puts("valor nao existe");
    }

    (*novaLista)->tamanhoElementos = tamanhoElemento;
    puts("aaa");
    memcpy((*novaLista)->inicio, inicio, sizeof *inicio);
    puts("bbb");
}

No* retornarElementoPorIndice(Lista lista, Indice indice) {
    Indice count = 0;
    No* noAtual = lista.inicio;
    while (noAtual != NULL) {
        if(count == indice) break;
        count += 1;
        noAtual = noAtual->proximo;
    }
    //noAtual representa o buscado

    return noAtual;;
}

No* retornarElementoPorValor(Lista lista, void *valor) {
    No* noAtual = lista.inicio;
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

    No* noAtual = lista.inicio;
    while(noAtual->proximo != NULL) noAtual = noAtual->proximo;

    noAtual->proximo = novoNo;
    return novoNo;
}

No* adicionarElementoAoInicioDaLista(Lista lista, void* novoValor) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = malloc(lista.tamanhoElementos);
    memmove(novoNo->valor, novoValor, lista.tamanhoElementos);
    novoNo->proximo = lista.inicio;

    lista.inicio = novoNo;
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
    if(lista.inicio->valor == valor)
    {
        lista.inicio = lista.inicio->proximo;
    }
    else
    {
        No* noAtual = lista.inicio;
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
        lista.inicio = lista.inicio->proximo;
    }
    else
    {
        Indice count = 0;
        No* noAtual = lista.inicio;
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
    No* noAtual = lista.inicio;
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

size_t listalen(Lista *lista) {
    size_t len = 0;
    No* noAtual = lista->inicio;
    puts("erro no inicio");
    while (noAtual != NULL)
    {
        puts("looping");
        noAtual = noAtual->proximo;
        printf("%d\n", noAtual == NULL ? 1 : 0);
        len += 1;
    }
    printf("len: %d\n", len);
    return len;
}
*/

typedef struct Data {
    struct Data* proximo;
    void* data;
} Data;

typedef Data *InicioLista;
typedef Data *NoLista;
typedef size_t ListaLen;
typedef size_t TamanhoData;

typedef struct Lista {
    InicioLista inicio;
    ListaLen len;
    TamanhoData tamData;
} Lista;

void criarLista(Lista **listaPtr, TamanhoData tamanhoData) {
    *listaPtr = malloc(sizeof *listaPtr); //M
    (*listaPtr)->inicio = NULL;
    (*listaPtr)->len = 0u;
    (*listaPtr)->tamData = tamanhoData;
}

void adicionarPrimeiroItemNaLista(Lista *lista, void* novoItem) {
    lista->inicio = malloc(sizeof *lista->inicio); //M
    lista->inicio->proximo = NULL;
    lista->inicio->data = malloc(lista->tamData);
    memcpy(lista->inicio->data, novoItem, lista->tamData);
    lista->len += 1;
}

void adicionarItemAoInicioDaLista(Lista *lista, void* novoItem) {
    if(lista->inicio == NULL) {
        adicionarItemAoInicioDaListaNoInicio(lista, novoItem);
        return;
    }

    NoLista novoNo = criarNovoNo(novoItem, lista->tamData);
    novoNo->proximo = lista->inicio;
    lista->inicio = novoNo;
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

    NoLista novoNo = criarNovoNo(novoItem, lista->tamData);
    noAtual->proximo = novoNo;
    lista->len += 1;
}

NoLista criarNovoNo(void *data, TamanhoData tamData) {
    NoLista novoNo = malloc(sizeof *novoNo);
    novoNo->proximo = NULL;
    novoNo->data = malloc(tamData);
    memcpy(novoNo->data, data, tamData); 
    return novoNo;   
}

void apagarLista(Lista **listaPtr) {
    NoLista noAtual = (*listaPtr)->inicio;
    for(ListaLen i = 0u; i < (*listaPtr)->len; i++) {
        NoLista proximoNo = noAtual->proximo;
        free(noAtual->data);
        free(noAtual);
        noAtual = proximoNo;
    }

    free(*listaPtr);
}
