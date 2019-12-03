#ifndef XADREZ_FUNCOES
    #define XADREZ_FUNCOES 1

    #include "typesXadrez.h"
    #include "listXadrez.h"

    #ifndef INCLUDE_STDBOOL
        #define INCLUDE_STDBOOL 1
        #include <stdbool.h>
    #endif

    //FUNCOES DO JOGO 
        //Cria o jogo e retorna ele a partir dos nomes pegos do CMD
        Jogo* inicializarJogo(Nome nomeJogadorBranco, Nome nomeJogadorPreto);

        CorPeca determinarVencedorAposXequeMate(Jogo *jogo);

        //Apagar o jogo dando free em suas variaveis
        void apagarJogo(Jogo** jogo);

        //Cria o tabuleiro e inicializa ele
        void inicializarTabuleiro(Tabuleiro novoTabuleiro);

        //Cria as pecas e coloca elas nas posições padrões do xadrez
        void inicializarPecas(Tabuleiro novoTabuleiro);

        //Cria 8 peoes da cor desejada e retorna um ponteiro para o primeiro peao
        Peca** criarPeoes(CorPeca corCriada);

        //Cria as 8 pecas especiais (nao peoes) (padrao criarPeoes)
        Peca** criarPecasEspeciais(CorPeca corCriada);

        //Cria um novo jogador a partir do seu nome e cor
        void criarJogador(Jogador* jogador, Nome nomeJogador, CorPeca corJogador);

        //Funcao que transforma uma posicao relativa a tela 2D para o plano cartesiano
        Posicao converterPosicaoTelaParaCartesiano(Posicao posicaoTela, CorPeca corTurno);

        Posicao converterPosicaoCartesianoParaTela(Posicao posicaoCartesiano, CorPeca corTurno);

        Lista** retornarTodosAsPecasDeOutraCor(CorPeca corJogando, Tabuleiro tabuleiro);

        void acharPecaNoTabuleiro(Posicao* posicao, Tabuleiro tabuleiro, CorPeca corPeca, TipoPeca tipoPeca);

        bool xequemate(Jogo jogo);

        bool xequeAgora(Jogo jogo);

        //Funcao que inverte o tabuleiro para o proximo jogador
        void inverterTabuleiro(Tabuleiro tabuleiro);

        void inverterColunasTabuleiro(Tabuleiro tabuleiro);

        void inverterLinhasTabuleiro(Tabuleiro tabuleiro);

        void proximoTurno(Jogo *jogo);
    //endregion

    //FUNCOES DAS PECAS
        //mover peca para nova posicao
        void moverPeca(CasaTabuleiro pecaMovida, Tabuleiro tabuleiro, CasaTabuleiro novaPosicao);

        //funcao que retorna todas os movimentos possiveis
        ListaCasaTabuleiro** movimentosPossiveis(CasaTabuleiro peca, Jogo jogo);

        //funcao dos movimentos do peao
        ListaCasaTabuleiro** movimentosPossiveisPeao(CasaTabuleiro peca, Tabuleiro tabuleiro);

        //funcao que retorna os movimentos relevantes ao peao
        CasaTabuleiro** casasRelevantesAoPeao(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual);

        //funcao dos movimentos do cavalo
        ListaCasaTabuleiro** movimentosPossiveisCavalo(CasaTabuleiro peca, Tabuleiro tabuleiro);

        //funcao que retorna os movimentos relevantes ao cavalo
        CasaTabuleiro** casasRelevantesAoCavalo(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual);

        //funcao dos movimentos da torre
        ListaCasaTabuleiro** movimentosPossiveisTorre(CasaTabuleiro peca, Tabuleiro tabuleiro);

        //funcao que retorna os movimentos relevantes a torre
        CasaTabuleiro** casasRelevantesATorre(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual);

        //funcao dos movimentos do bispo
        ListaCasaTabuleiro** movimentosPossiveisBispo(CasaTabuleiro peca, Tabuleiro tabuleiro);

        //funcao que retorna os movimentos relevantes ao bispo
        CasaTabuleiro** casasRelevantesAoBispo(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual);

        //funcao dos movimentos da rainha
        ListaCasaTabuleiro** movimentosPossiveisRainha(CasaTabuleiro peca, Tabuleiro tabuleiro);

        //funcao que retorna os movimentos relevantes a rainha
        CasaTabuleiro** casasRelevantesARainha(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual);

        //funcao dos movimentos do rei
        ListaCasaTabuleiro** movimentosPossiveisRei(CasaTabuleiro peca, Tabuleiro tabuleiro);

        //funcao que retorna os movimentos relevantes ao rei
        CasaTabuleiro** casasRelevantesAoRei(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual);

        //função que verifica os movimentos que deixariam o rei em cheque
        void filtrarCasasPossiveisAoRei(CasaTabuleiro** casasPossiveis, Tabuleiro tabuleiro, Turno turnoAtual);

        bool movimentoExisteEmTalPosicao(int linha, int coluna, ListaCasaTabuleiro* lista); 
    //endregion
#endif
