#ifndef TOWER_H
#define TOWER_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Monster.h"
#include "Gem.h"
#include <time.h>

/*
*The tower structure:
*   Field:
*       Point posTower the position of the tower
*       Point shootZone[48] arrayof points which represents the area where the gem on the tower can shoot
*       Boolean isGemActive Boolean which equals true if the gem on the tower is active and false if not
*       Struct timespec containGemSince contain a delta time since the gem is on the tower
*/
typedef struct 
{
    Point *posTower;
    Point shootZone[48]; //Radius for shoot is 3+1 for the diagonal then a square of 7x7 
    bool  isGemActive;
    double containGemSince;
    Gem *gem;
}Tower;


void showTower(Tower tower);
/*
*Initialize the fields of a Tower object's pointer
*Params:
*   Tower* Pointer to a Tower
*   int posX posY position of the tower
*
*
*
*/
void initializeTower(Tower *tower, int posX, int posY);


/*
*Determine a zone of Points that the Tower can reach with a Gem
*
*Params:
*   Tower the tower
*   Point shootZone The array who represent the zone to determine
*
*Return:
*   void
*/
void detTowerShootZone(Tower tower,Point shootZone[48]);

/*
*Fill a 3X3 Square of Points without the center Point
*
*Params:
*   Point center to avoid
*   Point square the square to fill
*
*
*
*/
void fillSquare(Point center, Point square[48]);

/*
*Determine if a gem on a tower could be active or not
*
*Params:
*   Tower* tower Pointer to the tower
*
*
*Return:
    true if active since 2 seconds and false if not
*/
bool isGemActiveForTwoSeconds(Tower *tower);

/* 
*Reset a tower to her initial state
*   Param:
*       Tower* tower pointer to the tower
*   
*/

void resetTowerState(Tower *tower);


/**
 * Finds the monster with the highest health within the shooting zone of a given tower.
 *
 * Params:
 *  tower - The tower whose shooting zone is to be checked.
 *  monsters - An array of monsters to be checked.
 *  numMonsters - The number of monsters in the array.
 *
 * Return:
 *  Returns a pointer to the monster with the highest health in the shooting zone.
 *  If no monster is found in the shooting zone, returns NULL.
 */
Monster* findStrongestMonsterInZone(Tower tower, Monster monsters[], int numMonsters);




#endif