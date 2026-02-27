#include "Shoot.h"
#include<stdio.h>
#include <stdlib.h>


void initializeShoot(Shoot* shoot,double xTarget,double yTarget,Gem* gem,bool isTargetReached,double xPosition,double yPosition){
    
    if(shoot != NULL){
        if(gem != NULL){
            
            shoot->gem =gem;
            
            shoot->xTarget = xTarget;
            shoot->yTarget = yTarget;
            shoot->isTargetReached = isTargetReached;
            shoot->xPosition = xPosition;
            shoot->yPosition = yPosition;
        }
    }
}
Shoot initializeShoot2(double xTarget, double yTarget, Gem* gem, double xPosition, double yPosition) {
    Shoot tmp;
    if (gem != NULL) {
        tmp.gem = gem;
        tmp.xTarget = xTarget;
        tmp.yTarget = yTarget;
        tmp.isTargetReached = false;
        tmp.xPosition = xPosition;
        tmp.yPosition = yPosition;
    }
    return tmp;
}

ShootArray * initShotArray(int sizeMax) {
    ShootArray* arr = malloc(sizeof(ShootArray));;
    arr->array = (Shoot *)malloc(sizeof(Shoot) * sizeMax);
    arr->size = 0;
    arr->sizeMax = sizeMax;
    return arr;
}

void freeShotArray(ShootArray *arr ){
    free(arr->array);
    arr->array = NULL;
    arr->size = 0;
    arr->sizeMax = 0;
}

void addElemShotArray(ShootArray *arr, Shoot shot){
    if (arr->size == arr->sizeMax) {
        arr->sizeMax *= 2;
        arr->array = (Shoot *)realloc(arr->array, arr->sizeMax * sizeof(Shoot));         
    }
    arr->array[arr->size] = shot;
    arr->size++;
}


void delElemAtIndexShotArray(ShootArray *arr, int index) {
    if (arr->size > 0 && index < arr->size) {
        for (int i = index; i < arr->size - 1; i++) {
            arr->array[i] = arr->array[i + 1];
        }
        arr->size--;
    }
}



float applyDamage(int tintShoot,int tintTarget,int levelShoot){
    
    float d = 30.0;
    float res;
    res = d*pow(2.0,levelShoot)*(1-(cosf(tintShoot-tintTarget)/2));
    return res;
}


void showShoot(Shoot shoot){
    printf("-------------SHOOT----------\n");
    printf("Target xPos :%0.2f\n",shoot.xTarget);
    printf("Target yPos :%0.2f\n",shoot.yTarget);
    printf("Shoot xPos :%0.2f\n",shoot.xPosition);
    printf("Shoot yPos :%0.2f\n",shoot.yPosition);
    printf("Shoot from :\n");
    showGem(*shoot.gem);

}



