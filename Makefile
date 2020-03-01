all: jogo

jogo: mao.o baralho.o tarefas.o embaralha.o regras.o arvore.o
	gcc -o jogo mao.o baralho.o tarefas.o embaralha.o regras.o arvore.o -lm

mao.o: mao.c
	gcc -c mao.c

baralho.o: baralho.c
	gcc -c baralho.c

tarefas.o: tarefas.c
	gcc -c tarefas.c

embaralha.o: embaralha.c
	gcc -c embaralha.c
regras.o: regras.c
	gcc -c regras.c

arvore.o: arvore.c
	gcc -c arvore.c
clean:
	rm *.o jogo

rmpromper: clean
	rm -rf jogo

run: jogo
	./jogo

