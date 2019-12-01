#include "../headers/includeLibrarys.h"
#include "../headers/typesXadrez.h"
#include "../headers/functionsXadrez.h"

void criarJogador(Jogador* jogador, Nome nomeJogador, CorPeca corJogador) {
    jogador->corDasPecas = corJogador;
    strcpy(jogador->nome, nomeJogador);
}

Peca** criarPeoes(CorPeca corCriada) {
    static const int QTD_PEOES = QTD_CASAS_POR_COLUNA;
    Peca** peoes = malloc(sizeof(Peca*) * QTD_PEOES);

    for(int i = 0; i < QTD_PEOES; i++)
    {
        Peca* novoPeao = malloc(sizeof(novoPeao));
        novoPeao->emXeque = false;
        novoPeao->evitandoXequeMate = false;
        novoPeao->tipo = PEAO;
        novoPeao->cor = corCriada;
        
        peoes[i] = novoPeao;
    }

    return peoes;
}

Peca** criarPecasEspeciais(CorPeca corCriada) {
    static const int QTD_PECAS = QTD_CASAS_POR_COLUNA;
    Peca** pecas = malloc(QTD_PECAS * sizeof(Peca*));

    for(int i = 0; i < QTD_PECAS; i++)
    {
        Peca *novaPeca = malloc(sizeof(Peca));
        novaPeca->cor = corCriada;
        novaPeca->emXeque = false;
        novaPeca->evitandoXequeMate = false;

        pecas[i] = novaPeca;
    }
    pecas[0]->tipo = TORRE;
    pecas[1]->tipo = CAVALO;
    pecas[2]->tipo = BISPO;
    pecas[3]->tipo = RAINHA;
    pecas[4]->tipo = REI;
    pecas[5]->tipo = BISPO;
    pecas[6]->tipo = CAVALO;
    pecas[7]->tipo = TORRE;

    return pecas;
}

Jogo* inicializarJogo(Nome nomeJogadorBranco, Nome nomeJogadorPreto) {
    Jogo *novoJogo = malloc(sizeof *novoJogo);

    criarJogador(&novoJogo->jogadores[0], nomeJogadorBranco, BRANCO);
    criarJogador(&novoJogo->jogadores[1], nomeJogadorPreto, PRETO);

    //Jogador Branco vai primeiro:
    novoJogo->corJogando = BRANCO;
    novoJogo->turno = 1;
    novoJogo->jogando = true;
    inicializarTabuleiro(novoJogo->tabuleiro);
    inicializarPecas(novoJogo->tabuleiro);

    return novoJogo;
}

void apagarJogo(Jogo** jogo) {
    for(int i = 0; i < QTD_CASAS_POR_COLUNA; i++) {
        for(int j = 0; j < QTD_CASAS_POR_LINHA; j++) {
            Peca *peca = (*jogo)->tabuleiro[i][j].peca;
            free(peca);
        }
    }
    free(*jogo);
}

void inicializarTabuleiro(Tabuleiro novoTabuleiro) {
    static const CorPeca COR_INICIAL = PRETO; //Cor da casa [0][0]

    CorPeca corDaCasa = COR_INICIAL;
    for(int i = 0; i < QTD_CASAS_POR_LINHA; i++)
    {
        for(int j = 0; j < QTD_CASAS_POR_COLUNA; j++)
        {
            CasaTabuleiro novaCasa;
            Posicao localizacaoNovaCasa = { i, j };
            novaCasa.localizacao = localizacaoNovaCasa;
            novaCasa.cor = corDaCasa;
            novaCasa.peca = NULL;
            novoTabuleiro[i][j] = novaCasa;

            corDaCasa = !corDaCasa;
        }

        //proxima linha a cor da casa é igual a cor da casa da ultima coluna da linha anterior
        corDaCasa = !corDaCasa;
    }
}

void inicializarPecas(Tabuleiro novoTabuleiro) {
    static const int QTD_LINHAS_COM_PECAS = 2;
    Peca **peoes, **outrasPecas;

    peoes = criarPeoes(BRANCO);
    outrasPecas = criarPecasEspeciais(BRANCO);
    for(int i = 0; i < QTD_LINHAS_COM_PECAS; i++)
    {
        for(int j = 0; j < QTD_CASAS_POR_COLUNA; j++)
        {
            if(i == 0)
                novoTabuleiro[i][j].peca = outrasPecas[j];
            else
                novoTabuleiro[i][j].peca = peoes[j];

            Posicao posicaoPeca = { i, j };
            novoTabuleiro[i][j].peca->posicao = posicaoPeca; 
        }    
    }
    free(peoes);
    free(outrasPecas);

    peoes = criarPeoes(PRETO);
    outrasPecas = criarPecasEspeciais(PRETO);
    for(int i = QTD_CASAS_POR_LINHA - 1; i >= QTD_CASAS_POR_LINHA - QTD_LINHAS_COM_PECAS; i--)
    {
        for(int j = 0; j < QTD_CASAS_POR_COLUNA; j++)
        {
            if(i == QTD_CASAS_POR_LINHA - 1)
                novoTabuleiro[i][j].peca = outrasPecas[j];
            else
                novoTabuleiro[i][j].peca = peoes[j];

            Posicao posicaoPeca = { i, j };
            novoTabuleiro[i][j].peca->posicao = posicaoPeca; 
        }    
    }
    free(peoes);
    free(outrasPecas);
}

void inverterTabuleiro(Tabuleiro tabuleiro) {
    inverterLinhasTabuleiro(tabuleiro);
    inverterColunasTabuleiro(tabuleiro);
}

void inverterLinhasTabuleiro(Tabuleiro tabuleiro) {
        for(int i = 0; i < QTD_CASAS_POR_LINHA; i++) {
        //j(de 0 ate x) e k(do final ate x) onde x e onde eles se encontram (metade do tabuleiro)
        int metadeDoTabuleiro = QTD_CASAS_POR_COLUNA/2;
        for(int j = 0, k = QTD_CASAS_POR_COLUNA - 1; k >= metadeDoTabuleiro && j < metadeDoTabuleiro; j++, k--) {
            Posicao posTemp = tabuleiro[j][i].localizacao;
            tabuleiro[j][i].localizacao = tabuleiro[k][i].localizacao;
            tabuleiro[k][i].localizacao = posTemp;

            CasaTabuleiro temp = tabuleiro[j][i];
            tabuleiro[j][i] = tabuleiro[k][i];
            tabuleiro[k][i] = temp;

            if(tabuleiro[j][i].peca != NULL)
                tabuleiro[j][i].peca->posicao = tabuleiro[j][i].localizacao;
            if(tabuleiro[k][i].peca != NULL)
                tabuleiro[k][i].peca->posicao = tabuleiro[k][i].localizacao;
        }
    }
}

void inverterColunasTabuleiro(Tabuleiro tabuleiro) {
    for(int i = 0; i < QTD_CASAS_POR_COLUNA; i++) {
        //j(de 0 ate x) e k(do final ate x) onde x e onde eles se encontram (metade do tabuleiro)
        int metadeDoTabuleiro = QTD_CASAS_POR_LINHA/2;
        for(int j = 0, k = QTD_CASAS_POR_LINHA - 1; k >= metadeDoTabuleiro && j < metadeDoTabuleiro; j++, k--) {
            Posicao posTemp = tabuleiro[i][j].localizacao;
            tabuleiro[i][j].localizacao = tabuleiro[i][k].localizacao;
            tabuleiro[i][k].localizacao = posTemp;

            CasaTabuleiro temp = tabuleiro[i][j];
            tabuleiro[i][j] = tabuleiro[i][k];
            tabuleiro[i][k] = temp;

            if(tabuleiro[i][j].peca != NULL)
                tabuleiro[i][j].peca->posicao = tabuleiro[i][j].localizacao;
            if(tabuleiro[i][k].peca != NULL)
                tabuleiro[i][k].peca->posicao = tabuleiro[i][k].localizacao;
        }
    }
}

void proximoTurno(Jogo *jogo) {
    jogo->turno += 1;
    jogo->corJogando = !(jogo->corJogando);
    inverterTabuleiro(jogo->tabuleiro);
}

Posicao converterPosicaoTelaParaCartesiano(Posicao posicaoTela, CorPeca corTurno) {
    Posicao posicaoPlano;

    posicaoPlano.linha = corTurno == PRETO ? QTD_CASAS_POR_COLUNA - posicaoPlano.linha : posicaoTela.linha - 1;
    posicaoPlano.coluna = corTurno == PRETO ? (QTD_CASAS_POR_LINHA - 1) - posicaoTela.coluna : posicaoTela.coluna;

    return posicaoPlano;
}

Posicao converterPosicaoCartesianoParaTela(Posicao posicaoCartesiano, CorPeca corTurno) {
    Posicao posicaoTela;

    posicaoTela.linha = corTurno == PRETO ? QTD_CASAS_POR_COLUNA - posicaoCartesiano.linha : posicaoCartesiano.linha + 1;
    posicaoTela.coluna = corTurno == PRETO ? (QTD_CASAS_POR_LINHA - 1) - posicaoCartesiano.coluna : posicaoCartesiano.coluna;

    return posicaoTela;
}
