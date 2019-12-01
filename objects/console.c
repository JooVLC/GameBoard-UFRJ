#include "../headers/includeLibrarys.h"
#include "../headers/typesXadrez.h"
#include "../headers/functionsXadrez.h"
#include "../headers/listXadrez.h"
#include "../headers/consoleLib.h"
#include "../headers/colors.h"

void iniciarJogoConsole(Nome jogadorBranco, Nome jogadorPreto) {
    Jogo **jogoPtr = malloc(sizeof *jogoPtr);
    *jogoPtr = inicializarJogo(jogadorBranco, jogadorPreto);
    Jogo jogo = **jogoPtr;
    while(jogo.jogando)
    {
        system(CLEAR);
        printf("Vez do jogador %s jogar!!!\n\n", jogo.jogadores[jogo.corJogando].nome);
        printarTabuleiro(jogo.tabuleiro, jogo.tabuleiro[0][0], NULL);
        
        Posicao posicaoMovimento = converterPosicaoTelaParaCartesiano(pedirPecaMovidaJogador());
        CasaTabuleiro pecaTentandoMover = jogo.tabuleiro[posicaoMovimento.linha][posicaoMovimento.coluna];
        ListaCasaTabuleiro** movimentosPossiveisArray = malloc(sizeof *movimentosPossiveisArray);
        *movimentosPossiveisArray = movimentosPossiveis(pecaTentandoMover, jogo);
        if((*movimentosPossiveisArray)->len == 0)
        {
            puts("Peça não pode se mover ou a casa está vazia, tente outra casa...");
            getchar();
            continue;
        }

        bool movimentoValido = false;
        CasaTabuleiro *movimento = NULL;
        while(!movimentoValido) {
            system(CLEAR);
            printarTabuleiro(jogo.tabuleiro, pecaTentandoMover, *movimentosPossiveisArray);
            movimento = pedirMovimentoJogador(pecaTentandoMover, *movimentosPossiveisArray);
            if(movimento != NULL)
                movimentoValido = true;
            else
                puts("Digite um dos movimentos válidos por favor");
        }

        moverPeca(pecaTentandoMover, jogo.tabuleiro, *movimento);
        proximoTurno(&jogo);
        apagarLista(movimentosPossiveisArray);
        free(movimentosPossiveisArray);
    }
    apagarJogo(jogoPtr);
    free(jogoPtr);
}

void printarTabuleiro(Tabuleiro tabuleiro, CasaTabuleiro casaMovida, ListaCasaTabuleiro* casasPossiveis) {
    printColunas();
    printBordas(true);
    for(int i = 1; i <= QTD_CASAS_POR_LINHA; i++) {
        printLinhaIndice(QTD_CASAS_POR_COLUNA - i, tabuleiro, casaMovida, casasPossiveis);
    }
    printBordas(false);
    puts("");
}

void printColunas(void) {
    char letra = 'a';
    puts("");
    printf("    ");
    for(int i = 0; i < QTD_CASAS_POR_LINHA; i++)
        printf("  %c  ", letra + i);
    puts("");
}

void printBordas(bool bordaSuperior) {
    printf("   *");
    for(int i = 0; i < QTD_CASAS_POR_LINHA; i++){
        if(bordaSuperior)
            printf("_____");
        else
            printf("\u203E\u203E\u203E\u203E\u203E");
    }
    puts("*");
}

void printLinhaIndice(int linha, Tabuleiro tabuleiro, CasaTabuleiro casaMovida, ListaCasaTabuleiro* casasPossiveis) {
    static const char *const COR_MOVIMENTO = YELHB;
    static const char *const COR_CASA_MOVIDA = REDB;

    printf("%d  |", QTD_CASAS_POR_COLUNA - linha);

    for(int i = 0; i < QTD_CASAS_POR_LINHA; i++)
    {
        CasaTabuleiro peca = tabuleiro[linha][i];

        bool pintarCasaComoMovimento = casasPossiveis != NULL && movimentoExisteEmTalPosicao(linha, i, casasPossiveis);
        bool pintarCasaMovida = casasPossiveis != NULL && casaMovida.localizacao.linha == linha && casaMovida.localizacao.coluna == i;

        char pecaNaTela = peca.peca == NULL ? ' ' : letraDoTipoDaPeca(peca.peca->tipo);
        char pecaNaTelaString[] = { pecaNaTela, '\0' };

        const char *const corDaCasa = pintarCasaMovida ? COR_CASA_MOVIDA : (pintarCasaComoMovimento ? COR_MOVIMENTO : (peca.cor == BRANCO ? WHTHB : BLKHB));
        const char *const corDaPeca = peca.peca != NULL ? (peca.peca->cor == BRANCO ? BWHT : BBLK) : corDaCasa;
        bool corIgualCasaPeca = peca.peca != NULL && peca.cor != peca.peca->cor;

        printc("  ", corDaCasa, false);
        printc("", corDaCasa, true);
        printc(pecaNaTelaString, corDaPeca, false);
        printc("", corDaCasa, false);
        printc("  ", corDaCasa, false);
    }
    puts("|");
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
    puts("");
    puts("\nDigite o número de um dos seguintes movimentos:");
    Posicao posAtual = { pecaMovida.peca->posicao.linha, pecaMovida.peca->posicao.coluna };
    Posicao posAtualTela = converterPosicaoCartesianoParaTela(posAtual);
    for(size_t i = 0; i < movimentos->len; i++)
    {
        CasaTabuleiro* novaPosicao = retornarElementoDaLista(movimentos, i)->data;
        Posicao posProxima = { novaPosicao->localizacao.linha, novaPosicao->localizacao.coluna };
        Posicao posProximaTela = converterPosicaoCartesianoParaTela(posProxima);

        printf("\t%lu -> %d%c para %d%c\n", i + 1, 
            posAtualTela.linha, posAtualTela.coluna+'a',
            posProximaTela.linha, posProximaTela.coluna+'a');
    }

    int numeroDigitado;
    scanf("%d", &numeroDigitado);
    getchar();
    return retornarElementoDaLista(movimentos, numeroDigitado - 1)->data;
}

void printc(const char *const str, const char *const color, bool corDeBackground) {
    printf("%s%s%s", color, str, corDeBackground ? "" : COLOR_RESTART);
}
