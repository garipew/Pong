#include "pong.h"
#include <curses.h>


int main(){
	
	Tela* tela = criarTela(40, 25);
	
	Barra* barraEsquerda = criarBarra(2, (tela->altura - 6), 5);
	Barra* barraDireita = criarBarra((tela->largura - 3) , 3, 5);

	Bola* bola = criarBola(tela);

	initscr();
	noecho();
	cbreak();
	timeout(500);

	gameLoop(tela, barraEsquerda, barraDireita, bola);
	
	endwin();

}
