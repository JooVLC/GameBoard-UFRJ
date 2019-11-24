# GameBoard-UFRJ

- Projeto da UFRJ - C (Jogo de Tabuleiro)
- [Prof: Valeria Menezes Bastos](https://dcc.ufrj.br/~valeriab/)

---

## Jogo de Tabuleiro Escolhido: Xadrez

---

### Código no bash do Linux(MAC) para compilar e executar o programa

```bash
cd objects
gcc -c *.c -Wall -Wextra -asci -pedantic
mv *.o ../
cd ..
gcc `pkg-config gtk+-3.0 --cflags` program.c gui.c *.o -o xadrez.out -Wall -Wextra -asci -pedantic `pkg-config gtk+-3.0 --libs`
rm *.o
./xadrez.out
```

> ATENÇÃO: Necessaria a biblioteca gráfica GTK
