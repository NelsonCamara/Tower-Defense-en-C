#include "EntityMovements.h"
#include <unistd.h>




double monsterSpeedVariation() {

    srand(time(NULL));
    int randInt = rand();
    double normalizedRand = (double)randInt / RAND_MAX;    
    double randomDouble = 0.9 + normalizedRand * 0.2;

    return randomDouble;
}


double distanceCalculation(double shotX, double shotY, double monsterX, double monsterY){ 
    return sqrt(pow(monsterX - shotX,2) + pow(monsterY - shotY,2));
}


int  shotDirection(Shoot *shot, Monster monster){
    double xDir = 0, yDir = 0;
    double distance = 0;
    double shotspeed = 0;

    
    shotspeed = 3.0/60;
    
    distance = distanceCalculation(shot->xPosition, shot->yPosition,monster.posX, monster.posY);
   
    
    if(distance <= shotspeed)return 1;
    if(distance != 0){
        xDir = (monster.posX - shot->xPosition)/ distance;
        yDir = (monster.posY - shot->yPosition)/ distance;
        
        shot->xPosition += xDir * shotspeed;
        shot->yPosition += yDir * shotspeed;
        
    }
    
    //printf("Xtir %f, yTir %f\n", shot->xPosition, shot->yPosition);

    return 0;
}

void gemShot(Grid *gameData) {
    Monster *currentMonster;
    Tower *currentTower;
    for (int i = 0; i < gameData->num_towers; i++) {
        if (!gameData->towers[i].isGemActive) continue;

        currentTower= &(gameData->towers[i]);

        int targetIndex = -1;
        int maxHealth = 0;

        for (int j = 0; j < gameData->monstersArr->size; j++) {
            currentMonster = &(gameData->monstersArr->array[j]);

            if (posFlInZone(currentMonster->posX,currentMonster->posY,currentTower->posTower->i,currentTower->posTower->j,3)==0 &&
                currentMonster->monsterHealth > maxHealth) {
                maxHealth = currentMonster->monsterHealth;
                targetIndex = j;
            }
        }

        if(targetIndex != -1) {
            double targetX = ((double)(currentTower->posTower->i)) + 0.5;
            double targetY = ((double)(currentTower->posTower->j)) + 0.5;
            
            addElemShotArray(gameData->monstersArr->array[targetIndex].shootArray,
                initializeShoot2(currentMonster->posX, currentMonster->posY,
                    currentTower->gem, targetX, targetY));
        }
    }
}





void monsterMove(Grid * grid){
    int i;
    for(i = 0; i < grid->monstersArr->size; i++){
        if(grid->monstersArr->array[i].posWay >= grid->size_way){
            grid->player->mana -= 0.15*grid->monstersArr->array[i].monsterHealth*pow(1.3,grid->player->levelMana);
            grid->monstersArr->array[i].posWay = 0;
            grid->monstersArr->array[i].posX = grid->way[0].i;
            grid->monstersArr->array[i].posY = grid->way[0].j;
            grid->monstersArr->array[i].direction = grid->way[0].dir;
        } 
        updateDir(grid->way, &(grid->monstersArr->array[i])); 
        updatePos(&(grid->monstersArr->array[i]));
    }
}

void updatePos(Monster *monster){
    
    switch(monster->direction){
        case NORTH : monster->posY -= monster->speed/60 * monsterSpeedVariation(); break;
        case SOUTH : monster->posY += monster->speed/60 * monsterSpeedVariation(); break;
        case EAST : monster->posX += monster->speed/60 * monsterSpeedVariation(); break;
        case WEST : monster->posX -= monster->speed/60 * monsterSpeedVariation(); break;
        case NO_DIR : break;
    }
}

void updateDir(Point *way, Monster *monster){
    //printf("%f %d, %f %d \n", monster->posX, way[monster->posWay].i, monster->posY, way[monster->posWay].j );
    switch(monster->direction){
        case SOUTH : {
            if(monster->posY >= way[monster->posWay].j  ){
                monster->direction = way[monster->posWay].dir;
                monster->posWay++;
            } break;
        }
        case NORTH : {
            if(monster->posY <= way[monster->posWay].j ){
                monster->direction = way[monster->posWay].dir;
                monster->posWay++;
            } break;
        }
        case EAST : {
            if(monster->posX >= way[monster->posWay].i  ){
                monster->direction = way[monster->posWay].dir;
                monster->posWay++;
            } break;
        }
        case WEST : {
            if(monster->posX <= way[monster->posWay].i  ){
                monster->direction = way[monster->posWay].dir;
                monster->posWay++;
            } break;
        }
        case NO_DIR : break;
    }  
}