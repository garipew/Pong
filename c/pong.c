#include "pong.h"
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/time.h>
#include <unistd.h>


Bola* criarBola(Tela* tela){


	Bola* bola = (Bola*)malloc(sizeof(Bola));

	bola->posX = tela->largura/2;
	bola->posY = tela->altura/2;


	bola->velocidade[0] = 1;
	bola->velocidade[1] = -1;


	return bola;

}


Barra* criarBarra(int posX, int posY, int tamanho){


	Barra* barra = (Barra*)malloc(sizeof(Barra));
	
	barra->posX = posX;
	barra->posY = posY;
	barra->tamanho = tamanho;


	return barra;

}


Tela* criarTela(int largura, int altura){


	Tela* tela = (Tela*)malloc(sizeof(Tela));

	tela->altura = altura;
	tela->largura = largura;


	return tela;

}


int* capturarMovimento(int* movimento){
	
	int acao = getch();

	switch(acao){
		
		case 'w':
			*movimento = -1;
			break;
		case 'k':
			*(movimento + 1) = 1;
			break;
		case 's':
			*movimento = 1;
			break;
		case 'i':
			*(movimento + 1) = -1;
			break;
	
	}

	return movimento;

}


void moverBarras(Tela* tela, Barra* barraEsquerda, Barra* barraDireita){

	int movimento[] = {0, 0};
	int* novasPosicoes = capturarMovimento(movimento);
	
	if(((barraEsquerda->posY + *novasPosicoes) >= 1) && ((barraEsquerda->posY + barraEsquerda->tamanho + *novasPosicoes) < tela->altura)){
		barraEsquerda->posY += *novasPosicoes;
	}
	if(((barraDireita->posY + *(novasPosicoes+1)) >= 1) && ((barraDireita->posY + barraDireita->tamanho + *(novasPosicoes+1)) < tela->altura)){
			barraDireita->posY += *(novasPosicoes+1);
	}

}


void atualizarPosicaoBola(Bola* bola){

	bola->posX += bola->velocidade[0];
	bola->posY += bola->velocidade[1];

}

void atualizarVelocidadeBola(Tela* tela, Bola* bola, int* contato){
	

	if(*contato > 0 || *(contato+1) > 0){

		bola->velocidade[0] *= -1;
			
	} 

	if(*contato < 0 || *(contato+1) < 0){
	
		bola->velocidade[1] *= -1;
	}



}


int contato(Tela* tela, Barra* barra, Bola* bola){
	
	int contato = 0;

	if((bola->posX + bola->velocidade[0]) == barra->posX){

		if(((barra->posY - 1) <= bola->posY) && (bola->posY < (barra->posY + barra->tamanho)))
			contato = 1;

	} else if(((bola->posY + bola->velocidade[1]) == 0) || ((bola->posY + bola->velocidade[1]) == (tela->altura - 1))){
	
		contato = -1;
	}

	
	return contato;

}


void desenharTela(Tela* tela, Barra* barraEsquerda, Barra* barraDireita, Bola* bola){
	
	clear();


	for(int i = 0; i < tela->altura; i++){
		for(int j = 0; j < tela->largura; j++){
			
			if(i == 0 || i == (tela->altura - 1)){
				addstr("=");
				continue;
			}
			if(barraEsquerda->posX == j){
				if((barraEsquerda->posY <= i) && (i < (barraEsquerda->posY + barraEsquerda->tamanho))){
					addch('|');
					continue;
				}
			}

			if(barraDireita->posX == j){
				if((barraDireita->posY <= i) && (i < (barraDireita->posY + barraDireita->tamanho))){
				addch('|');
				continue;
				}
			}


			if((bola->posX == j) && (bola->posY == i)){
				addch('x');
				continue;
			}

			addch(' ');
				
		}
		
		addch('\n');

	}

}


int gameOver(Tela* tela, Bola* bola){
	
	if(bola->posX < 0 || bola->posX > tela->largura - 1)
		return 1;
	return 0;

}


void gameLoop(Tela* tela, Barra* barraEsquerda, Barra* barraDireita, Bola* bola){
	
	int cont[2];
	int game = 1;
	char controle = ' ';
	float time[] = {0, 0};
	struct timeval start, end;

	while(game){		
				
		gettimeofday(&start, NULL);

		cont[0] = contato(tela, barraEsquerda, bola);
		cont[1] = contato(tela, barraDireita, bola);
		
		moverBarras(tela, barraEsquerda, barraDireita);

		gettimeofday(&end, NULL);
		

		if(time[0] < 0.1){
			time[0] += (end.tv_sec - start.tv_sec) + (1e-6)*(float)(end.tv_usec - start.tv_usec);
			time[1] += (end.tv_sec - start.tv_sec) + (1e-6)*(float)(end.tv_usec - start.tv_usec);

			continue;
		} else{
			desenharTela(tela, barraEsquerda, barraDireita, bola);
			time[0] = 0;
		}
		
		if(time[1] < 0.3){
			
			time[1] += (end.tv_sec - start.tv_sec) + (1e-6)*(float)(end.tv_usec - start.tv_usec);
			continue;
		} else{
			atualizarVelocidadeBola(tela, bola, cont);
			atualizarPosicaoBola(bola);
		}

		if(gameOver(tela, bola)){

			clear();

			addstr("\n\n\n\n\t\tGame Over ! ! !\n");
			addstr("\tPress R to restart or X to exit");
			
			do{
				controle = getch();
				if(controle == 'x'){
					game = 0;
					break;
				}
				if(controle == 'r'){
					if(bola->posX < 0){
						bola->posX += 15;
					}
					else if(bola->posX > tela->largura){
						bola->posX -= 15;
					}

					break;
				}

			} while((controle != 'x') || (controle != 'r'));
			
		}

		if(game == 0)
			break;
	
	}

	
	free(bola);
	free(barraEsquerda);
	free(barraDireita);
	free(tela);

}







