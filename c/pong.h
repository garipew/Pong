

typedef struct barra{
	
	int posX;
	int posY;
	int tamanho;

} Barra;


typedef struct bola{

	int posX;
	int posY;
	int velocidade[2];

} Bola;


typedef struct tela{

	int largura;
	int altura;

} Tela;



Bola* criarBola(Tela*);
Barra* criarBarra(int, int, int);
Tela* criarTela(int, int);
void gameLoop(Tela*, Barra*, Barra*, Bola*);
int gameOver(Tela*, Bola*);
int contato(Tela*, Barra*, Bola*);
void moverBarras(Tela*, Barra*, Barra*);
void atualizarPosicaoBola(Bola*);
void atualizarVelocidadeBola(Tela*, Bola*, int*);
void desenharTela(Tela*, Barra*, Barra*, Bola*);
