#ifndef SHOOT_H
#define SHOOT_H
#include "Utils.h"
#include "Tint.h"
#include "Gem.h"
#include <math.h>

/*
*The structure to represent a shoot
*Fields:
*   float xTarget the float position of the target in the X axis
*   float yTarget the float position in the Y axis
*   float xPosition the float position of the shoot in the X axis
*   float yPosition the float position of the shoot in the Y axis
*   Element shootElement the element of the shoot
*   Gem* gem a pointer to the gem from where the shoot comes
*   bool isTargetReached true if the shoot has reached his target and false if not
*/
typedef struct Shoot
{
    double xTarget;
    double yTarget;
    double xPosition;
    double yPosition;
    Gem *gem;
    bool isTargetReached;
}Shoot;

/*
*Struct reprensenting a array of Shoot element
*Fields :
*    Shoot* array an array of Shoot element
*    size_t size the number of element in the array;
*    size_t sizeMax the maximum number of Shoot that the array can contain
*/
typedef struct ShootArray{
    Shoot * array;
    size_t size;
    size_t sizeMax;
}ShootArray;

/*

*Initialize the fields of a ShootArray
*Params:
*   int sizeMax, the desired maximum size of the array
*Returns:
*   ShootArray*
*/
ShootArray *initShotArray(int sizeMax);

/*
*Free the struct 
*Params:
*    ShootArray * arr a pointer to a ShootArray
*Returns:
*   void
*/
void freeShotArray(ShootArray *arr );

/*
* Add an element at the end of the array
*Params:
*    ShootArray * arr a pointer to a ShootArray
*Returns:
*   void
*/
void addElemShotArray(ShootArray *arr, Shoot shot);

/*
* Delete the indexed element of the array
*Params:
*    ShootArray * arr a pointer to a ShootArray
*Returns:
*   void
*/
void delElemAtIndexShotArray(ShootArray *arr, int index);



void showShoot(Shoot shoot);

/*
*Initialize the fields of a Shoot structure
*Params:
*   float xTarget the float position of the target in the X axis
*   float yTarget the float position in the Y axis
*   float xPosition the float position of the shoot in the X axis
*   float yPosition the float position of the shoot in the Y axis
*   Element shootElement the element of the shoot
*   Gem* gem a pointer to the gem from where the shoot comes
*   bool isTargetReached true if the shoot has reached his target and false if not
*Returns:
*   void
*/
void initializeShoot(Shoot* shoot,double xTarget,double yTarget,Gem* gem,bool isTargetReached,double xPosition,double yPosition);


/*
*Determine the damages of a shoot
*Params
*   int tintShoot the tint of the shoot
*   int tintTarget the tint of the target
*   int levelShoot the level of the shoot
*Returns
*   float the damage result 
*
*/
float applyDamage(int tintShoot,int tintTarget,int levelShoot);

Shoot initializeShoot2(double xTarget, double yTarget, Gem* gem, double xPosition, double yPosition) ;

#endif 
