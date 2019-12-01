#include "./headers/includeLibrarys.h"

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

NoLista criarNovoNo(void *data, TamanhoData tamData);

NoLista retornarElementoDaLista(Lista *lista, Indice indice);

void apagarLista(Lista **listaPtr);


NoLista retornarElementoDaLista(Lista *lista, Indice indice) {
    if(indice >= lista->len || indice < 0)
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
    //puts("b");
    lista->inicio->proximo = NULL;
    lista->inicio->data = novoItem;
    //puts("c");
    //memcpy(lista->inicio->data, novoItem, lista->tamData);
    lista->len += 1;
    printf("len: %lu\n", lista->len);
}

void adicionarItemAoInicioDaLista(Lista *lista, void* novoItem) {
    if(lista->inicio == NULL) {
        puts("primeiro item");
        adicionarPrimeiroItemNaLista(lista, novoItem);
        return;
    }

    NoLista novoNo = criarNovoNo(novoItem, lista->tamData);
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

    NoLista novoNo = criarNovoNo(novoItem, lista->tamData);
    noAtual->proximo = novoNo;
    lista->len += 1;
}

NoLista criarNovoNo(void *data, TamanhoData tamData) {
    NoLista novoNo = malloc(sizeof *novoNo);
    novoNo->proximo = NULL;
    novoNo->data = data;
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

typedef struct Teste {
    int x;
    float y;
    char a;
} Teste;

int main(void) {
    Lista** lista = malloc(sizeof *lista);

    criarLista(lista, sizeof(Teste));

    Teste *v = malloc(sizeof *v);
    v->a = 'b';
    v->x = 1;
    v->y = 4;

    puts("teste1");
    adicionarItemAoInicioDaLista(*lista, v);
    for(ListaLen i = 0; i < (*lista)->len; i++) {
        printf("%c\n", ((Teste*)retornarElementoDaLista(*lista, i)->data)->a);
    }

    puts("teste2");
    Teste *c = malloc(sizeof *v);
    c->a = 'p';
    c->x = 1;
    c->y = 4;
    adicionarItemAoFinalDaLista(*lista, c);
    for(ListaLen i = 0; i < (*lista)->len; i++) {
        printf("%c\n", ((Teste*)retornarElementoDaLista(*lista, i)->data)->a);
    }

    apagarLista(lista);
    free(lista);
    puts("digite algo");
    getchar();
    return 0;
}