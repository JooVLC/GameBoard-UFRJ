#include "../headers/includeLibrarys.h"
#include "../headers/genericList.h"
#include "../headers/listXadrez.h"

void criarListaCasasTabuleiro(ListaCasaTabuleiro **lista) {
    criarListaDeTipoGenerico(lista, sizeof(CasaTabuleiro), NULL);
    printf("criando: %d\n", (*lista)->inicio->proximo == NULL);
}

CasaTabuleiro* ListaParaArrayDeCasaTabuleiro(ListaCasaTabuleiro *lista) {
    if(listalen(lista) == 1)
        return NULL;

    size_t listaTamanho = listalen(lista);
    CasaTabuleiro* array = malloc(lista->tamanhoElementos * listaTamanho);

    for(size_t i = 0; i < listaTamanho; i++)
        array[i] = *((CasaTabuleiro*)retornarElementoPorIndice(*lista, i)->valor);

    return array;
}

void adicionarNovoMovimento(ListaCasaTabuleiro *lista, CasaTabuleiro peca) {
    if(listaEstaVazia(lista))
        adicionarElementoPorIndice(*lista, &peca, 0);
    else
        adicionarElementoAoFinalDaLista(*lista, &peca);
}

bool listaEstaVazia(ListaCasaTabuleiro *lista) {
    if(lenListaCasaTabuleiro(lista) == 0)
        return true;
    else
        return false; 
}

CasaTabuleiro* retornarMovimentoPeloIndice(ListaCasaTabuleiro *lista, Indice indice) {
    if(listaEstaVazia(lista))
        return NULL;
    
    return (CasaTabuleiro*)retornarElementoPorIndice(*lista, indice)->valor;
}

size_t lenListaCasaTabuleiro(ListaCasaTabuleiro *lista) {
    puts("len error");
    printf("lista.inicio.proximo == NULL ? R:%d\n", lista->inicio->proximo == NULL ? 1 : 0);
    if(lista->inicio == NULL || lista->inicio->valor == NULL || lista->inicio->proximo == NULL) {
        puts("if0");
        return 0;
    }
    else
    {
        puts("else0");
        return listalen(lista);
    }
}
