#include "../headers/typesXadrez.h"
#include "../headers/functionsXadrez.h"
#include "../headers/listXadrez.h"

/*Peao não pode pular pecas
Peao pode se mover duas casas no inicio do jogo (não necessita verificação pois o turno já verificas as condições)
Peao pode se mover para comer um peao na diagonal direita
Peao pode se mover para comer um peao na diagonal esquerda
Peao pode se mover para frente (ate o final do board)*/
CasaTabuleiro* movimentosPossiveisPeao(CasaTabuleiro peca, Tabuleiro tabuleiro, Turno turnoAtual) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    //CASAS RELEVANTES AO PEAO (manual pela dificuldade do peão e pequena quantidade de movimentos)
    CasaTabuleiro **casasRelevantes = casasRelevantesAoPeao(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    CasaTabuleiro *casaAcimaDoPeaoLinha = casasRelevantes[0];
    CasaTabuleiro *casaAcimaDoPeaoLinhaDireita = casasRelevantes[1];
    CasaTabuleiro *casaAcimaDoPeaoLinhaEsquerda = casasRelevantes[2];

    ListaCasaTabuleiro movimentosPossiveis = criarListaCasasTabuleiro();

    if( (turnoAtual == 1 && peca.peca->cor == BRANCO) || (turnoAtual == 2 && peca.peca->cor == PRETO) )
    {
        if(casaAcimaDoPeaoLinha != NULL && casaAcimaDoPeaoLinha->peca == NULL)
        {
            CasaTabuleiro movimentoPeaoDuasCasas = tabuleiro[pecaLinhaAtual+2][pecaColunaAtual];
            adicionarNovoMovimento(movimentosPossiveis, movimentoPeaoDuasCasas);
        }
    }

    if(casaAcimaDoPeaoLinhaDireita != NULL && casaAcimaDoPeaoLinhaDireita->peca != NULL && casaAcimaDoPeaoLinhaDireita->peca->cor != peca.peca->cor)
        adicionarNovoMovimento(movimentosPossiveis, *casaAcimaDoPeaoLinhaDireita);

    if(casaAcimaDoPeaoLinhaEsquerda != NULL && casaAcimaDoPeaoLinhaEsquerda->peca != NULL && casaAcimaDoPeaoLinhaEsquerda->peca->cor != peca.peca->cor)
        adicionarNovoMovimento(movimentosPossiveis, *casaAcimaDoPeaoLinhaEsquerda);

    if(casaAcimaDoPeaoLinha != NULL && casaAcimaDoPeaoLinha->peca == NULL)
        adicionarNovoMovimento(movimentosPossiveis, *casaAcimaDoPeaoLinha);
    
    free(casasRelevantes);
    return ListaParaArrayDeCasaTabuleiro(movimentosPossiveis);
}

CasaTabuleiro** casasRelevantesAoPeao(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    CasaTabuleiro *casaAcimaDoPeaoLinha = pecaLinhaAtual + 1 < QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual] : NULL;
    CasaTabuleiro *casaAcimaDoPeaoLinhaDireita = pecaColunaAtual + 1 < QTD_CASAS_POR_LINHA && pecaLinhaAtual + 1 < QTD_CASAS_POR_COLUNA? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual+1] : NULL;
    CasaTabuleiro *casaAcimaDoPeaoLinhaEsquerda = pecaColunaAtual > 0 && pecaLinhaAtual + 1 < QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual-1] : NULL;

    CasaTabuleiro** casasRelevantes = malloc(sizeof(CasaTabuleiro*) * MOVIMENTOS_POSSIVEIS_PEAO);
    casasRelevantes[0] = casaAcimaDoPeaoLinha;
    casasRelevantes[1] = casaAcimaDoPeaoLinhaDireita;
    casasRelevantes[2] = casaAcimaDoPeaoLinhaEsquerda;

    return casasRelevantes;
}

/*Cavalo pode pular peças
Cavalo pode se mover em L para qualquer casa proxima sem peça da mesma cor
L = duas casas (linhas ou coluna) e depos uma casas (coluna ou linha)
Cavalo não pode ultrapassar o board*/
CasaTabuleiro* movimentosPossiveisCavalo(CasaTabuleiro peca, Tabuleiro tabuleiro, Turno turnoAtual) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    CasaTabuleiro **casasRelevantes = casasRelevantesAoCavalo(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    ListaCasaTabuleiro movimentosPossiveis = criarListaCasasTabuleiro();

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_CAVALO; i++)
    {
        if(casasRelevantes[i] != NULL)
        {
            bool existePecaComMesmaCor = casasRelevantes[i]->peca != NULL && casasRelevantes[i]->peca->cor == peca.peca->cor;
            if(!existePecaComMesmaCor)
                adicionarNovoMovimento(movimentosPossiveis, *casasRelevantes[i]);
        }
    }

    free(casasRelevantes);
    return ListaParaArrayDeCasaTabuleiro(movimentosPossiveis);
}

CasaTabuleiro** casasRelevantesAoCavalo(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    CasaTabuleiro *casaL_SuperiorDireita = pecaLinhaAtual + 2 < QTD_CASAS_POR_COLUNA && pecaColunaAtual + 1 < QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual+2][pecaColunaAtual+1] : NULL;
    CasaTabuleiro *casaL_SuperiorEsquerda = pecaLinhaAtual + 2 < QTD_CASAS_POR_COLUNA && pecaColunaAtual - 1 > 0 ? &tabuleiro[pecaLinhaAtual+2][pecaColunaAtual-1] : NULL;
    CasaTabuleiro *casaL_EsquerdaCima = pecaLinhaAtual + 1 < QTD_CASAS_POR_COLUNA && pecaColunaAtual - 2 > 0 ? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual-2] : NULL;
    CasaTabuleiro *casaL_EsquerdaBaixo = pecaLinhaAtual - 1 > 0 && pecaColunaAtual - 2 > 0 ? &tabuleiro[pecaLinhaAtual-1][pecaColunaAtual-2] : NULL;
    CasaTabuleiro *casaL_DireitaCima = pecaLinhaAtual + 1 < QTD_CASAS_POR_COLUNA && pecaColunaAtual + 2 < QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual+2] : NULL;
    CasaTabuleiro *casaL_DireitaBaixo = pecaLinhaAtual - 1 > 0 && pecaColunaAtual + 2 < QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual-1][pecaColunaAtual+2] : NULL;
    CasaTabuleiro *casaL_InferiorDireita = pecaLinhaAtual - 2 > 0 && pecaColunaAtual + 1 < QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual-2][pecaColunaAtual+1] : NULL;
    CasaTabuleiro *casaL_InferiorEsquerda = pecaLinhaAtual - 2 > 0 && pecaColunaAtual - 1 > 0 ? &tabuleiro[pecaLinhaAtual-2][pecaColunaAtual-1] : NULL;

    CasaTabuleiro** casasRelevantes = malloc(sizeof(CasaTabuleiro*) * MOVIMENTOS_POSSIVEIS_CAVALO);
    casasRelevantes[0] = casaL_SuperiorDireita;
    casasRelevantes[1] = casaL_SuperiorEsquerda;
    casasRelevantes[2] = casaL_EsquerdaCima;
    casasRelevantes[3] = casaL_EsquerdaBaixo;
    casasRelevantes[4] = casaL_DireitaCima;
    casasRelevantes[5] = casaL_DireitaBaixo;
    casasRelevantes[6] = casaL_InferiorDireita;
    casasRelevantes[7] = casaL_InferiorEsquerda;

    return casasRelevantes;
}

/*Torre não pode pular peças
Torre se move na horizontal e vertical para qualquer casa até atingir um alvo inimigo ou parar em uma peça amiga
Torre não pode ultrapassar o board
*/
CasaTabuleiro* movimentosPossiveisTorre(CasaTabuleiro peca, Tabuleiro tabuleiro, Turno turnoAtual) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    CasaTabuleiro **casasRelevantes = casasRelevantesAoCavalo(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    ListaCasaTabuleiro movimentosPossiveis = criarListaCasasTabuleiro();

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_TORRE; i++)
    {
        if(casasRelevantes[i] != NULL)
            adicionarNovoMovimento(movimentosPossiveis, *casasRelevantes[i]);
    }

    free(casasRelevantes);
    return ListaParaArrayDeCasaTabuleiro(movimentosPossiveis);
}

CasaTabuleiro** casasRelevantesATorre(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    int index = 0;
    bool encontrouPeca;
    CasaTabuleiro** casasRelevantes = malloc(sizeof(CasaTabuleiro*) * MOVIMENTOS_POSSIVEIS_TORRE);

    //Movimentos na horizontal (da posição da torre indo para a esquerda):
    encontrouPeca = false;
    for(int i = pecaColunaAtual - 1; i >= 0; i--, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = &tabuleiro[pecaLinhaAtual][i];
        
        if(encontrouPeca)
            casasRelevantes[index] = NULL;
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casaPossivelParaMoverTorre->peca != NULL)//Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor)
                casasRelevantes[index] = NULL;
        }
    }

    //Movimentos na horizontal (da posição da torre indo para a direita):
    encontrouPeca = false;
    for(int i = pecaColunaAtual + 1; i < QTD_CASAS_POR_COLUNA; i++, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = &tabuleiro[pecaLinhaAtual][i];
        
        if(encontrouPeca)
            casasRelevantes[index] = NULL;
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casaPossivelParaMoverTorre->peca != NULL) //Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor)
                casasRelevantes[index] = NULL;
        }
    }

    //Movimentos na vertical (da posição da torre indo para cima)
    encontrouPeca = false;
    for(int i = pecaLinhaAtual + 1; i < QTD_CASAS_POR_LINHA; i++, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = &tabuleiro[i][pecaLinhaAtual];
        
        if(encontrouPeca)
            casasRelevantes[index] = NULL;
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casaPossivelParaMoverTorre->peca != NULL) //Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor)
                casasRelevantes[index] = NULL;
        }
    }

    //Movimentos na vertical (da posição da torre indo para baixo)
    encontrouPeca = false;
    for(int i = pecaLinhaAtual - 1; i >= 0; i--, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = &tabuleiro[i][pecaLinhaAtual];
        
        if(encontrouPeca)
            casasRelevantes[index] = NULL;
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casaPossivelParaMoverTorre->peca != NULL) //Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor)
                casasRelevantes[index] = NULL;
        }
    }

    return casasRelevantes;
}

/*Bispo não pode pular peças
Bispo se move na diagonal de sua cor de origem para qualquer casa até atingir um alvo inimigo ou parar em uma peça amiga
Bispo não pode ultrapassar o board
*/
CasaTabuleiro* movimentosPossiveisBispo(CasaTabuleiro peca, Tabuleiro tabuleiro, Turno turnoAtual) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    CasaTabuleiro **casasRelevantes = casasRelevantesAoBispo(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    ListaCasaTabuleiro movimentosPossiveis = criarListaCasasTabuleiro();

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_BISPO; i++)
    {
        if(casasRelevantes[i] != NULL)
            adicionarNovoMovimento(movimentosPossiveis, *casasRelevantes[i]);
    }

    free(casasRelevantes);
    return ListaParaArrayDeCasaTabuleiro(movimentosPossiveis);
}

CasaTabuleiro** casasRelevantesAoBispo(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    int index = 0;
    bool encontrouPeca;
    CasaTabuleiro** casasRelevantes = malloc(sizeof(CasaTabuleiro*) * MOVIMENTOS_POSSIVEIS_BISPO);

    //Movimentos na horizontal (da posição da torre indo para a esquerda):
    encontrouPeca = false;
    for(int i = pecaColunaAtual - 1; i >= 0; i--, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = &tabuleiro[pecaLinhaAtual][i];
        
        if(encontrouPeca)
            casasRelevantes[index] = NULL;
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casaPossivelParaMoverTorre->peca != NULL)//Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor)
                casasRelevantes[index] = NULL;
        }
    }

    //Movimentos na horizontal (da posição da torre indo para a direita):
    encontrouPeca = false;
    for(int i = pecaColunaAtual + 1; i < QTD_CASAS_POR_COLUNA; i++, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = &tabuleiro[pecaLinhaAtual][i];
        
        if(encontrouPeca)
            casasRelevantes[index] = NULL;
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casaPossivelParaMoverTorre->peca != NULL) //Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor)
                casasRelevantes[index] = NULL;
        }
    }

    //Movimentos na vertical (da posição da torre indo para cima)
    encontrouPeca = false;
    for(int i = pecaLinhaAtual + 1; i < QTD_CASAS_POR_LINHA; i++, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = &tabuleiro[i][pecaLinhaAtual];
        
        if(encontrouPeca)
            casasRelevantes[index] = NULL;
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casaPossivelParaMoverTorre->peca != NULL) //Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor)
                casasRelevantes[index] = NULL;
        }
    }

    //Movimentos na vertical (da posição da torre indo para baixo)
    encontrouPeca = false;
    for(int i = pecaLinhaAtual - 1; i >= 0; i--, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = &tabuleiro[i][pecaLinhaAtual];
        
        if(encontrouPeca)
            casasRelevantes[index] = NULL;
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casaPossivelParaMoverTorre->peca != NULL) //Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor)
                casasRelevantes[index] = NULL;
        }
    }

    return casasRelevantes;
}

void moverPeca(CasaTabuleiro pecaMovida, Tabuleiro tabuleiro, CasaTabuleiro novaPosicao) {
    if(pecaMovida.peca->cor == novaPosicao.peca->cor)
        return;

    tabuleiro[novaPosicao.peca->posicao.linha][novaPosicao.peca->posicao.coluna].peca = pecaMovida.peca;
    tabuleiro[pecaMovida.peca->posicao.linha][pecaMovida.peca->posicao.coluna].peca = NULL;
    pecaMovida.peca->posicao = novaPosicao.peca->posicao;
    free(novaPosicao.peca); //talvez apague dps (depende de como Peca *peca é criada)
}