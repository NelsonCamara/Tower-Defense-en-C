#include "Tower.h"

void initializeTower(Tower *tower, int posX, int posY) {
    tower->posTower = malloc(sizeof(Point)); // Alloue de la mémoire pour posTower
    if (tower->posTower != NULL) {
        tower->posTower->i = posX;
        tower->posTower->j = posY;
        fillSquare(*(tower->posTower), tower->shootZone);
        tower->isGemActive = false;
        tower->containGemSince = 0;
        tower->gem = NULL;
    } else {
        fprintf(stderr,"memory error in monsterPos allocation");
        exit(EXIT_FAILURE);
    }
}




void fillSquare(Point center, Point square[]) {
    int index = 0;
    printf("POS  %d|%d\n",center.i,center.j);
    for (int i = center.i - 3; i <= center.i + 3; i++) {
        for (int j = center.j - 3; j <= center.j + 3; j++) {
            if (i != center.i || j != center.j) { 
                
                square[index].i = i;
                square[index].j = j;
                index++;
            }
        }
    }
}


void detTowerShootZone(Tower tower,Point shootZone[48]){
    
    fillSquare(*(tower.posTower),shootZone);
    for(int i = 0;i<47;i++){
        printf("Point :%d %d\n",shootZone[i].i,shootZone[i].j);
    }
}

bool isGemActiveForTwoSeconds(Tower *tower) {
    
    if(tower->containGemSince >= 2.0&& tower->gem != NULL){
        tower->isGemActive = true;
        return true;
    } 
    else return false;

 
}

void resetTowerState(Tower *tower){
    tower->isGemActive = false;
    tower->containGemSince = 0;
}


Monster* findStrongestMonsterInZone(Tower tower, Monster monsters[], int numMonsters) {
    Monster* strongestMonster = NULL;
    int highestHealth = 0;

    for (int i = 0; i < numMonsters; i++) {
        for (int j = 0; j < 48; j++) {
            if (monsters[i].posCaseMonster->i == tower.shootZone[j].i && 
                monsters[i].posCaseMonster->j == tower.shootZone[j].j) {
                if (monsters[i].monsterHealth > highestHealth) {
                    highestHealth = monsters[i].monsterHealth;
                    strongestMonster = &monsters[i];
                }
            }
        }
    }

    return strongestMonster;
}




void showTower(Tower tower){
    printf("---------------TOWER-----------------\n");
    printf("X POS :%d\n",tower.posTower->i);
    printf("Y POS :%d\n",tower.posTower->j);
    if(tower.gem != NULL) showGem(*tower.gem);
}