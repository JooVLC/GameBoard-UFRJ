#include "../headers/typesXadrez.h"
#include "../headers/functionsXadrez.h"
#include "../headers/listXadrez.h"

/*Peao não pode pular pecas
Peao pode se mover duas casas no inicio do jogo (não necessita verificação pois o turno já verificas as condições)
Peao pode se mover para comer um peao na diagonal direita
Peao pode se mover para comer um peao na diagonal esquerda
Peao pode se mover para frente (ate o final do board)*/
ListaCasaTabuleiro* movimentosPossiveisPeao(CasaTabuleiro peca, Tabuleiro tabuleiro, Turno turnoAtual) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    //CASAS RELEVANTES AO PEAO (manual pela dificuldade do peão e pequena quantidade de movimentos)
    CasaTabuleiro **casasRelevantes = casasRelevantesAoPeao(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    CasaTabuleiro *casaAcimaDoPeaoLinha = casasRelevantes[0];
    CasaTabuleiro *casaAcimaDoPeaoLinhaDireita = casasRelevantes[1];
    CasaTabuleiro *casaAcimaDoPeaoLinhaEsquerda = casasRelevantes[2];

    ListaCasaTabuleiro* movimentosPossiveis = criarListaCasasTabuleiro();

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
    return movimentosPossiveis;
}

CasaTabuleiro** casasRelevantesAoPeao(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    CasaTabuleiro *casaAcimaDoPeaoLinha = pecaLinhaAtual + 1 < QTD_CASAS_POR_LINHA ? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual] : NULL;
    CasaTabuleiro *casaAcimaDoPeaoLinhaDireita = pecaLinhaAtual + 1 < QTD_CASAS_POR_LINHA && pecaColunaAtual + 1 < QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual+1] : NULL;
    CasaTabuleiro *casaAcimaDoPeaoLinhaEsquerda = pecaLinhaAtual + 1 < QTD_CASAS_POR_LINHA && pecaColunaAtual >= 0 ? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual-1] : NULL;

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
ListaCasaTabuleiro* movimentosPossiveisCavalo(CasaTabuleiro peca, Tabuleiro tabuleiro) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    CasaTabuleiro **casasRelevantes = casasRelevantesAoCavalo(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    ListaCasaTabuleiro* movimentosPossiveis = criarListaCasasTabuleiro();

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
    return movimentosPossiveis;
}

CasaTabuleiro** casasRelevantesAoCavalo(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    CasaTabuleiro *casaL_SuperiorDireita = pecaLinhaAtual + 2 < QTD_CASAS_POR_LINHA && pecaColunaAtual + 1 < QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual+2][pecaColunaAtual+1] : NULL;
    CasaTabuleiro *casaL_SuperiorEsquerda = pecaLinhaAtual + 2 < QTD_CASAS_POR_LINHA && pecaColunaAtual - 1 >= 0 ? &tabuleiro[pecaLinhaAtual+2][pecaColunaAtual-1] : NULL;
    CasaTabuleiro *casaL_EsquerdaCima = pecaLinhaAtual + 1 < QTD_CASAS_POR_LINHA && pecaColunaAtual - 2 >= 0 ? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual-2] : NULL;
    CasaTabuleiro *casaL_EsquerdaBaixo = pecaLinhaAtual - 1 >= 0 && pecaColunaAtual - 2 >= 0 ? &tabuleiro[pecaLinhaAtual-1][pecaColunaAtual-2] : NULL;
    CasaTabuleiro *casaL_DireitaCima = pecaLinhaAtual + 1 < QTD_CASAS_POR_LINHA && pecaColunaAtual + 2 < QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual+2] : NULL;
    CasaTabuleiro *casaL_DireitaBaixo = pecaLinhaAtual - 1 >= 0 && pecaColunaAtual + 2 < QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual-1][pecaColunaAtual+2] : NULL;
    CasaTabuleiro *casaL_InferiorDireita = pecaLinhaAtual - 2 >= 0 && pecaColunaAtual + 1 < QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual-2][pecaColunaAtual+1] : NULL;
    CasaTabuleiro *casaL_InferiorEsquerda = pecaLinhaAtual - 2 >= 0 && pecaColunaAtual - 1 >= 0 ? &tabuleiro[pecaLinhaAtual-2][pecaColunaAtual-1] : NULL;

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
ListaCasaTabuleiro* movimentosPossiveisTorre(CasaTabuleiro peca, Tabuleiro tabuleiro) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    CasaTabuleiro **casasRelevantes = casasRelevantesATorre(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    ListaCasaTabuleiro* movimentosPossiveis = criarListaCasasTabuleiro();

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_TORRE; i++)
    {
        if(casasRelevantes[i] != NULL)
            adicionarNovoMovimento(movimentosPossiveis, *casasRelevantes[i]);
    }

    free(casasRelevantes);
    return movimentosPossiveis;
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
ListaCasaTabuleiro* movimentosPossiveisBispo(CasaTabuleiro peca, Tabuleiro tabuleiro) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    CasaTabuleiro **casasRelevantes = casasRelevantesAoBispo(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    ListaCasaTabuleiro* movimentosPossiveis = criarListaCasasTabuleiro();

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_BISPO; i++)
    {
        if(casasRelevantes[i] != NULL)
            adicionarNovoMovimento(movimentosPossiveis, *casasRelevantes[i]);
    }

    free(casasRelevantes);
    return movimentosPossiveis;
}

CasaTabuleiro** casasRelevantesAoBispo(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    int index = 0;
    bool encontrouPeca;
    CasaTabuleiro** casasRelevantes = malloc(sizeof(CasaTabuleiro*) * MOVIMENTOS_POSSIVEIS_BISPO);

    //Movimentos na diagonal superior esquerda (da posição do bispo indo para cima):
    encontrouPeca = false;
    for(int i = pecaLinhaAtual + 1, j = pecaColunaAtual - 1; i < QTD_CASAS_POR_LINHA && j >= 0; i++, j--, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = &tabuleiro[i][j];
        
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

    //Movimentos na diagonal superior direita (da posição do bispo indo para cima):
    encontrouPeca = false;
    for(int i = pecaLinhaAtual + 1, j = pecaColunaAtual + 1; i < QTD_CASAS_POR_LINHA && j < QTD_CASAS_POR_COLUNA; i++, j++, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = &tabuleiro[i][j];
        
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

    //Movimentos na diagonal inferior esquerda (da posição do bispo indo para baixo):
    encontrouPeca = false;
    for(int i = pecaLinhaAtual - 1, j = pecaColunaAtual - 1; i >= 0 && j >= 0; i--, j--, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = &tabuleiro[i][j];
        
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

    //Movimentos na diagonal inferior direita (da posição do bispo indo para baixo):
    encontrouPeca = false;
    for(int i = pecaLinhaAtual - 1, j = pecaColunaAtual + 1; i >= 0 && j < QTD_CASAS_POR_COLUNA; i--, j++, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = &tabuleiro[i][j];
        
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


    return casasRelevantes;
}


/*Rainha não pode pular peças
Rainha se move em qualquer sentido (diagonal, horizontal e vertical) como se fosse um Bispo ou Torre
Rainha não pode ultrapassar o board
*/
ListaCasaTabuleiro* movimentosPossiveisRainha(CasaTabuleiro peca, Tabuleiro tabuleiro) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    CasaTabuleiro **casasRelevantes = casasRelevantesARainha(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    ListaCasaTabuleiro* movimentosPossiveis = criarListaCasasTabuleiro();

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_RAINHA; i++)
    {
        if(casasRelevantes[i] != NULL)
            adicionarNovoMovimento(movimentosPossiveis, *casasRelevantes[i]);
    }

    free(casasRelevantes);
    return movimentosPossiveis;
}

CasaTabuleiro** casasRelevantesARainha(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    CasaTabuleiro** casasRelevantes = malloc(sizeof(CasaTabuleiro*) * MOVIMENTOS_POSSIVEIS_RAINHA);
    CasaTabuleiro** movimentosRelevantesBispo = casasRelevantesAoBispo(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    CasaTabuleiro** movimentosRelevantesTorre = casasRelevantesATorre(tabuleiro, pecaLinhaAtual, pecaColunaAtual);

    //MOVIMENTOS_POSSIVEIS_RAINHA = MOVIMENTOS_POSSIVEIS_BISPO + MOVIMENTOS_POSSIVEIS_TORRE
    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_BISPO; i++)
        casasRelevantes[i] = movimentosRelevantesBispo[i];

    for(int i = MOVIMENTOS_POSSIVEIS_BISPO; i < MOVIMENTOS_POSSIVEIS_RAINHA; i++)
        casasRelevantes[i] = movimentosRelevantesTorre[i - MOVIMENTOS_POSSIVEIS_BISPO];

    free(movimentosRelevantesBispo);
    free(movimentosRelevantesTorre);

    return casasRelevantes;
}


/*Rei não pode pular peças
Rei se move como a Rainha, mas sempre limitado por uma casa
Rei não pode ultrapassar o board
Rei não pode se colocar em cheque
*/
ListaCasaTabuleiro* movimentosPossiveisRei(CasaTabuleiro peca, Tabuleiro tabuleiro) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    CasaTabuleiro **casasRelevantes = casasRelevantesAoRei(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    ListaCasaTabuleiro *movimentosPossiveis = criarListaCasasTabuleiro();

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_REI; i++)
    {
        if(casasRelevantes[i] != NULL)
        {
            bool existePecaComMesmaCor = casasRelevantes[i]->peca != NULL && casasRelevantes[i]->peca->cor == peca.peca->cor;
            if(!existePecaComMesmaCor)
                adicionarNovoMovimento(movimentosPossiveis, *casasRelevantes[i]);
        }
    }

    free(casasRelevantes);
    return movimentosPossiveis;
}

CasaTabuleiro** casasRelevantesAoRei(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    CasaTabuleiro *casa_SuperiorDireita = pecaLinhaAtual + 1 < QTD_CASAS_POR_LINHA && pecaColunaAtual + 1 < QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual+1] : NULL;
    CasaTabuleiro *casa_SuperiorEsquerda = pecaLinhaAtual + 1 < QTD_CASAS_POR_COLUNA && pecaColunaAtual - 1 >= 0 ? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual-1] : NULL;
    CasaTabuleiro *casa_Superior = pecaLinhaAtual + 1 < QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual+1][pecaColunaAtual] : NULL;
    CasaTabuleiro *casa_Esquerda = pecaColunaAtual - 1 >= 0 ? &tabuleiro[pecaLinhaAtual][pecaColunaAtual-1] : NULL;
    CasaTabuleiro *casa_InferiorDireita = pecaLinhaAtual - 1 >= 0 && pecaColunaAtual + 1 < QTD_CASAS_POR_COLUNA ? &tabuleiro[pecaLinhaAtual-1][pecaColunaAtual+1] : NULL;
    CasaTabuleiro *casa_InferiorEsquerda = pecaLinhaAtual - 1 >= 0 && pecaColunaAtual - 1 >= 0 ? &tabuleiro[pecaLinhaAtual-1][pecaColunaAtual-1] : NULL;
    CasaTabuleiro *casa_Inferior = pecaLinhaAtual - 1 >= 0 ? &tabuleiro[pecaLinhaAtual-1][pecaColunaAtual] : NULL;
    CasaTabuleiro *casa_Direita = pecaColunaAtual - 1 >= 0 ? &tabuleiro[pecaLinhaAtual][pecaColunaAtual-1] : NULL;
    CasaTabuleiro** casasRelevantes = malloc(sizeof(CasaTabuleiro*) * MOVIMENTOS_POSSIVEIS_REI);

    casasRelevantes[0] = casa_SuperiorDireita;
    casasRelevantes[1] = casa_SuperiorEsquerda;
    casasRelevantes[2] = casa_Superior;
    casasRelevantes[3] = casa_Esquerda;
    casasRelevantes[4] = casa_InferiorDireita;
    casasRelevantes[5] = casa_InferiorEsquerda;
    casasRelevantes[6] = casa_Inferior;
    casasRelevantes[7] = casa_Direita;

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

ListaCasaTabuleiro* movimentosPossiveis(CasaTabuleiro peca, Jogo jogo) {
    ListaCasaTabuleiro *movimentosPossiveisPeca;

    if(peca.peca == NULL)
        return NULL;

    switch (peca.peca->tipo)
    {
        case PEAO:
            movimentosPossiveisPeca = movimentosPossiveisPeao(peca, jogo.tabuleiro, jogo.turno);
            break;
        case CAVALO:
            movimentosPossiveisPeca = movimentosPossiveisCavalo(peca, jogo.tabuleiro);
            break;
        case TORRE:
            movimentosPossiveisPeca = movimentosPossiveisTorre(peca, jogo.tabuleiro);
            break;
        case BISPO:
            movimentosPossiveisPeca = movimentosPossiveisBispo(peca, jogo.tabuleiro);
            break;
        case RAINHA:
            movimentosPossiveisPeca = movimentosPossiveisRainha(peca, jogo.tabuleiro);
            break;
        case REI:
            movimentosPossiveisPeca = movimentosPossiveisRei(peca, jogo.tabuleiro);
            //filtrarCasasPossiveisAoRei(&movimentosPossiveis, jogo.tabuleiro, jogo.turno);
            break;
    }

    return movimentosPossiveisPeca;
}

/*void filtrarCasasPossiveisAoRei(CasaTabuleiro** casasPossiveis, Tabuleiro tabuleiro, Turno turnoAtual) {

}*/
