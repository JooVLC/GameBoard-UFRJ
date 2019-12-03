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
    CorPeca corVitoriosa;
    while(jogo.jogando)
    {
        system(CLEAR);
        bool xequeMateDessaCor = xequemate(jogo) || xequeAgora(jogo);

        if(xequeAgora(jogo)) {
            corVitoriosa = determinarVencedorAposXequeAgora(&jogo);
            continue;
        }
        if(xequemate(jogo)) {
            corVitoriosa = determinarVencedorAposXequeMate(&jogo);
            continue;
        }

        printf("Vez do jogador %s jogar!!!\n\n", jogo.jogadores[jogo.corJogando].nome);
        printarTabuleiro(jogo.tabuleiro, jogo.tabuleiro[0][0], NULL, jogo.corJogando);
        
        Posicao posicaoMovimento = converterPosicaoTelaParaCartesiano(pedirPecaMovidaJogador(), jogo.corJogando);
        CasaTabuleiro pecaTentandoMover = jogo.tabuleiro[posicaoMovimento.linha][posicaoMovimento.coluna];
        getchar();

        if(pecaTentandoMover.peca != NULL && pecaTentandoMover.peca->cor != jogo.corJogando)
        {
            puts("Peça de cor diferenta da sua, tente outra casa...");
            getchar();
            continue;
        }

        ListaCasaTabuleiro** movimentosPossiveisArray = movimentosPossiveis(pecaTentandoMover, jogo);
        if(movimentosPossiveisArray == NULL || (*movimentosPossiveisArray)->len == 0)
        {
            puts("Peça não pode se mover ou a casa está vazia, tente outra casa...");
            getchar();
            continue;
        }

        bool movimentoValido = false;
        CasaTabuleiro *movimento = NULL;
        while(!movimentoValido) {
            system(CLEAR);
            printarTabuleiro(jogo.tabuleiro, pecaTentandoMover, *movimentosPossiveisArray, jogo.corJogando);
            movimento = pedirMovimentoJogador(pecaTentandoMover, *movimentosPossiveisArray, jogo.corJogando);
            if(movimento != NULL)
                movimentoValido = true;
            else
                puts("Digite um dos movimentos válidos por favor");
        }

        moverPeca(pecaTentandoMover, jogo.tabuleiro, *movimento); //erro
        proximoTurno(&jogo); //erro
        apagarLista(movimentosPossiveisArray);
        free(movimentosPossiveisArray);
        getchar();
    }
    apagarJogo(jogoPtr);
    free(jogoPtr);
    printf("o jogador %s venceu!!!\n", corVitoriosa == BRANCO ? "branco" : "preto");
}

void printarTabuleiro(Tabuleiro tabuleiro, CasaTabuleiro casaMovida, ListaCasaTabuleiro* casasPossiveis, CorPeca corTurno) {
    printColunas(corTurno);
    printBordas(true);
    for(int i = 1; i <= QTD_CASAS_POR_LINHA; i++) {
        printLinhaIndice(QTD_CASAS_POR_COLUNA - i, tabuleiro, casaMovida, casasPossiveis, corTurno);
    }
    printBordas(false);
    puts("");
}

void printColunas(CorPeca corTurno) {
    char letra = corTurno == BRANCO ? 'a' : 'h';
    puts("");
    printf("    ");
    for(int i = 0; i < QTD_CASAS_POR_LINHA; i++)
        printf("  %c  ", corTurno == BRANCO ? letra + i : letra - i);
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

void printLinhaIndice(int linha, Tabuleiro tabuleiro, CasaTabuleiro casaMovida, ListaCasaTabuleiro* casasPossiveis, CorPeca corTurno) {
    static const char *const COR_MOVIMENTO = YELB;
    static const char *const COR_CASA_MOVIDA = REDB;

    printf("%d  |", corTurno == PRETO ? QTD_CASAS_POR_COLUNA - linha : linha + 1);

    for(int i = 0; i < QTD_CASAS_POR_LINHA; i++)
    {
        CasaTabuleiro peca = tabuleiro[linha][i];

        bool pintarCasaComoMovimento = casasPossiveis != NULL && movimentoExisteEmTalPosicao(linha, i, casasPossiveis);
        bool pintarCasaMovida = casasPossiveis != NULL && casaMovida.localizacao.linha == linha && casaMovida.localizacao.coluna == i;

        char pecaNaTela = peca.peca == NULL ? ' ' : letraDoTipoDaPeca(peca.peca->tipo);
        char pecaNaTelaString[] = { pecaNaTela, '\0' };

        const char *const corDaCasa = pintarCasaMovida ? COR_CASA_MOVIDA : (pintarCasaComoMovimento ? COR_MOVIMENTO : (peca.cor == BRANCO ? NULL_COLOR : BLKB));
        const char *const corDaPeca = peca.peca != NULL ? (peca.peca->cor == BRANCO ? BWHT : BBLK) : corDaCasa;

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
    puts("Digite a linha e coluna (%d%c):");
    getPosicaoDoUsuario(&linha, &coluna);

    Posicao posicao;
    posicao.linha = linha;
    posicao.coluna = coluna - 'a';
    return posicao;
}

CasaTabuleiro* pedirMovimentoJogador(CasaTabuleiro pecaMovida, ListaCasaTabuleiro *movimentos, CorPeca corTurno) {
    Posicao posAtual = { pecaMovida.peca->posicao.linha, pecaMovida.peca->posicao.coluna };
    Posicao posAtualTela = converterPosicaoCartesianoParaTela(posAtual, corTurno);
    for(size_t i = 0; i < movimentos->len; i++)
    {
        CasaTabuleiro* novaPosicao = retornarElementoDaLista(movimentos, i)->data;
        Posicao posProxima = { novaPosicao->localizacao.linha, novaPosicao->localizacao.coluna };
        Posicao posProximaTela = converterPosicaoCartesianoParaTela(posProxima, corTurno);

        printf("\t%lu -> %d%c para %d%c\n", i + 1, 
            posAtualTela.linha, posAtualTela.coluna+'a',
            posProximaTela.linha, posProximaTela.coluna+'a');
    }

    int numeroDigitado;
    puts("Digite o numero do seu proximo movimento:");
    getNumeroDoUsuario(&numeroDigitado, movimentos->len);
    return retornarElementoDaLista(movimentos, numeroDigitado - 1)->data;
}

void printc(const char *const str, const char *const color, bool corDeBackground) {
    printf("%s%s%s", color, str, corDeBackground ? "" : COLOR_RESTART);
}

void getPosicaoDoUsuario(int *linha, char *coluna) {
    char digitacao[LEN_DIGITACAO_MAX];
    bool digitacaoCorreta = false;
    while(!digitacaoCorreta) {
        fgets(digitacao, LEN_DIGITACAO_MAX, stdin);
        if(sscanf(digitacao, "%d%c\n", linha, coluna) == 2)
        {
            if(*linha < 1 || *linha > 8 || *coluna < 'a' || *coluna > 'h')
                puts("Digite um linha/coluna valida!");
            else
                digitacaoCorreta = true;
        }
        else
            puts("Digite no formato exigido!");
    }
    limparBuffer(digitacao, LEN_DIGITACAO_MAX);
}

void getNumeroDoUsuario(int *num, int maxNum) {
    char digitacao[LEN_DIGITACAO_MAX];
    bool digitacaoCorreta = false;
    while(!digitacaoCorreta) {
        fgets(digitacao, LEN_DIGITACAO_MAX, stdin);
        if(sscanf(digitacao, "%d\n", num) == 1)
        {
            if(*num < 1 || *num > maxNum)
                puts("Digite no intervalo valido!");
            else
                digitacaoCorreta = true;
        }
        else
            puts("Digite no formato exigido!");
    }
    limparBuffer(digitacao, LEN_DIGITACAO_MAX);
}

void limparBuffer(char str[], size_t tamanhoDesejado) {
    size_t strLen = strlen(str);
    if(strLen != tamanhoDesejado - 1) {
        str[strLen-1] = 0;
    }
    else {           
        char c;
        while((c = getchar()) && c != EOF && c != '\n');   
    }
}
