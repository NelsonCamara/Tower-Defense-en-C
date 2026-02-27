#ifndef __ENTITYMOVEMENTS__
#define __ENTITYMOVEMENTS__

#include "Game.h"





/*
* Generate a random number between 0.9 and 1.1
* Param :
*  none
* Return
*  double
*/
double monsterSpeedVariation();


/*
 Make all entity in the grid move to their next position

 Param:
    grid : A pointer to a grid
 Return:
    void
*/
void monsterMove(Grid * grid);

/*
 Make an entity on the grid move toward its direction.

 Param:
    monster : A pointer to a monster
 Return:
    void
*/
void updatePos(Monster *monster);
/*
 For a given monster, check if its direction is accorded to its 

 Param:
    way : A pointer to an array of point representing the monster's path
    monster : Pointer to a monster
 Return:
    void
*/
void updateDir(Point *way, Monster *monster);




/*
 Calculate distance between two  points.
   Despite the name of its parameters this is a generic calculation fonction
   it does not require a shoot or monster struct.
 
 Param:
   shotX : x position of the first point
   shotY : y position of the first point
   monsterX : x position of the second point
   monsterY : x position of the second point
 Return:
   double : the distance between the two points  
*/
double distanceCalculation(double shotX, double shotY, double monsterX, double monsterY);

/*
*Scan the surrounding of each gem and select the target for each gem, than shoot a new shot at the target
*Params:
*   Grid gameData;
*Return:
*   void   
*/
void gemShot(Grid *gameData);


int  shotDirection(Shoot *shot, Monster monster);
#endif