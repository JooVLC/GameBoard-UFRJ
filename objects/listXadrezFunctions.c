#include "../headers/includeLibrarys.h"
#include "../headers/genericList.h"
#include "../headers/listXadrez.h"

/*void criarListaCasasTabuleiro(ListaCasaTabuleiro **lista) {
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
}*/

void printLista(Lista *lista, char nomeLista[]) {
    printf("imprimindo lista: %s - tam: %d\n", nomeLista, lista != NULL ? lista->len : 0);
    for(int i = 0; i < lista->len; i++) {
        printf("id: %d - ", i);
        CasaTabuleiro* e = retornarElementoDaLista(lista, i)->data;
        if(e == NULL) 
            continue;
        printf("coord: %d %d\t", e->localizacao.linha, e->localizacao.coluna);
        printf("corCasa: %s\t", e->cor == BRANCO ? "B" : "P");
        printf("pecaNull: %s\t", e->peca == NULL ? "TRUE" : "FALSE");
        if(e->peca != NULL)
        {
            printf("Peca:  ");
            printf("coord: %d %d\t", e->peca->posicao.linha, e->peca->posicao.coluna);
            printf("tipo: %d - cor: %s\t", e->peca->tipo, e->cor == BRANCO ? "B" : "P");
        }
        puts("\n");
    }
    puts("fim");
    getchar();
}

void printArray(CasaTabuleiro **lista, char nomeLista[], int len) {
    printf("imprimindo lista: %s - tam: %d\n", nomeLista, len);
    for(int i = 0; i < len; i++) {
        puts("\n");
        CasaTabuleiro* e = lista[i];
        printf("id: %d - ", i);
        if(e == NULL) 
            continue;
        printf("coord: %d %d\t", e->localizacao.linha, e->localizacao.coluna);
        printf("corCasa: %s\t", e->cor == BRANCO ? "B" : "P");
        printf("pecaNull: %s\t", e->peca == NULL ? "TRUE" : "FALSE");
        if(e->peca != NULL)
        {
            printf("Peca:  ");
            printf("coord: %d %d\t", e->peca->posicao.linha, e->peca->posicao.coluna);
            printf("tipo: %d - cor: %s\t", e->peca->tipo, e->cor == BRANCO ? "B" : "P");
        }
    }
    puts("fim");
    getchar();
}