# GameBoard-UFRJ

- Projeto da UFRJ - C (Jogo de Tabuleiro)
- [Prof: Valeria Menezes Bastos](https://dcc.ufrj.br/~valeriab/)

---

## Jogo de Tabuleiro Escolhido: Xadrez

---

### Código no bash do Linux(ou MAC) para compilar e executar o programa

```bash
cd objects
gcc -c *.c -Wall -Wextra -pedantic -pedantic-errors
mv *.o ../
cd ..
gcc program.c *.o -o xadrez.out -Wall -Wextra -pedantic -pedantic-errors
rm *.o
./xadrez.out
```

### Código no bash do PowerShell para compilar e executar o programa

> Necessario antes a instalação do gcc no Windows

```bash
rm xadrez.exe
cd objects
gcc -c *.c
mv *.o ../
cd ..
gcc program.c *.o -o xadrez.exe
rm *.o
.\xadrez.exe
```

---

> ATENÇÃO: Necessaria a biblioteca gráfica GTK para usar a versao com gui
