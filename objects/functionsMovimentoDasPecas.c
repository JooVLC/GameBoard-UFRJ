#include "../headers/includeLibrarys.h"
#include "../headers/typesXadrez.h"
#include "../headers/functionsXadrez.h"
#include "../headers/listXadrez.h"
#include "../headers/genericList.h"

/*Peao não pode pular pecas
Peao pode se mover duas casas no inicio do jogo (não necessita verificação pois o turno já verificas as condições)
Peao pode se mover para comer um peao na diagonal direita
Peao pode se mover para comer um peao na diagonal esquerda
Peao pode se mover para frente (ate o final do board)*/
ListaCasaTabuleiro** movimentosPossiveisPeao(CasaTabuleiro peca, Tabuleiro tabuleiro) {
    Coordenada pecaLinhaAtual = peca.localizacao.linha;
    Coordenada pecaColunaAtual = peca.localizacao.coluna;

    //CASAS RELEVANTES AO PEAO (manual pela dificuldade do peão e pequena quantidade de movimentos)
    CasaTabuleiro **casasRelevantes = casasRelevantesAoPeao(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    CasaTabuleiro *casaAcimaDoPeaoLinha = casasRelevantes[0];
    CasaTabuleiro *casaAcimaDoPeaoLinhaDireita = casasRelevantes[1];
    CasaTabuleiro *casaAcimaDoPeaoLinhaEsquerda = casasRelevantes[2];

    ListaCasaTabuleiro** movimentosPossiveis = malloc(sizeof *movimentosPossiveis);
    criarLista(movimentosPossiveis, sizeof(CasaTabuleiro));

    if(peca.localizacao.linha == 1)
    {
        if(casaAcimaDoPeaoLinha != NULL && casaAcimaDoPeaoLinha->peca == NULL)
        {
            CasaTabuleiro *movimentoPeaoDuasCasas = malloc(sizeof *movimentoPeaoDuasCasas);
            *movimentoPeaoDuasCasas = tabuleiro[pecaLinhaAtual+2][pecaColunaAtual];
            adicionarItemAoFinalDaLista(*movimentosPossiveis, movimentoPeaoDuasCasas); //erro aqui
        }
    }

    if(casaAcimaDoPeaoLinhaDireita != NULL && casaAcimaDoPeaoLinhaDireita->peca != NULL && casaAcimaDoPeaoLinhaDireita->peca->cor != peca.peca->cor)
        adicionarItemAoFinalDaLista(*movimentosPossiveis, casaAcimaDoPeaoLinhaDireita);

    if(casaAcimaDoPeaoLinhaEsquerda != NULL && casaAcimaDoPeaoLinhaEsquerda->peca != NULL && casaAcimaDoPeaoLinhaEsquerda->peca->cor != peca.peca->cor)
        adicionarItemAoFinalDaLista(*movimentosPossiveis, casaAcimaDoPeaoLinhaEsquerda);

    if(casaAcimaDoPeaoLinha != NULL && casaAcimaDoPeaoLinha->peca == NULL)
        adicionarItemAoFinalDaLista(*movimentosPossiveis, casaAcimaDoPeaoLinha);
    
    //printLista(*movimentosPossiveis, "peaoLista");
    free(casasRelevantes);
    return movimentosPossiveis;
}

CasaTabuleiro** casasRelevantesAoPeao(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    CasaTabuleiro *casaAcimaDoPeaoLinha = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casaAcimaDoPeaoLinhaDireita = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casaAcimaDoPeaoLinhaEsquerda = malloc(sizeof(CasaTabuleiro));;
    if(pecaLinhaAtual + 1 < QTD_CASAS_POR_LINHA) {
        *casaAcimaDoPeaoLinha = tabuleiro[pecaLinhaAtual+1][pecaColunaAtual];
    }
    else {
        free(casaAcimaDoPeaoLinha);
        casaAcimaDoPeaoLinha = NULL;
    }

    if(pecaLinhaAtual + 1 < QTD_CASAS_POR_LINHA && pecaColunaAtual + 1 < QTD_CASAS_POR_COLUNA) {
        *casaAcimaDoPeaoLinhaDireita = tabuleiro[pecaLinhaAtual+1][pecaColunaAtual+1];
    }
    else {
        free(casaAcimaDoPeaoLinhaDireita);
        casaAcimaDoPeaoLinhaDireita = NULL;
    }

    if((pecaLinhaAtual + 1) < QTD_CASAS_POR_LINHA && (pecaColunaAtual - 1) >= 0) {
        *casaAcimaDoPeaoLinhaEsquerda = tabuleiro[pecaLinhaAtual+1][pecaColunaAtual-1];
    }
    else {
        free(casaAcimaDoPeaoLinhaEsquerda);
        casaAcimaDoPeaoLinhaEsquerda = NULL;
    }

    CasaTabuleiro** casasRelevantes = malloc(sizeof(CasaTabuleiro*) * MOVIMENTOS_POSSIVEIS_PEAO);
    casasRelevantes[0] = casaAcimaDoPeaoLinha;
    casasRelevantes[1] = casaAcimaDoPeaoLinhaDireita;
    casasRelevantes[2] = casaAcimaDoPeaoLinhaEsquerda;

    return casasRelevantes;
}


//Cavalo pode pular peças
//Cavalo pode se mover em L para qualquer casa proxima sem peça da mesma cor
//L = duas casas (linhas ou coluna) e depos uma casas (coluna ou linha)
//Cavalo não pode ultrapassar o board
ListaCasaTabuleiro** movimentosPossiveisCavalo(CasaTabuleiro peca, Tabuleiro tabuleiro) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    CasaTabuleiro **casasRelevantes = casasRelevantesAoCavalo(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    ListaCasaTabuleiro** movimentosPossiveis = malloc(sizeof(ListaCasaTabuleiro*));
    criarLista(movimentosPossiveis, sizeof(CasaTabuleiro));

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_CAVALO; i++)
    {
        if(casasRelevantes[i] != NULL)
        {
            bool existePecaComMesmaCor = casasRelevantes[i]->peca != NULL && casasRelevantes[i]->peca->cor == peca.peca->cor;
            if(!existePecaComMesmaCor)
                adicionarItemAoFinalDaLista(*movimentosPossiveis, casasRelevantes[i]);
        }
    }

    //for(int i = 0; i < MOVIMENTOS_POSSIVEIS_CAVALO; i++)
        //free(casasRelevantes[i]);
    free(casasRelevantes);
    return movimentosPossiveis;
}

CasaTabuleiro** casasRelevantesAoCavalo(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    CasaTabuleiro *casaL_SuperiorDireita = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casaL_SuperiorEsquerda = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casaL_EsquerdaCima = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casaL_EsquerdaBaixo = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casaL_DireitaCima = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casaL_DireitaBaixo = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casaL_InferiorDireita = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casaL_InferiorEsquerda = malloc(sizeof(CasaTabuleiro));

    CasaTabuleiro casaVazia;
    Posicao posNegativa = { -1, -1 };
    casaVazia.localizacao = posNegativa;

    *casaL_SuperiorDireita = pecaLinhaAtual + 2 < QTD_CASAS_POR_LINHA && pecaColunaAtual + 1 < QTD_CASAS_POR_COLUNA ? tabuleiro[pecaLinhaAtual+2][pecaColunaAtual+1] : casaVazia;
    *casaL_SuperiorEsquerda = pecaLinhaAtual + 2 < QTD_CASAS_POR_LINHA && pecaColunaAtual - 1 >= 0 ? tabuleiro[pecaLinhaAtual+2][pecaColunaAtual-1] : casaVazia;
    *casaL_EsquerdaCima = pecaLinhaAtual + 1 < QTD_CASAS_POR_LINHA && pecaColunaAtual - 2 >= 0 ? tabuleiro[pecaLinhaAtual+1][pecaColunaAtual-2] : casaVazia;
    *casaL_EsquerdaBaixo = pecaLinhaAtual - 1 >= 0 && pecaColunaAtual - 2 >= 0 ? tabuleiro[pecaLinhaAtual-1][pecaColunaAtual-2] : casaVazia;
    *casaL_DireitaCima = pecaLinhaAtual + 1 < QTD_CASAS_POR_LINHA && pecaColunaAtual + 2 < QTD_CASAS_POR_COLUNA ? tabuleiro[pecaLinhaAtual+1][pecaColunaAtual+2] : casaVazia;
    *casaL_DireitaBaixo = pecaLinhaAtual - 1 >= 0 && pecaColunaAtual + 2 < QTD_CASAS_POR_COLUNA ? tabuleiro[pecaLinhaAtual-1][pecaColunaAtual+2] : casaVazia;
    *casaL_InferiorDireita = pecaLinhaAtual - 2 >= 0 && pecaColunaAtual + 1 < QTD_CASAS_POR_COLUNA ? tabuleiro[pecaLinhaAtual-2][pecaColunaAtual+1] : casaVazia;
    *casaL_InferiorEsquerda = pecaLinhaAtual - 2 >= 0 && pecaColunaAtual - 1 >= 0 ? tabuleiro[pecaLinhaAtual-2][pecaColunaAtual-1] : casaVazia;

    CasaTabuleiro** casasRelevantes = malloc(sizeof(CasaTabuleiro*) * MOVIMENTOS_POSSIVEIS_CAVALO);
    casasRelevantes[0] = casaL_SuperiorDireita;
    casasRelevantes[1] = casaL_SuperiorEsquerda;
    casasRelevantes[2] = casaL_EsquerdaCima;
    casasRelevantes[3] = casaL_EsquerdaBaixo;
    casasRelevantes[4] = casaL_DireitaCima;
    casasRelevantes[5] = casaL_DireitaBaixo;
    casasRelevantes[6] = casaL_InferiorDireita;
    casasRelevantes[7] = casaL_InferiorEsquerda;

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_CAVALO; i++) {
        CasaTabuleiro* casaAtualCavalo = casasRelevantes[i];
        if(casaAtualCavalo->localizacao.linha == -1) {
            //free(casaAtualCavalo);
            casasRelevantes[i] = NULL;
        }
    }
    //printArray(casasRelevantes, "casas relevantes cavalo", MOVIMENTOS_POSSIVEIS_REI);
    return casasRelevantes;
}


//Torre não pode pular peças
//Torre se move na horizontal e vertical para qualquer casa até atingir um alvo inimigo ou parar em uma peça amiga
//Torre não pode ultrapassar o board
ListaCasaTabuleiro** movimentosPossiveisTorre(CasaTabuleiro peca, Tabuleiro tabuleiro) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    CasaTabuleiro **casasRelevantes = casasRelevantesATorre(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    ListaCasaTabuleiro** movimentosPossiveis = malloc(sizeof(ListaCasaTabuleiro*));
    criarLista(movimentosPossiveis, sizeof(CasaTabuleiro));

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_TORRE; i++)
    {
        if(casasRelevantes[i] != NULL) { 
            //CasaTabuleiro* movimentoNovo = malloc(sizeof *movimentoNovo);
            //*movimentoNovo = *casasRelevantes[i];
            adicionarItemAoFinalDaLista(*movimentosPossiveis, casasRelevantes[i]);
        }
    }

    free(casasRelevantes);
    return movimentosPossiveis;
}

CasaTabuleiro** casasRelevantesATorre(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    int index = 0;
    bool encontrouPeca;
    CasaTabuleiro** casasRelevantes = malloc(sizeof(CasaTabuleiro*) * MOVIMENTOS_POSSIVEIS_TORRE);

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_TORRE; i++)
        casasRelevantes[i] = NULL;

    //Movimentos na horizontal (da posição da torre indo para a esquerda):
    encontrouPeca = false;
    for(int i = pecaColunaAtual - 1; i >= 0; i--, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = malloc(sizeof *casaPossivelParaMoverTorre);
        *casaPossivelParaMoverTorre = tabuleiro[pecaLinhaAtual][i];
        
        if(encontrouPeca) {
            casasRelevantes[index] = NULL;
            //free(casaPossivelParaMoverTorre);
        }
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casasRelevantes[index] != NULL && casaPossivelParaMoverTorre->peca != NULL)//Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor) {
                casasRelevantes[index] = NULL;
                //free(casaPossivelParaMoverTorre);
            }
        }
    }

    //Movimentos na horizontal (da posição da torre indo para a direita):
    encontrouPeca = false;
    for(int i = pecaColunaAtual + 1; i < QTD_CASAS_POR_COLUNA; i++, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = malloc(sizeof *casaPossivelParaMoverTorre);
        *casaPossivelParaMoverTorre = tabuleiro[pecaLinhaAtual][i];
        
        if(encontrouPeca) {
            casasRelevantes[index] = NULL;
            //free(casaPossivelParaMoverTorre);
        }
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casasRelevantes[index] != NULL && casaPossivelParaMoverTorre->peca != NULL) //Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor) {
                casasRelevantes[index] = NULL;
                //free(casaPossivelParaMoverTorre);
            }
        }
    }

    //Movimentos na vertical (da posição da torre indo para cima)
    encontrouPeca = false;
    for(int i = pecaLinhaAtual + 1; i < QTD_CASAS_POR_LINHA; i++, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = malloc(sizeof *casaPossivelParaMoverTorre);
        *casaPossivelParaMoverTorre = tabuleiro[i][pecaColunaAtual];
        
        if(encontrouPeca) {
            casasRelevantes[index] = NULL;
            //free(casaPossivelParaMoverTorre);
        }
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casasRelevantes[index] != NULL && casaPossivelParaMoverTorre->peca != NULL) //Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor) {
                casasRelevantes[index] = NULL;
                //free(casaPossivelParaMoverTorre);
            }
        }
    }

    //Movimentos na vertical (da posição da torre indo para baixo)
    encontrouPeca = false;
    for(int i = pecaLinhaAtual - 1; i >= 0; i--, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = malloc(sizeof *casaPossivelParaMoverTorre);
        *casaPossivelParaMoverTorre = tabuleiro[i][pecaColunaAtual];
        
        if(encontrouPeca) {
            casasRelevantes[index] = NULL;
            //free(casaPossivelParaMoverTorre);
        }
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casasRelevantes[index] != NULL && casaPossivelParaMoverTorre->peca != NULL) //Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor) {
                casasRelevantes[index] = NULL;
                //free(casaPossivelParaMoverTorre);
            }
        }
    }

    return casasRelevantes;
}


//Bispo não pode pular peças
//Bispo se move na diagonal de sua cor de origem para qualquer casa até atingir um alvo inimigo ou parar em uma peça amiga
//Bispo não pode ultrapassar o board
ListaCasaTabuleiro** movimentosPossiveisBispo(CasaTabuleiro peca, Tabuleiro tabuleiro) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    CasaTabuleiro **casasRelevantes = casasRelevantesAoBispo(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    ListaCasaTabuleiro** movimentosPossiveis = malloc(sizeof(ListaCasaTabuleiro*));
    criarLista(movimentosPossiveis, sizeof(CasaTabuleiro));

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_BISPO; i++)
    {
        if(casasRelevantes[i] != NULL)
            adicionarItemAoFinalDaLista(*movimentosPossiveis, casasRelevantes[i]);
    }
    //printLista(*movimentosPossiveis, "peaoLista");

    //for(int i = 0; i < MOVIMENTOS_POSSIVEIS_BISPO; i++)
    //    free(casasRelevantes[i]);
    free(casasRelevantes);
    return movimentosPossiveis;
}

CasaTabuleiro** casasRelevantesAoBispo(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    int index = 0;
    bool encontrouPeca;
    CasaTabuleiro** casasRelevantes = malloc(sizeof(CasaTabuleiro*) * MOVIMENTOS_POSSIVEIS_BISPO);

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_BISPO; i++)
        casasRelevantes[i] = NULL;

    //Movimentos na diagonal superior esquerda (da posição do bispo indo para cima):
    encontrouPeca = false;
    for(int i = pecaLinhaAtual + 1, j = pecaColunaAtual - 1; i < QTD_CASAS_POR_LINHA && j >= 0; i++, j--, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = malloc(sizeof *casaPossivelParaMoverTorre);
        *casaPossivelParaMoverTorre = tabuleiro[i][j];
        
        if(encontrouPeca) {
            casasRelevantes[index] = NULL;
            //free(casaPossivelParaMoverTorre);
        }
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casaPossivelParaMoverTorre->peca != NULL)//Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor) {
                casasRelevantes[index] = NULL;
                //free(casaPossivelParaMoverTorre);
            }
        }
    }

    //Movimentos na diagonal superior direita (da posição do bispo indo para cima):
    encontrouPeca = false;
    for(int i = pecaLinhaAtual + 1, j = pecaColunaAtual + 1; i < QTD_CASAS_POR_LINHA && j < QTD_CASAS_POR_COLUNA; i++, j++, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = malloc(sizeof *casaPossivelParaMoverTorre);
        *casaPossivelParaMoverTorre = tabuleiro[i][j];
        
        if(encontrouPeca) {
            casasRelevantes[index] = NULL;
            //free(casaPossivelParaMoverTorre);
        }
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casaPossivelParaMoverTorre->peca != NULL)//Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor) {
                casasRelevantes[index] = NULL;
                //free(casaPossivelParaMoverTorre);
            }
        }
    }

    //Movimentos na diagonal inferior esquerda (da posição do bispo indo para baixo):
    encontrouPeca = false;
    for(int i = pecaLinhaAtual - 1, j = pecaColunaAtual - 1; i >= 0 && j >= 0; i--, j--, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = malloc(sizeof *casaPossivelParaMoverTorre);
        *casaPossivelParaMoverTorre = tabuleiro[i][j];
        
        if(encontrouPeca) {
            casasRelevantes[index] = NULL;
            //free(casaPossivelParaMoverTorre);
        }
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casaPossivelParaMoverTorre->peca != NULL)//Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor) {
                casasRelevantes[index] = NULL;
                //free(casaPossivelParaMoverTorre);
            }
        }
    }

    //Movimentos na diagonal inferior direita (da posição do bispo indo para baixo):
    encontrouPeca = false;
    for(int i = pecaLinhaAtual - 1, j = pecaColunaAtual + 1; i >= 0 && j < QTD_CASAS_POR_COLUNA; i--, j++, index++)
    {
        CasaTabuleiro* casaPossivelParaMoverTorre = malloc(sizeof *casaPossivelParaMoverTorre);
        *casaPossivelParaMoverTorre = tabuleiro[i][j];
        
        if(encontrouPeca) {
            casasRelevantes[index] = NULL;
            //free(casaPossivelParaMoverTorre);
        }
        else   
            casasRelevantes[index] = casaPossivelParaMoverTorre;

        if(casaPossivelParaMoverTorre->peca != NULL)//Se achar alguma peça pare
        {
            encontrouPeca = true;
            if(casaPossivelParaMoverTorre->peca->cor == tabuleiro[pecaLinhaAtual][pecaColunaAtual].peca->cor) {
                casasRelevantes[index] = NULL;
                //free(casaPossivelParaMoverTorre);
            }
        }
    }


    return casasRelevantes;
}


//Rainha não pode pular peças
//Rainha se move em qualquer sentido (diagonal, horizontal e vertical) como se fosse um Bispo ou Torre
//Rainha não pode ultrapassar o board
ListaCasaTabuleiro** movimentosPossiveisRainha(CasaTabuleiro peca, Tabuleiro tabuleiro) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    CasaTabuleiro **casasRelevantes = casasRelevantesARainha(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    ListaCasaTabuleiro** movimentosPossiveis = malloc(sizeof(ListaCasaTabuleiro*));
    criarLista(movimentosPossiveis, sizeof(CasaTabuleiro));

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_RAINHA; i++)
    {
        if(casasRelevantes[i] != NULL)
            adicionarItemAoFinalDaLista(*movimentosPossiveis, casasRelevantes[i]);
    }

    //for(int i = 0; i < MOVIMENTOS_POSSIVEIS_RAINHA; i++)
    //    free(casasRelevantes[i]);
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


//Rei não pode pular peças
//Rei se move como a Rainha, mas sempre limitado por uma casa
//Rei não pode ultrapassar o board
//Rei não pode se colocar em cheque
ListaCasaTabuleiro** movimentosPossiveisRei(CasaTabuleiro peca, Tabuleiro tabuleiro) {
    Coordenada pecaLinhaAtual = peca.peca->posicao.linha;
    Coordenada pecaColunaAtual = peca.peca->posicao.coluna;

    CasaTabuleiro **casasRelevantes = casasRelevantesAoRei(tabuleiro, pecaLinhaAtual, pecaColunaAtual);
    ListaCasaTabuleiro** movimentosPossiveis = malloc(sizeof(ListaCasaTabuleiro*));
    criarLista(movimentosPossiveis, sizeof(CasaTabuleiro));

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_REI; i++)
    {
        if(casasRelevantes[i] != NULL)
        {
            bool existePecaComMesmaCor = casasRelevantes[i]->peca != NULL && casasRelevantes[i]->peca->cor == peca.peca->cor;
            if(!existePecaComMesmaCor)
                adicionarItemAoFinalDaLista(*movimentosPossiveis, casasRelevantes[i]);
        }
    }

    //for(int i = 0; i < MOVIMENTOS_POSSIVEIS_REI; i++)
    //   free(casasRelevantes[i]);
    free(casasRelevantes);
    return movimentosPossiveis;
}

CasaTabuleiro** casasRelevantesAoRei(Tabuleiro tabuleiro, Coordenada pecaLinhaAtual, Coordenada pecaColunaAtual) {
    CasaTabuleiro *casa_SuperiorDireita = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casa_SuperiorEsquerda = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casa_Superior = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casa_Esquerda = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casa_InferiorDireita = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casa_InferiorEsquerda = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casa_Inferior = malloc(sizeof(CasaTabuleiro));
    CasaTabuleiro *casa_Direita = malloc(sizeof(CasaTabuleiro));

    CasaTabuleiro casaVazia;
    Posicao posNegativa = { -1, -1 };
    casaVazia.localizacao = posNegativa;

    *casa_SuperiorDireita = pecaLinhaAtual + 1 < QTD_CASAS_POR_LINHA && pecaColunaAtual + 1 < QTD_CASAS_POR_COLUNA ? tabuleiro[pecaLinhaAtual+1][pecaColunaAtual+1] : casaVazia;
    *casa_SuperiorEsquerda = pecaLinhaAtual + 1 < QTD_CASAS_POR_COLUNA && pecaColunaAtual - 1 >= 0 ? tabuleiro[pecaLinhaAtual+1][pecaColunaAtual-1] : casaVazia;
    *casa_Superior = pecaLinhaAtual + 1 < QTD_CASAS_POR_COLUNA ? tabuleiro[pecaLinhaAtual+1][pecaColunaAtual] : casaVazia;
    *casa_Esquerda = pecaColunaAtual - 1 >= 0 ? tabuleiro[pecaLinhaAtual][pecaColunaAtual-1] : casaVazia;
    *casa_InferiorDireita = pecaLinhaAtual - 1 >= 0 && pecaColunaAtual + 1 < QTD_CASAS_POR_COLUNA ? tabuleiro[pecaLinhaAtual-1][pecaColunaAtual+1] : casaVazia;
    *casa_InferiorEsquerda = pecaLinhaAtual - 1 >= 0 && pecaColunaAtual - 1 >= 0 ? tabuleiro[pecaLinhaAtual-1][pecaColunaAtual-1] : casaVazia;
    *casa_Inferior = pecaLinhaAtual - 1 >= 0 ? tabuleiro[pecaLinhaAtual-1][pecaColunaAtual] : casaVazia;
    *casa_Direita = pecaColunaAtual - 1 >= 0 ? tabuleiro[pecaLinhaAtual][pecaColunaAtual-1] : casaVazia;

    CasaTabuleiro** casasRelevantes = malloc(sizeof(CasaTabuleiro*) * MOVIMENTOS_POSSIVEIS_REI);

    casasRelevantes[0] = casa_SuperiorDireita;
    casasRelevantes[1] = casa_SuperiorEsquerda;
    casasRelevantes[2] = casa_Superior;
    casasRelevantes[3] = casa_Esquerda;
    casasRelevantes[4] = casa_InferiorDireita;
    casasRelevantes[5] = casa_InferiorEsquerda;
    casasRelevantes[6] = casa_Inferior;
    casasRelevantes[7] = casa_Direita;

    for(int i = 0; i < MOVIMENTOS_POSSIVEIS_REI; i++) {
        CasaTabuleiro* casaAtualRei = casasRelevantes[i];
        if(casaAtualRei->localizacao.linha == -1) {
            //free(casaAtualRei);
            casasRelevantes[i] = NULL;
        }
    }
    
    //printArray(casasRelevantes, "casas relevantes rei", MOVIMENTOS_POSSIVEIS_REI);
    return casasRelevantes;
}

void moverPeca(CasaTabuleiro pecaMovida, Tabuleiro tabuleiro, CasaTabuleiro novaPosicao, CorPeca corJogando) {
    if(novaPosicao.peca != NULL && pecaMovida.peca->cor == novaPosicao.peca->cor)
        return;

    tabuleiro[novaPosicao.localizacao.linha][novaPosicao.localizacao.coluna].peca = pecaMovida.peca;
    tabuleiro[pecaMovida.peca->posicao.linha][pecaMovida.peca->posicao.coluna].peca = NULL;
    tabuleiro[novaPosicao.localizacao.linha][novaPosicao.localizacao.coluna].peca->posicao = novaPosicao.localizacao;
    tabuleiro[novaPosicao.localizacao.linha][novaPosicao.localizacao.coluna].localizacao = novaPosicao.localizacao;
    //free(novaPosicao.peca); //talvez apague dps (depende de como Peca *peca é criada)

    if(pecaMovida.peca->tipo == PEAO && pecaMovida.localizacao.linha == 1 && novaPosicao.localizacao.linha == 3) {
        tabuleiro[0][novaPosicao.localizacao.coluna].peca = malloc(sizeof(CasaTabuleiro));
        tabuleiro[0][novaPosicao.localizacao.coluna].peca->tipo = getTipoPelaColuna(novaPosicao.localizacao.coluna);
        tabuleiro[0][novaPosicao.localizacao.coluna].peca->tipo = getTipoPelaColuna(novaPosicao.localizacao.coluna);
        tabuleiro[0][novaPosicao.localizacao.coluna].peca->cor = corJogando;
        tabuleiro[0][novaPosicao.localizacao.coluna].peca->posicao = tabuleiro[0][novaPosicao.localizacao.coluna].localizacao;

        tabuleiro[1][0].peca = NULL;
        return;
    }
}

ListaCasaTabuleiro** movimentosPossiveis(CasaTabuleiro peca, Jogo jogo) {
    ListaCasaTabuleiro **movimentosPossiveisPeca = NULL;

    if(peca.peca == NULL)
        return NULL;

    switch (peca.peca->tipo)
    {
        case PEAO:
            movimentosPossiveisPeca = movimentosPossiveisPeao(peca, jogo.tabuleiro);
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

bool movimentoExisteEmTalPosicao(int linha, int coluna, ListaCasaTabuleiro* lista) {
    bool movimentoExiste = false;

    for(size_t i = 0; i < lista->len; i++) {
        CasaTabuleiro *casaAtual = retornarElementoDaLista(lista, i)->data;
        if(casaAtual->localizacao.linha == linha && casaAtual->localizacao.coluna == coluna)
            movimentoExiste = true;
    }

    return movimentoExiste;
}
