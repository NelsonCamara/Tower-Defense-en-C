#include "PlayerEvents.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>




void showPlayer(Player player){
    printf("-------------------SHOW PLAYER-----------\n");
    printf("MANA MAX :%d\n",player.manaMax);
    printf("MANA :%d\n",player.mana);
    printf("MANA LEVEL:%d\n",player.levelMana);
    printf("NB GEMS:%d\n",player.cntGems);
    if(player.cntGems > 0){
        for(int i=0;i<player.cntGems;i++){
            showGem(player.gems[i]);
        }
    }
}



void addGem(Player *player,Gem gem){
    player->gems[player->cntGems] = gem;
    player->cntGems++;
}


void manaAddLevel(Player *player){
    player->levelMana++;
    double resStockMana= pow(1.4,player->levelMana) * 2000;
    player->manaMax = (int)resStockMana;
    double resMana = pow(1.4,player->levelMana) * 500;
    player->mana -= (int)resMana;

}

void monsterKilledMana(int maxHPMonster,Player *player){
    double resMana;
    resMana = pow(1.3,player->levelMana)*0.10*maxHPMonster;

    player->mana += (int) resMana;
    if(player->mana > player->manaMax) player->mana = player->manaMax;
}


int monsterSurvivedTheWay(int maxHPMOnster,Player *player){
    double resMana;
    resMana = pow(1.3,player->levelMana)*0.15;

    player->mana -= (int) resMana;
    if(player->mana < 0 ){
        return -1;
    }
    else return 0;
}



void applyPyro(Monster *monsters,float centerXPoint,float centerYPoint,int cntMonsters,int shootTint,int shootLevel){
    for(int i = 0;i<cntMonsters;i++){
        if(posFlInZone(monsters[i].posX,monsters[i].posY,centerXPoint,centerXPoint,2.5) ==0){
            monsters[i].monsterHealth -= 0.15*applyDamage(shootTint,monsters[i].tint,shootLevel);
            

        }
    }
}

void applyPyroXHydro(Monster *monsters,float centerXPoint,float centerYPoint,int cntMonsters,int shootTint,int shootLevel,Monster *hittedMonster){
    for(int i = 0;i<cntMonsters;i++){
        if(posFlInZone(monsters[i].posX,monsters[i].posY,centerXPoint,centerXPoint,3.5) == 0){
            monsters[i].monsterHealth -= 0.15*applyDamage(shootTint,monsters[i].tint,shootLevel);
            if(monsters[i].monsterElement !=UNDER_DOUBLE_EFFECT ){
                monsters[i].speed /= 1.25;
                monsters[i].monsterElement = UNDER_DOUBLE_EFFECT;
                monsters[i].elemEvent = hittedMonster->elemEvent;
                
            }
            
            

        }
    }
}





void updateTimedElementalEvent(double frametime,Monster *monsters,int cntMonsters,Point *monstersWay) {
    ElementalEvent *event;
    TimedEvent *timedEvent;
    
    for(int i =0;i<cntMonsters;i++){
        event = monsters[i].elemEvent;
        
        
        if (event == NULL){
            
            continue; 
        }               
        
        switch (event->type) {
            
            case EVENT_TYPE_PYRO:
                
                applyPyro(monsters,monsters[i].posX,monsters[i].posY,cntMonsters,event->shootTint,event->shootLevel);
                monsters[i].monsterElement = PYRO;
                
                monsters[i].elemEvent = NULL;
                break;
            case EVENT_TYPE_DENDRO:
                
                timedEvent = event->timedEvent;

                timedEvent->elapsed_since_last_event += frametime;
                timedEvent->elapsed_total += frametime;
                if(timedEvent->elapsed_since_last_event >= 0.5){
                    monsters[i].monsterHealth -= 0.025*applyDamage(event->shootTint,monsters[i].tint,event->shootLevel);
                    timedEvent->elapsed_since_last_event= 0;
                    monsters[i].monsterElement = DENDRO;
                }
                if (timedEvent->elapsed_total >= timedEvent->duration) monsters[i].elemEvent = NULL;
                break;
            case EVENT_TYPE_HYDRO:
                
                timedEvent = event->timedEvent;

                timedEvent->elapsed_since_last_event += frametime;
                timedEvent->elapsed_total += frametime;
                if (timedEvent->active == true && monsters[i].monsterElement != UNDER_DOUBLE_EFFECT) {
                    monsters[i].speed /= 1.5;
                    timedEvent->active = false;
                    monsters[i].monsterElement = HYDRO;
                }
                if(timedEvent->elapsed_total >= timedEvent->duration) {
                    monsters[i].speed = monsters[i].initialSpeed;
                    monsters[i].elemEvent = NULL;
                    
                }
            
                break;
            case PYRO_AND_DENDRO:
                
                monsters[i].monsterHealth -= 2*applyDamage(event->shootTint,monsters[i].tint,event->shootLevel);
                monsters[i].monsterElement =NO_ELEMENT;
                monsters[i].elemEvent = NULL;
                break;
            case PYRO_HYDRO:
                
                timedEvent = event->timedEvent;

                timedEvent->elapsed_since_last_event += frametime;
                timedEvent->elapsed_total += frametime;
                if (timedEvent->elapsed_total <= timedEvent->duration && timedEvent->active == true)  {
                    applyPyroXHydro(monsters,monsters[i].posX,monsters[i].posY,cntMonsters,event->shootTint,event->shootLevel,&monsters[i]);
                    timedEvent->active = false;
                }
                else{
                    for(int j = 0;j<cntMonsters;j++){
                        if(monsters[j].elemEvent == monsters[i].elemEvent && timedEvent->elapsed_total >= timedEvent->duration){
                            monsters[j].speed =monsters[j].initialSpeed;
                            monsters[j].elemEvent = NULL;
                            monsters[j].monsterElement =NO_ELEMENT;
                        } 
                    }
                    monsters[i].monsterElement =NO_ELEMENT;
                    monsters[i].elemEvent = NULL;
                } 
                break;
            case DENDRO_HYDRO:
                
                timedEvent = event->timedEvent;

                timedEvent->elapsed_since_last_event += frametime;
                timedEvent->elapsed_total += frametime;
                if(timedEvent->active == true){
                    monsters[i].speed = 0;
                    timedEvent->active = false;

                }
                if(timedEvent->elapsed_total >= timedEvent->duration){
                    monsters[i].speed = monsters[i].initialSpeed;
                    monsters[i].monsterElement =NO_ELEMENT;
                    monsters[i].elemEvent = NULL;

                }
                
                break;
        }
        
    
    }

}


void updateWaveTimeEvent(Grid *grid,double frametime,WaveNode **head){
    grid->waveTimed->elapsed_since_last_event += frametime;
    grid->waveTimed->elapsed_total += frametime;
    if(grid->waveTimed->elapsed_since_last_event >= 35){
        
        Wave *wave;
        wave = malloc(sizeof(Wave));
        if(wave == NULL){
            perror("Unable to allocate memory for new wave");
            exit(EXIT_FAILURE);
        }
        
        initWave(wave,waveTypeFromInt(grid->cntWaves));
        *head = insertWaveSorted(*head,wave);
        
        grid->cntWaves++;
               
        grid->waveTimed->elapsed_since_last_event = 0;

    }
}





void newWaveForcedMana(Grid *grid){
    double timeRemain;
   
    timeRemain = 35 - grid->waveTimed->elapsed_since_last_event;
    
    grid->player->mana += (int) ((timeRemain/100)* grid->player->manaMax);
    if(grid->player->mana > grid->player->manaMax) grid->player->mana = grid->player->manaMax;

    showPlayer(*grid->player);
}

int enoughManaTower(Grid grid){
    if(grid.num_towers <3){
        return 1;
    }
    if((grid.player->mana - 100 * (1 << (grid.num_towers - 4))) <= 0){
        return 0;
    }
    else return 1;
}

void newTowerManaPrice(Grid *grid){
    if(grid->num_towers <3){
    }
    else{
        grid->player->mana -= 100 * (1 << (grid->num_towers - 4)); 
    }

}


int gemCost(int level){
    return 100*pow(2,level);
}


int addGemOnTower(Grid *grid,Gem *gem,Point *point){
    for(int i = 0;i < grid->num_towers;i++){
        if(grid->towers[i].posTower->i == point->i && grid->towers[i].posTower->j == point->j){
            if(grid->towers[i].gem == NULL){
                grid->towers[i].gem = malloc(sizeof(Gem));
                initializeGem(grid->towers[i].gem,gem->color,gem->gemElement,gem->tint);
                
                grid->towers[i].gem->level = gem->level;
                
                grid->towers[i].gem->gemPosition->i = point->i;
                grid->towers[i].gem->gemPosition->j = point->j;

                return 0;
            }
            else{
                return 1;
            }
        }
    }
    return 1;
}