#include "Game.h"





void iterateUpdates(Grid *gameData, double frametime, int mustShot) {
    int i;
    if(gameData->monstersArr->size >0){
        for (i = 0; i < gameData->monstersArr->size; i++) {
            
            Monster *currentMonster = &(gameData->monstersArr->array[i]);
            
           
            if(currentMonster->shootArray->size > 0){
                for (int n = 0; n < currentMonster->shootArray->size; n++) {
                Shoot *currentShot = &(currentMonster->shootArray->array[n]);
            
                if (shotDirection(currentShot, *currentMonster)) {
                    int monsterKilled = monsterHittedByShoot(currentMonster, currentShot, frametime);
                    if(monsterKilled ==0){
                        monsterKilledMana(currentMonster->monsterMaxHealth,gameData->player);
                    }
                    delElemAtIndexShotArray((currentMonster->shootArray), n);
                }
            }
            }
             if (currentMonster->monsterHealth <= 0) {
                delElemAtIndexMonsterArray(gameData->monstersArr, i);
            }
            
        } 
        

    }
    if(!mustShot){
        gemShot(gameData);
    }
        

}


void spawnMonster(Grid *grid,Wave *wave){

    float monsterHealth;
    Color monsterColor;
    int monsterTint;
    monsterColor = aleatColor();
    monsterTint = aleatTint(monsterColor);
    monsterHealth = 80* pow(1.2,grid->cntWaves);
    if(wave->waveType == BOSS){
        printf("BOSS MONSTER////////////////////////////////////////////////////////////////////////////\n");
        monsterHealth = 12*80* pow(1.2,grid->cntWaves);
        showWave(*wave);
    }

    initializeMonster(&(grid->monstersArr->array[grid->monstersArr->size]),grid->way[0].i,grid->way[0].j,grid->way[0].i,grid->way[0].j,monsterHealth,NO_ELEMENT,monsterColor,monsterTint,wave->speedMonsters, grid->way[0].dir);


}

void updateWavesAndSpawnMonsters(WaveNode *head, double frametime,Grid *grid) {
    WaveNode *current = head;
    while (current != NULL) {
       
        if (current->wave->spawnEvent->elapsed_since_last_event >= current->wave->spawnEvent->frequency || current->wave->spawnEvent->elapsed_total == 0) {
            
            spawnMonster(grid,current->wave);
            grid->monstersArr->size ++;
            

            current->wave->spawnEvent->elapsed_since_last_event = 0;
        } else {
        }
        current->wave->spawnEvent->elapsed_total += frametime;
        current->wave->spawnEvent->elapsed_since_last_event += frametime;
        current = current->next;
    }
}


void updateGemsOnTowers(Tower *towers,int cntTowers,double frametime){
    if(cntTowers == 0){
        return;
    }
    else{
        for(int i = 0;i<cntTowers;i++){
            if(towers[i].gem != NULL){
                
                
                towers[i].containGemSince += frametime;
                if(towers[i].containGemSince >= 2){
                    towers[i].isGemActive = true;
                    
                }
            }
        }
    }
}


void loop_test(Grid *grid, int tile_size,MLV_Input_box *box){
    int compteur;  
    int x, y;
    bool test = false;
    int res,firstGemIndex;
    MLV_Event event;
    
    MLV_Button_state state;
    MLV_Keyboard_modifier keyBoardState;
    MLV_Keyboard_button   keyBoardButton;
    Point *point;
   
    int tailleCase = 10*4;
    compteur = 0;
    srand((unsigned int)time(NULL));
    struct timespec end_time, new_time;
    double frametime, extratime,time;
    time = 0.00;
    frametime = 0;
    WaveNode *waveListHead = NULL;
    char* boxText;
    int maxTextSize = 100; 
    int gameState = 0;

    boxText = (char*) malloc(maxTextSize * sizeof(char));

    if (boxText == NULL) {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }

    boxText[0] = '\0';

    
    while(1){
      
        clock_gettime(CLOCK_REALTIME, &end_time);
        if(grid->player->mana <= 0){
            printf("PARTIE PERDUE\n");
            free(grid->player);
            free(grid->waveTimed);
            freeMonsterArray(grid->monstersArr);
            break;
        }
        draw_all(*grid, tile_size,box,boxText,gameState);
        
        event = MLV_get_event( 
        &keyBoardButton,&keyBoardState, NULL,
        &boxText, &box,
        &x,&y, NULL,
        &state
        );

        if (event == MLV_INPUT_BOX){
            printf("TEXT : %s\n",boxText);

           
            
            
            
            
        }
        if(event == MLV_MOUSE_BUTTON && state == MLV_PRESSED){
            point = clickOnGridCase(x,y,tailleCase);
            if(point != NULL){
                drawZone(tailleCase,*point);
                if(gameState == 3){
                    
                    if(pointInWay(*point,grid->way,grid->size_way)==0 && isUniquePosition(*grid,*point)== true){
                        if(enoughManaTower(*grid) == 1){
                            addTower(grid,*point);
                            drawTower(tailleCase,*grid,point->i,point->j);
                            newTowerManaPrice(grid);
                        }
                        else printf("PAS ASSEZ DE MANA\n");
                        
                        gameState = 0;
                    }
                    else gameState = 0;

                    

                }
                if(gameState == 4){
                    if(grid->gems[firstGemIndex].gemState == 0){
                        if(isUniquePosition(*grid,*point)== false){
                            if(addGemOnTower(grid,&grid->gems[firstGemIndex],point) ==0){
                                grid->gems[firstGemIndex].gemState = 1;
                                fillInventoryHolesCaller(grid);
                                grid->cntGems--;
                            }
                        }
                    }
                    
                    gameState = 0;
                }
            } 
            if(clickOnNewGemButton(x,y,tailleCase)==0 && (gameState ==0||gameState == 3)){
                printf("CLICK SUR BOUTON GEMME\n");
                gameState = 1;
            }

       

            if( clickOnNewLevelButton(x,y,tailleCase) == 0 && gameState == 1 && isAllDigits(boxText)==true){
                
                gameState = 2;


            }
            
            if(gameState == 2){
                printf("GEMME DANS LINVENTAIRE\n");
                Gem *gem;
                int level;
                
                level = atoi(boxText);
                if(grid->player->mana - gemCost(level) > 0){
                    gem = newGem(level);
                
                    boxText[0] = '\0';
                    grid->gems[grid->cntGems] = *gem;
                    grid->gems[grid->cntGems].gemState=0;
                
                    grid->cntGems++;

                }
                showGems(grid->gems,grid->cntGems);
            
                
                gameState = 0;
            }
            res = clickOnInventory(x,y);
            if(res!=-1){

                if(gameState==4){
                    
                    if(grid->player->mana - 100 >0){
                        if(grid->gems[res].gemState ==0 && grid->gems[firstGemIndex].gemState == 0 && res!= firstGemIndex){
                            int tmp;
                            if(firstGemIndex>res){
                                tmp = res;
                                res = firstGemIndex;
                                firstGemIndex = tmp;

                            }
                            if(gemFusion2(&(grid->gems[firstGemIndex]),&(grid->gems[res]))==1){
                                printf("CHECK FUSION OK\n");
                                fillInventoryHolesCaller(grid);
                                grid->player->mana -=100;
                                grid->cntGems--;
                            }
                        }
                    
                    }
                    
                    gameState = 0;
                    
                }
                else{
                    gameState = 4;
                    firstGemIndex = res;

                }
                
            }
            if(clickOnTowerButton(x,y,tailleCase)==0){
                printf("TOWER BUTTON\n");
                gameState = 3;
            }

        }

        if(event == MLV_KEY && keyBoardButton == MLV_KEYBOARD_m && state == MLV_PRESSED){
            Wave *wave;
            wave = malloc(sizeof(Wave));
            if (wave == NULL) {
                perror("Unable to allocate memory for new wave");
                exit(EXIT_FAILURE);
            }
            
            newWaveForcedMana(grid);
            initWave(wave,waveTypeFromInt(grid->cntWaves));
            

            
            waveListHead = insertWaveSorted(waveListHead,wave);
            

            
            grid->cntWaves++;
            grid->waveTimed->elapsed_since_last_event = 0;
            gameState = 0;
            
            
        }

        if(event == MLV_KEY && keyBoardButton == MLV_KEYBOARD_p && state == MLV_PRESSED) manaAddLevel(grid->player);
    
        monsterMove(grid);
        
        updateWavesAndSpawnMonsters(waveListHead, frametime,grid);
        updateGemsOnTowers(grid->towers,grid->num_towers,frametime);
        iterateUpdates(grid,frametime, compteur);
        updateWaveTimeEvent(grid,frametime,&waveListHead);
        removeExpiredWaves(&waveListHead);
        updateTimedElementalEvent(frametime,grid->monstersArr->array,grid->monstersArr->size,grid->way);
        clock_gettime(CLOCK_REALTIME, &new_time);
        frametime = new_time.tv_sec - end_time.tv_sec;
        frametime += (new_time.tv_nsec - end_time.tv_nsec) / 1.0E9;
        time += frametime;

        extratime = 1.0/60 - frametime;
        compteur = (compteur + 1) % 30;
        if(extratime > 0){
            MLV_wait_milliseconds((int)(extratime * 1000));
        }
    }
}