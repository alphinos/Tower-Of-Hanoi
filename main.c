#include <stdio.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0

#define QTD_TORRE 3


//Define o Tipo Disco, que contém a posição na Torre e o ID, este último necessário para o tamanho do disco
typedef struct disk{
  int id;
} Disk;

//Define o Tipo Torre, contendo um ponteiro para o vetor de discos, o tamanho (quantidade de discos) e o tamanho atual
typedef struct tower{
  Disk *discos;
  int tam;
  int currentTAM;
} Tower;

//Cria a Torre com a Quantidade de Discos escolhida
Tower createTower(int size){
  Tower t;
  t.discos = (Disk*)malloc(size * sizeof(Disk));
  t.tam = size;
  t.currentTAM = 0;
  return t;
}

//Enche uma Torre com Todos os Discos
void fullfillDisk(Tower *t){
  for (int i = 0; i < t->tam; i++){
    Disk d = {t->tam - i};
    t->discos[i] = d;
  }
  t->currentTAM = t->tam;
}

//Esvazia Todas as Torres
void clean_towers(Tower *towers){
  for(int j=0; j<QTD_TORRE; j++){
      for(int i=0; i<towers[0].tam; i++){
        towers[j].discos[i].id = 0;
    }
  }
}

//Remove um Disco de uma Torre
void removeDisk(Tower *t){
  Disk O = {0};
  t->discos[t->currentTAM - 1] = O;
  t->currentTAM--;
}

//Adiciona um disco à uma Torre
void addDisk(Tower *t, Disk *newD){
  t->currentTAM++;
  t->discos[t->currentTAM - 1] = *newD;
}

//Move um Disco de uma Torre para a Outra
int moveDisk(Tower *Out, Tower *In){
  Disk lastDisk_out = Out->discos[Out->currentTAM - 1];
  if(In->currentTAM != 0){
    Disk lastDisk_in = In->discos[In->currentTAM-1];
    if(lastDisk_out.id > lastDisk_in.id){
      return FALSE;
    }
  }
  removeDisk(Out);
  addDisk(In, &lastDisk_out);
  return TRUE;
}

void drawLine(int disco, int QTD_SPC){
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
  for (int i =  tower_vec[0].tam-1; i > -1; i--){
    for (int j = 0; j < QTD_TORRE; j++){ 
      int id_disco = tower_vec[j].discos[i].id;
      drawLine(id_disco, tower_vec[0].tam-1);
      printf("\t\t");
    }
    printf("\n");
  }
  printf("\n");
}

int verifica_win(Tower t){
  if( t.currentTAM == t.tam){
    return TRUE;
  }
  return FALSE;
}

void gamePlay(void){
	// Let's play
	//Função que inicia o jogo

  int towerOut, towerIn;
  int qtd_discos;

  printf("Fala meu dog, quer tentar a torre de Hanoi com quantos discos? \n");
  scanf("%d", &qtd_discos);

  Tower towers[QTD_TORRE];
  for (int i = 0; i < QTD_TORRE; i++){
    towers[i] = createTower(qtd_discos);
  }
  clean_towers(towers);
  fullfillDisk(&towers[0]);
  
  int quantidade_movimentos = 0;
  while (TRUE){
    printGame(towers);
    printf("Coeh, meu mano, move os discos da torre aih!\n");
    printf("Escolha a Torre de Saihda: ");
    scanf("%d", &towerOut);
    printf("Escolha a Torre de Entrada: ");
    scanf("%d", &towerIn);
    system("cls");
    int movement_validation = moveDisk(&towers[towerOut], &towers[towerIn]); 

    quantidade_movimentos++; 
    
    int win_ = verifica_win(towers[QTD_TORRE-1]);

    if(movement_validation == FALSE){
      printf("MOvimento Invalido meu dog\n");
    }  

    if(win_ == TRUE){
      printf("Oloco, meu PIT. Parabens, vc resolveu a torre de hanoi de %d Discos com %d movimentos!", qtd_discos, quantidade_movimentos);
      break;
    }
  }

}

int main(void) {
  gamePlay();
  return 0;
}