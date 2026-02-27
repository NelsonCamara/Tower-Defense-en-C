#include "Gem.h"
#include <stdio.h>
#include <stdlib.h>

void initializeGem(Gem *gem,Color gemColor,Element gemElement,int tint){
    Point *gemPos = malloc(sizeof(Point));
    if(gemPos != NULL){
        gem->color = gemColor;
        printf("ici\n");
        gem->gemElement = gemElement;
    
        gem->tint = tint;
 
        gem->damage = 0.0;
        gem->gemPosition = gemPos;

        
    }
    else {
        fprintf(stderr,"memory error in gemPos allocation");
        exit(EXIT_FAILURE);
    }

    
}


void showGem(Gem gem){

    printf("--------------------------------------------GEM--------------------------------------------\n");
    showColor(gem.color);
    showElement(gem.gemElement);
    printf("Tint:%d\n",gem.tint);
    printf("Level:%d\n",gem.level);
    printf("Position %d|%d\n",gem.gemPosition->i,gem.gemPosition->j);
    
}


Gem* gemFusion(Gem* gemFirst,Gem* gemSecond){
    if(gemFirst != NULL && gemSecond != NULL){
        gemFirst->level++;
        gemFirst->tint = (gemFirst->tint + gemSecond->tint)/2;
        if(gemFirst->color == gemSecond->color && gemFirst->color != MIXED){
            gemSecond = NULL;
            return gemFirst;
        }
        gemSecond = NULL;
        return gemFirst;
    }
    else{
        printf("one of the gem or both is/are NULL\n");
        return NULL;
    }
}

int gemFusion2(Gem *gemFirst,Gem *gemSecond){

        if(gemFirst->level == gemSecond->level){
            gemFirst->level++;
            gemFirst->tint = (gemFirst->tint + gemSecond->tint)/2;
            showGem(*gemFirst);
            if(gemFirst->color == gemSecond->color && gemFirst->color != MIXED){
                gemSecond->gemState = -1;
                return 1;
            }
            gemSecond->gemState = -1;
            gemFirst->color = MIXED;
            gemFirst->gemState = 0;
            return 1;

        }
        return 0;
    
}

Gem *newGem(int level){
    Gem *gem;
    Color gemColor;
    Element gemElem;
    gem = malloc(sizeof(Gem));

    if(gem == NULL){
        perror("gem allocation error\n");
        exit(EXIT_FAILURE);
    }
    
    gem->level = level;
    
    gemColor = aleatColor();
    int gemTint;
    switch (gemColor)
    {
    case RED:
        gemTint = aleatTint(RED);
        gemElem = PYRO;
        initializeGem(gem,gemColor,gemElem,gemTint);
        return gem;
    case BLUE:
        gemTint = aleatTint(BLUE);
        gemElem = HYDRO;
        initializeGem(gem,gemColor,gemElem,gemTint);
        return gem;
    case GREEN:
        gemTint = aleatTint(GREEN);
        gemElem = DENDRO;
        initializeGem(gem,gemColor,gemElem,gemTint);
        return gem;
    
    default:
        return NULL;
    }
}




void fillInventoryHoles(Gem **gems, int cntGems) {
    int i, j = 0;

    for (i = 0; i < cntGems; i++) {
        if (gems[i]->gemState == 0) {
            if (i != j) {
                gems[j] = gems[i];
            }
            j++;
        }
    }
    for (; j < cntGems; j++) {
        
        gems[j] = NULL;
    }
}


void showGems(Gem *gems,int cntGems){
    printf("-----------------------------------------------GEMS--------------------------------------\n");
    printf("nb Gemmes:%d\n",cntGems);
    if(cntGems == 0) return;
    for(int i=0;i<cntGems;i++) showGem(gems[i]);
}
