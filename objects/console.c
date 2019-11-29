#include "../headers/includeLibrarys.h"
#include "../headers/typesXadrez.h"
#include "../headers/functionsXadrez.h"
#include "../headers/listXadrez.h"
#include "../headers/consoleLib.h"

void iniciarJogoConsole(Nome jogadorBranco, Nome jogadorPreto) {
    Jogo jogo = inicializarJogo(jogadorBranco, jogadorPreto);
    while(jogo.jogando)
    {
        system("cls;clear");
        printf("Vez do jogador %s jogar!!!\n\n", jogo.jogadores[jogo.corJogando].nome);
        printarTabuleiro(jogo.tabuleiro);
        
        Posicao posicaoMovimento = converterPosicaoTelaParaCartesiano(pedirPecaMovidaJogador());
        printf("pedido feito - %d%d\n", posicaoMovimento.linha, posicaoMovimento.coluna);
        CasaTabuleiro pecaTentandoMover = jogo.tabuleiro[posicaoMovimento.linha][posicaoMovimento.coluna];
        ListaCasaTabuleiro* movimentosPossiveisArray = movimentosPossiveis(pecaTentandoMover, jogo);
        puts("passou");
        if(movimentosPossiveisArray == NULL || listaEstaVazia(movimentosPossiveisArray))
        {
            puts("Peça não pode se mover ou a casa está vazia, tente outra casa...");
            getchar();
            continue;
        }
        puts("passou2");

        bool movimentoValido = false;
        CasaTabuleiro *movimento = NULL;
        while(!movimentoValido) {
            movimento = pedirMovimentoJogador(pecaTentandoMover, movimentosPossiveisArray);
            if(movimento != NULL)
                movimentoValido = true;
            else
                puts("Digite um dos movimentos válidos por favor");
        }

        moverPeca(pecaTentandoMover, jogo.tabuleiro, *movimento);
        proximoTurno(&jogo);
        apagarLista(*movimentosPossiveisArray);
        free(movimentosPossiveisArray);
    }
}

void printarTabuleiro(Tabuleiro tabuleiro) {
    printColunas();
    for(int i = 1; i <= QTD_CASAS_POR_LINHA; i++) {
        printLinhaIndice(QTD_CASAS_POR_COLUNA - i, tabuleiro);
    }
}

void printColunas(void) {
    char letra = 'a';
    puts("");
    printf(" ");
    for(int i = 0; i < QTD_CASAS_POR_LINHA; i++)
        printf("  %c  ", letra + i);
    puts("");
}

void printLinhaIndice(int linha, Tabuleiro tabuleiro) {
    printf("%d  ", QTD_CASAS_POR_COLUNA - linha);
    for(int i = 0; i < QTD_CASAS_POR_LINHA; i++)
    {
        CasaTabuleiro peca = tabuleiro[linha][i];
        char pecaNaTela = peca.peca == NULL ? 0 : letraDoTipoDaPeca(peca.peca->tipo);
        printf("%c    ", pecaNaTela);
    }
    puts("");
}

char letraDoTipoDaPeca(TipoPeca tipoPeca) {
    char letra;
    switch (tipoPeca)
    {
        case PEAO:
            letra = 'P';
            break;
        case CAVALO:
            letra = 'C';
            break;
        case TORRE:
            letra = 'T';
            break;
        case BISPO:
            letra = 'B';
            break;
        case RAINHA:
            letra = 'Q';
            break;
        case REI:
            letra = 'K';
            break;
        default:
            letra = 'E'; //ERRO
            break;
    }

    return letra;
}

Posicao pedirPecaMovidaJogador(void) {
    int linha;
    char coluna;
    puts("Digite a linha e coluna (%d %c):");
    scanf("%d %c", &linha, &coluna);
    getchar();

    Posicao posicao;
    posicao.linha = linha - 1;
    posicao.coluna = coluna - 'a';
    return posicao;
}

CasaTabuleiro* pedirMovimentoJogador(CasaTabuleiro pecaMovida, ListaCasaTabuleiro *movimentos) {
    size_t tamanhoLista = lenListaCasaTabuleiro(movimentos);

    puts("\nDigite o número de um dos seguintes movimentos:");
    for(size_t i = 0; i < tamanhoLista; i++)
    {
        CasaTabuleiro* novaPosicao = retornarMovimentoPeloIndice(movimentos, i);

        int linhaAtual = pecaMovida.peca->posicao.linha;
        int proximaLinha = novaPosicao->peca->posicao.linha;

        char colunaAtual = pecaMovida.peca->posicao.coluna + 'a';
        char proximaColuna = novaPosicao->peca->posicao.coluna + 'a';

        printf("\t%lu -> %d%c para %d%c\n", i + 1, linhaAtual, colunaAtual, proximaLinha, proximaColuna);
    }

    int numeroDigitado;
    scanf("%d", &numeroDigitado);
    getchar();
    return retornarMovimentoPeloIndice(movimentos, numeroDigitado);
}
