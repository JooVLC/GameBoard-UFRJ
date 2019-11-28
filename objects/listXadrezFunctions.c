#include "../headers/genericList.h"
#include "../headers/listXadrez.h"

ListaCasaTabuleiro* criarListaCasasTabuleiro() {
    Lista *listaCasas = malloc(sizeof(Lista));
    criarListaDeTipoGenerico(&listaCasas, sizeof(CasaTabuleiro), NULL);
    return listaCasas;
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
    printf("prt == NULL ? R:%d\n", *lista->inicio == NULL ? 1 : 0);
    if(*lista->inicio == NULL || (*lista->inicio)->valor == NULL) {
        puts("if0");
        return 0;
    }
    else
    {
        puts("else0");
        return listalen(lista);
    }
}
