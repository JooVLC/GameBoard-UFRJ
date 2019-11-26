#include "./headers/includeLibrarys.h"
#include "./headers/typesXadrez.h"
#include "./headers/functionsXadrez.h"
#include "./headers/listXadrez.h"
#include "./headers/consoleLib.h"

void iniciarJogoConsole(Nome jogadorBranco, Nome jogadorPreto) {
    Jogo jogo = inicializarJogo(jogadorBranco, jogadorPreto);
    while(jogo.jogando)
    {
        printf("Vez do jogador %s jogar!!!\n\n", jogo.jogadores[jogo.corJogando]);
        printarTabuleiro(jogo.tabuleiro);
        
        Posicao posicaoMovimento = pedirPecaMovidaJogador();
        CasaTabuleiro pecaTentandoMover = jogo.tabuleiro[posicaoMovimento.linha][posicaoMovimento.coluna];
        ListaCasaTabuleiro* movimentosPossiveisArray = movimentosPossiveis(pecaTentandoMover, jogo);

        if(listaEstaVazia(*movimentosPossiveisArray))
        {
            puts("Peça não pode se mover, tente outra peça");
            continue;
        }

        bool movimentoValido = false;
        CasaTabuleiro *movimento = NULL;
        while(!movimentoValido) {
            movimento = pedirMovimentoJogador(pecaTentandoMover, *movimentosPossiveisArray);
            if(movimento != NULL)
                movimentoValido = true;
            else
                puts("Digite um dos movimentos válidos por favor");
        }

        moverPeca(pecaTentandoMover, jogo.tabuleiro, *movimento);
        proximoTurno(jogo);
        apagarLista(*movimentosPossiveisArray);
        free(movimentosPossiveisArray);
    }
}

void printarTabuleiro(Tabuleiro tabuleiro) {
    printColunas();
    for(int i = 0; i < QTD_CASAS_POR_LINHA; i++) {
        printLinhaIndice(QTD_CASAS_POR_COLUNA - i, tabuleiro);
        puts("");
    }
}

void printColunas(void) {
    char letra = 'a';
    for(int i = 0; i < QTD_CASAS_POR_LINHA; i++)
        printf("  %c  ", letra + i);
    puts("");
}

void printLinhaIndice(int indice, Tabuleiro tabuleiro) {

}

Posicao pedirPecaMovidaJogador(void) {

}

CasaTabuleiro* pedirMovimentoJogador(CasaTabuleiro pecaMovida, ListaCasaTabuleiro movimentos) {
    size_t tamanhoLista = lenListaCasaTabuleiro(movimentos);
    char linha, coluna;

    puts("\nDigite o número de um dos seguintes movimentos:");
    for(int i = 0; i < tamanhoLista; i++)
    {
        CasaTabuleiro* novaPosicao = retornarMovimentoPeloIndice(movimentos, i);

        int linhaAtual = pecaMovida.peca->posicao.linha;
        int proximaLinha = novaPosicao->peca->posicao.linha;

        char colunaAtual = pecaMovida.peca->posicao.coluna + 'a';
        char proximaColuna = novaPosicao->peca->posicao.coluna + 'a';

        printf("\t%d -> %d%c para %d%c\n", i + 1, linhaAtual, colunaAtual, proximaLinha, proximaColuna);
    }

    int numeroDigitado;
    scanf("%d", &numeroDigitado);
    getchar();
    return retornarMovimentoPeloIndice(movimentos, numeroDigitado);
}
