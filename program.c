#include "./headers/includeLibrarys.h"
#include "./headers/typesXadrez.h"

#include "./console.c"

void limparBuffer(Nome nome) {
    size_t nomeLen = strlen(nome);
    if(nomeLen != NOME_LEN - 1)
    {
        nome[nomeLen-1] = 0;
    }
    else
    {           
        char c;
        while((c = getchar()) && c != EOF && c != '\n');   
    }
}

int main(void)
{
    Nome nomeBranco, nomePreto;

    puts("Digite o nome do jogador branco: ");
    fgets(nomeBranco, NOME_LEN, stdin);
    limparBuffer(nomeBranco);

    puts("Digite o nome do jogador branco: ");
    fgets(nomePreto, NOME_LEN, stdin);
    limparBuffer(nomePreto);

    puts("Digite qualquer tecla para iniciar o jogo...");
    getchar();

    printf("%s - %s\n", nomePreto, nomeBranco);
    iniciarJogoConsole(nomeBranco, nomePreto);
    //iniciarJogoGUI(nomeBranco, nomePreto);

    puts("Digite qualquer tecla para fechar o jogo...");
    getchar();

    return 0;
}