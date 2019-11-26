#include "../headers/genericList.h";
#include "../headers/listXadrez.h"

ListaCasaTabuleiro* criarListaCasasTabuleiro() {
    Lista *listaCasas = malloc(sizeof(Lista));
    criarListaDeTipoGenerico(&listaCasas, sizeof(CasaTabuleiro), NULL);
    return listaCasas;
}

CasaTabuleiro* ListaParaArrayDeCasaTabuleiro(ListaCasaTabuleiro lista) {
    if(listalen(lista) == 1)
        return NULL;

    size_t listaTamanho = listalen(lista);
    CasaTabuleiro* array = malloc(lista.tamanhoElementos * listaTamanho);

    for(int i = 0; i < listaTamanho; i++)
        array[i] = *((CasaTabuleiro*)retornarElementoPorIndice(lista, i)->valor);

    return array;
}

void adicionarNovoMovimento(ListaCasaTabuleiro *lista, CasaTabuleiro peca) {
    if(listalen(*lista) == 1)
        adicionarElementoPorIndice(*lista, &peca, 0);
    else
        adicionarElementoAoFinalDaLista(*lista, &peca);
}

bool listaEstaVazia(ListaCasaTabuleiro lista) {
    if(lenListaCasaTabuleiro(lista) == 0)
        return true;
    else
        return false; 
}

CasaTabuleiro* retornarMovimentoPeloIndice(ListaCasaTabuleiro lista, Indice indice) {
    if(listaEstaVazia(lista))
        return NULL;
    
    return retornarElementoPorIndice(lista, indice);
}

size_t lenListaCasaTabuleiro(ListaCasaTabuleiro lista) {
    if((*lista.inicio)->valor == NULL)
        return 0;
    else
        return listalen(lista);
}