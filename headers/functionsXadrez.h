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
        Jogo inicializarJogo(Nome nomeJogadorBranco, Nome nomeJogadorPreto);

        //Cria o tabuleiro e inicializa ele
        void inicializarTabuleiro(Tabuleiro novoTabuleiro);

        //Cria as pecas e coloca elas nas posições padrões do xadrez
        void inicializarPecas(Tabuleiro novoTabuleiro);

        //Cria 8 peoes da cor desejada e retorna um ponteiro para o primeiro peao
        Peca* criarPeoes(CorPeca corCriada);

        //Cria as 8 pecas especiais (nao peoes) (padrao criarPeoes)
        Peca* criarPecasEspeciais(CorPeca corCriada);

        //Cria um novo jogador a partir do seu nome e cor
        Jogador criarJogador(Nome nomeJogador, CorPeca corJogador);

        //Testa se houve xequemate, e caso houver, corPeca recebe a cor de quem
        //esta recebendo o xeque, caso não, retorna NULL
        bool xequeMate(Tabuleiro tabuleiro, CorPeca *corRecebendoCheque);

        //Verifica se uma peca esta em cheque em determinado tabuleiro
        bool pecaEstaEmXeque(CasaTabuleiro pecaTestada, Tabuleiro tabuleiro);

        //Verifica se a peca esta impedindo um xequemate
        bool pecaImpedindoXequeMate(CasaTabuleiro pecaTestada, Tabuleiro tabuleiro);

        //Funcao que transforma uma posicao relativa a tela 2D para o plano cartesiano
        Posicao converterPosicaoTelaParaCartesiano(Posicao posicaoTela);

        //Funcao para desalocar jogo da heap
        void terminarJogo(Jogo jogo);

        void proximoTurno(Jogo *jogo);
    //endregion

    //FUNCOES DAS PECAS
        //mover peca para nova posicao
        void moverPeca(CasaTabuleiro pecaMovida, Tabuleiro tabuleiro, CasaTabuleiro novaPosicao);

        //funcao que retorna todas os movimentos possiveis
        ListaCasaTabuleiro* movimentosPossiveis(CasaTabuleiro peca, Jogo jogo);

        //funcao dos movimentos do peao
        ListaCasaTabuleiro* movimentosPossiveisPeao(CasaTabuleiro peca, Tabuleiro tabuleiro, Turno turnoAtual);

        //funcao que retorna os movimentos relevantes ao peao
        CasaTabuleiro** casasRelevantesAoPeao(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual);

        //funcao dos movimentos do cavalo
        ListaCasaTabuleiro* movimentosPossiveisCavalo(CasaTabuleiro peca, Tabuleiro tabuleiro);

        //funcao que retorna os movimentos relevantes ao cavalo
        CasaTabuleiro** casasRelevantesAoCavalo(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual);

        //funcao dos movimentos da torre
        ListaCasaTabuleiro* movimentosPossiveisTorre(CasaTabuleiro peca, Tabuleiro tabuleiro);

        //funcao que retorna os movimentos relevantes a torre
        CasaTabuleiro** casasRelevantesATorre(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual);

        //funcao dos movimentos do bispo
        ListaCasaTabuleiro* movimentosPossiveisBispo(CasaTabuleiro peca, Tabuleiro tabuleiro);

        //funcao que retorna os movimentos relevantes ao bispo
        CasaTabuleiro** casasRelevantesAoBispo(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual);

        //funcao dos movimentos da rainha
        ListaCasaTabuleiro* movimentosPossiveisRainha(CasaTabuleiro peca, Tabuleiro tabuleiro);

        //funcao que retorna os movimentos relevantes a rainha
        CasaTabuleiro** casasRelevantesARainha(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual);

        //funcao dos movimentos do rei
        ListaCasaTabuleiro* movimentosPossiveisRei(CasaTabuleiro peca, Tabuleiro tabuleiro);

        //funcao que retorna os movimentos relevantes ao rei
        CasaTabuleiro** casasRelevantesAoRei(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual);

        //função que verifica os movimentos que deixariam o rei em cheque
        void filtrarCasasPossiveisAoRei(CasaTabuleiro** casasPossiveis, Tabuleiro tabuleiro, Turno turnoAtual);
    //endregion
#endif
