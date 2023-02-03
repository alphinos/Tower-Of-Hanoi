#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define SIZE 7
#define QTD_SPC SIZE - 1
#define qtdT 3

typedef struct disk{
  int pos;
  int id;
} Disk;

typedef struct tower{
  Disk *tower;
  int tam;
  int currentTAM;
} Tower;

Tower createTower(int size){
  Tower t;
  t.tower = (Disk*)malloc(size * sizeof(Disk));
  t.tam = size;
  t.currentTAM = 0;
  return t;
}

void fulfillDisk(Tower *t){
  for (int i = 0; i < t->tam; i++){
    Disk d = {i, t->tam - i};
    t->tower[i] = d;
  }
  t->currentTAM = t->tam;
}

void removeDisk(Tower *t){
  Disk O = {0, 0};
  t->tower[t->currentTAM - 1] = O;
  t->currentTAM--;
}

void addDisk(Tower *t, Disk *newD){
  t->currentTAM++;
  t->tower[t->currentTAM - 1] = *newD;
}

void moveDisk(Tower *last, Tower *dance){
  Disk lastDisk = last->tower[last->currentTAM - 1];
  removeDisk(last);
  addDisk(dance, &lastDisk);
}

void drawLine(int disco){
  if(disco == 0){
    for (int a = 0; a <= QTD_SPC - disco - 1; a++){
      printf(" ");
    }
      printf("|");
  } else {
    for (int a = 0; a <= QTD_SPC - disco; a++){
      printf(" ");
    }
    for (int b = 0; b < 2 * disco - 1; b++){
      printf("=");
    }
  }
  for (int c = 0; c < QTD_SPC - disco; c++){
    printf(" ");
    } 
}


void printGame(Tower *tower_vec){
  printf("\n");
  for (int i = SIZE-1; i > -1; i--){
    for (int j = 0; j < qtdT; j++){ 
      int disco = tower_vec[j].tower[i].id;
      drawLine(disco);
      printf("\t\t");
    }
    printf("\n");
  }
  printf("\n");
}

void gamePlay(void){
	// Let's play
	//Função que inicia o jogo

  int towerOut, towerIn;

  Tower towers[qtdT];
  for (int i = 0; i < qtdT; i++){
    towers[i] = createTower(SIZE);
  }
  fulfillDisk(&towers[0]);
  
  while (TRUE){
    printGame(towers);
    printf("Coé, meu mano, move os discos da torre aí!\n");
    printf("Escolha a Torre de Saída: ");
    scanf("%d", &towerOut);
    printf("Escolha a Torre de Entrada: ");
    scanf("%d", &towerIn);
    moveDisk(&towers[towerOut], &towers[towerIn]);    
  }
}

int main(void) {
  gamePlay();
  return 0;
}