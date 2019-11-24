#include "../headers/genericList.h";
#include "../headers/listXadrez.h"

ListaCasaTabuleiro criarListaCasasTabuleiro() {
    Lista listaCasas = criarListaDeTipoGenerico(sizeof(CasaTabuleiro), NULL);
    return listaCasas;
}

CasaTabuleiro* ListaParaArrayDeCasaTabuleiro(ListaCasaTabuleiro lista) {
    size_t listaTamanho = listalen(lista);
    CasaTabuleiro* array = malloc(lista.tamanhoElementos * listaTamanho);

    for(int i = 0; i < listaTamanho; i++)
        array[i] = *((CasaTabuleiro*)retornarElementoPorIndice(lista, i)->valor);

    return array;
}

void adicionarNovoMovimento(ListaCasaTabuleiro lista, CasaTabuleiro peca) {
    if(listalen(lista) == 1)
        (*lista.inicio)->valor = &peca;
    else
        adicionarElementoAoFinalDaLista(lista, &peca);
}