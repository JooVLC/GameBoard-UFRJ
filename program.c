#include "./headers/includeLibrarys.h"
#include "./headers/typesXadrez.h"
#include "./headers/consoleLib.h"

int main(void)
{
    Nome nomeBranco, nomePreto;
    system(CLEAR);

    puts("Digite o nome do jogador branco: ");
    fgets(nomeBranco, NOME_LEN, stdin);
    limparBuffer(nomeBranco, NOME_LEN);

    puts("Digite o nome do jogador preto: ");
    fgets(nomePreto, NOME_LEN, stdin);
    limparBuffer(nomePreto, NOME_LEN);

    puts("Digite qualquer tecla para iniciar o jogo...");
    getchar();

    iniciarJogoConsole(nomeBranco, nomePreto);
    //TODO: GUI Version
    //iniciarJogoGUI(nomeBranco, nomePreto);

    puts("Digite qualquer tecla para fechar o jogo...");
    getchar();

    return 0;
}
