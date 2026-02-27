#include "Monster.h"
#include <stdlib.h>
#include <stdio.h>


void initializeMonster(Monster *monster,double posX,double posY,int intXPos,int intYPos,float monsterHealth,Element monsterElement,Color monsterColor,int tint,float speed,Direction dir){    
    Point *monsterPos;

    monsterPos = malloc(sizeof(Point));
    if(monsterPos != NULL){
        monsterPos->i = intXPos;
        monsterPos->j = intYPos;
        monster->posX = posX;
        monster->posY = posY;
        monster->posCaseMonster = monsterPos;
        monster->monsterHealth = monsterHealth;
        monster->monsterMaxHealth = monsterHealth;
        monster->monsterElement = monsterElement;
        monster->monsterColor = monsterColor;
        monster->speed = speed;
        monster->initialSpeed = speed;
        monster->direction = dir;
        monster->tint = tint;
        monster->elemEvent = NULL;
        monster->shootArray = initShotArray(10);
        return;
    }
    else {
        fprintf(stderr,"memory error in monsterPos allocation");
        exit(EXIT_FAILURE);
    }



    
}




MonsterArray* initMonsterArray(int sizeMax) {
    
    MonsterArray* arr = malloc(sizeof(MonsterArray));
    arr->array = (Monster*)malloc(sizeof(Monster) * sizeMax);
    arr->size = 0;
    arr->sizeMax = sizeMax;
    
    
    for (size_t i = 0; i < sizeMax; i++) {
        arr->array[i].posCaseMonster = NULL;
        arr->array[i].shootArray = NULL;
    }
   
    return arr;
}


void freeMonsterArray(MonsterArray *arr) {
    for (int i = 0; i < arr->size; i++) {
        free(arr->array[i].posCaseMonster);
        freeShotArray(arr->array[i].shootArray);
        free(arr->array[i].shootArray);
    }

    free(arr->array);
    arr->array = NULL;
    arr->size = 0;
    arr->sizeMax = 0;
}


void addElemMonsterArray(MonsterArray *arr, Monster *monster) {
     
    if (arr->size == arr->sizeMax) {
        arr->sizeMax *= 2;
        arr->array = (Monster *)realloc(arr->array, arr->sizeMax * sizeof(Monster));
    }

    arr->array[arr->size] = *monster;
    arr->size++;
}


void delElemAtIndexMonsterArray(MonsterArray *arr, int index) {
    if (arr->size > 0 && index < arr->size) {
      
        free(arr->array[index].posCaseMonster);
        freeShotArray(arr->array[index].shootArray);
        free(arr->array[index].shootArray);
        for (int i = index; i < arr->size - 1; i++) {
            arr->array[i] = arr->array[i + 1];
        }
        arr->size--;
    }
}


void showMonster(Monster monster){
    printf("-----------------------Monster---------------------------\n");
    printf("Monster float Pos %f|%f\n",monster.posX,monster.posY);
    printf("Monster int Pos %d|%d\n",monster.posCaseMonster->i,monster.posCaseMonster->j);
    printf("Monster health %0.2f\n",monster.monsterHealth);
    showElement(monster.monsterElement);
    showColor(monster.monsterColor);
    printf("Monster pos Chemin: %d\n",monster.posWay);
    printf("Monster speeed %0.2f\n",monster.speed);
    printf("Monster initial speed %0.2f\n",monster.initialSpeed);
    printf("Monster tint :%d\n",monster.tint);
    if(monster.elemEvent != NULL){
        
        showElementalEvent(*monster.elemEvent);
    } 
    

}

ElementalEvent* newElemEvent(double frametime,EventType type,Shoot* shoot){
    ElementalEvent *elemEvent;
    
    elemEvent = malloc(sizeof(ElementalEvent));
    if(elemEvent == NULL){
        fprintf(stderr,"MEM ERROR");
        exit(EXIT_FAILURE);
    }
    else{
        elemEvent->type = type;
        elemEvent->timedEvent = newTimedEvent(frametime,type);
        
        elemEvent->shootLevel = shoot->gem->level;
        elemEvent->shootTint = shoot->gem->tint;
        
        
        return elemEvent;
    }
}

int monsterHittedByShoot(Monster *monster,Shoot *shoot,double frametime){

    monster->monsterHealth -= applyDamage(shoot->gem->tint,monster->tint,shoot->gem->level);
    
    shoot->isTargetReached = true;
    if(monster->monsterHealth <= 0) return 0; 

    else {
        EventType type;
        if(monster->monsterElement == NO_ELEMENT )monster->monsterElement = shoot->gem->gemElement;
        switch (shoot->gem->gemElement)
        {
        case PYRO:
            switch (monster->monsterElement)
            {
            case PYRO:
                type = PYRO;
                monster->elemEvent = newElemEvent(frametime,type,shoot);

                break;

            case DENDRO:
                type = PYRO_AND_DENDRO;
                monster->elemEvent = newElemEvent(frametime,type,shoot);
                monster->monsterElement= UNDER_DOUBLE_EFFECT;
                break;
            
            case HYDRO:
                type = PYRO_HYDRO;
                monster->elemEvent = newElemEvent(frametime,type,shoot);
                monster->monsterElement= UNDER_DOUBLE_EFFECT;
                break;
            
            default:
                type = PYRO;
                break;
            }

            break;

        case DENDRO:
            type = DENDRO;
            switch (monster->monsterElement)
            {
            case PYRO:
                type = PYRO_AND_DENDRO;
                monster->elemEvent = newElemEvent(frametime,type,shoot);
                monster->monsterElement= UNDER_DOUBLE_EFFECT;
                break;

            case DENDRO:
                monster->elemEvent = newElemEvent(frametime,type,shoot);
                break;
            
            case HYDRO:
                type = DENDRO_HYDRO;
                monster->elemEvent = newElemEvent(frametime,type,shoot);
                monster->monsterElement= UNDER_DOUBLE_EFFECT;
                break;
            
            default:
                type = DENDRO;
                break;
            }
            break;

        case HYDRO:
            type= HYDRO;
            switch (monster->monsterElement)
            {
            case PYRO:
                type = PYRO_HYDRO;
                monster->elemEvent = newElemEvent(frametime,type,shoot);
                monster->monsterElement= UNDER_DOUBLE_EFFECT;
                break;

            case DENDRO:
                type = DENDRO_HYDRO;
                monster->elemEvent = newElemEvent(frametime,type,shoot);
                monster->monsterElement= UNDER_DOUBLE_EFFECT;
                break;
            
            case HYDRO:
                break;
            
            default:
                type = HYDRO;
                break;
            }
            break;
        
        default:
            break;
        }
     
        
        
        
        return 1;
    } 
}

WaveType waveTypeFromInt(int cntWaves){
    int randInt;
    randInt = MLV_get_random_integer(1,100);
    printf("TPE WAVE INT %d\n",randInt);
    if(randInt >=1 && randInt <= 10 ){
        if(cntWaves < 3) return waveTypeFromInt(cntWaves);
        else return BOSS;

    } 
    if(randInt >=10 && randInt <= 30) return AGILE;
    if(randInt >=30 && randInt <= 50) return FOULE;
    if(randInt >=50 && randInt <= 100) return BASE;
}


void showWaveType(WaveType type){
    printf("------------------WAVE TYPE---------------------\n");
    switch (type)
    {
    case BOSS:
        printf("BOSS\n");
        break;
    
    case AGILE:
    
        printf("AGILE\n");
        break;
    case FOULE:

        printf("FOULE\n");

        break;
    case BASE:
        printf("BASE\n");
        
        break;

    default:
        printf("HOULA\n");
        break;
    }
}

void initWave(Wave *wave,WaveType type){
    TimedEvent *ev;
    ev= malloc(sizeof(TimedEvent));
    if(ev != NULL){
        switch (type){
            case BOSS:
                wave->cntMonsters =2; 
                wave->speedMonsters = 1;
                ev->duration = 2;
                ev->active =true;
                ev->elapsed_since_last_event = 0;
                ev->elapsed_total=0;
                ev->frequency = 1;
                wave->spawnEvent = ev;
                wave->waveType = type;
                break;
    
            case AGILE:
                ev->duration = 24;
                ev->active =true;
                ev->elapsed_since_last_event = 0;
                ev->elapsed_total=0;
                ev->frequency = 2;

                wave->cntMonsters =12;
                wave->speedMonsters = 2;
                wave->spawnEvent = ev;
                wave->waveType = type;
                break;
            case FOULE:
                ev->duration = 24;
                ev->active =true;
                ev->elapsed_since_last_event = 0;
                ev->elapsed_total=0;
                ev->frequency = 1;
                wave->cntMonsters =24;
                wave->speedMonsters = 1;
                wave->spawnEvent = ev;
                wave->waveType = type;
                break;
            case BASE:
                ev->duration = 12;
                ev->active =true;
                ev->elapsed_since_last_event = 0;
                ev->elapsed_total=0;
                ev->frequency = 1;
                wave->cntMonsters =12;
                wave->speedMonsters = 1;
                wave->spawnEvent = ev;
                wave->waveType = type;
                break;

            default:
                break;
        }
        

    }


}

Wave* newWave(){
    Wave *tmp;
    int resRand;
    tmp = malloc(sizeof(Wave));
    if(tmp != NULL){
        resRand = MLV_get_random_integer(1,100);
        tmp->waveType = waveTypeFromInt(resRand);
        initWave(tmp,tmp->waveType);

        
    }
}


void showWave(Wave wave){
    printf("--------------------------WAVE---------------\n");
    showWaveType(wave.waveType);
    printf("Taille :%d\n",wave.cntMonsters);
    printf("Monsters Speed :%0.2f\n",wave.speedMonsters);
    showTimedEvent(*wave.spawnEvent);
}



WaveNode* createWaveNode(Wave *wave) {
    WaveNode *newNode = (WaveNode *)malloc(sizeof(WaveNode));
    if (newNode == NULL) {
        perror("Unable to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    newNode->wave = wave;
    newNode->next = NULL;
    return newNode;
}

WaveNode* insertWaveSorted(WaveNode *head, Wave *wave) {
    WaveNode *newNode = createWaveNode(wave);
    if (head == NULL || (head->wave->spawnEvent->duration - head->wave->spawnEvent->elapsed_total) >= (wave->spawnEvent->duration - wave->spawnEvent->elapsed_total)) {
        newNode->next = head;
        return newNode;
    }

    WaveNode *current = findInsertionPoint(head, wave);
    newNode->next = current->next;
    current->next = newNode;

    return head;
}




void freeWaveNode(WaveNode *node) {
    if (node != NULL) {
        free(node->wave); 
        free(node);       
    }
}


WaveNode* findInsertionPoint(WaveNode *head, Wave *newWave) {
    WaveNode *current = head;
    double newWaveTimeLeft = newWave->spawnEvent->duration - newWave->spawnEvent->elapsed_total;

    while (current->next != NULL && (current->next->wave->spawnEvent->duration - current->next->wave->spawnEvent->elapsed_total) < newWaveTimeLeft) {
        current = current->next;
    }

    return current;
}


void deleteWaveNode(WaveNode **head, WaveNode *nodeToDelete) {
    if (head == NULL || *head == NULL || nodeToDelete == NULL) {
        return;
    }

    if (*head == nodeToDelete) {
        *head = (*head)->next;
        freeWaveNode(nodeToDelete);
        return;
    }

    WaveNode *current = *head;
    while (current->next != NULL && current->next != nodeToDelete) {
        current = current->next;
    }

    if (current->next == nodeToDelete) {
        current->next = nodeToDelete->next;
        freeWaveNode(nodeToDelete);
    }
}

void removeExpiredWaves(WaveNode **head) {
    if (head == NULL || *head == NULL) {
        return;
    }

    WaveNode *current = *head;
    WaveNode *prev = NULL;

    while (current != NULL) {
        if (current->wave->spawnEvent->elapsed_total >= current->wave->spawnEvent->duration) {
            WaveNode *toDelete = current;

            current = current->next;
            deleteWaveNode(head, toDelete);

            if (*head == current) {
                prev = NULL;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}


void showWaveList(WaveNode *head) {
    WaveNode *current = head;
    printf("ICI\n");
    while (current != NULL) {
        showWave(*(current->wave));  
        current = current->next;
    }
}




