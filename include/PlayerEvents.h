#ifndef __PLAYEREVENTS__
#define __PLAYEREVENTS__

#include "EntityMovements.h"
#include <MLV/MLV_all.h>




/*
*Apply and update effects of timed events 
*
*
*
*
*
*/


void updateTimedElementalEvent(double frametime,Monster *monsters,int cntMonsters,Point *monstersWay);




/*
*Show the stats of a player
*Params:
*   Player player
*Return:
*   void
*
*/
void showPlayer(Player player);


/*
*Add a gem to the player
*Params:
*   Player *player pointer to the player
*   Gem gem the gem to add
*
*/
void addGem(Player *player,Gem gem);


/**
 * Determine the cost of a new gem
 * Params 
 *  int level the level of the new gem
 * Returns
 *  int the cost 
 * 
 * */
int gemCost(int level);


/*
*Add a level to the stock of mana of the player
*Params:
*   Player *player pointer to the player
*
*
*/
void manaAddLevel(Player *player);


/*
*Calculate the mana the player get when a monster is killed
*the player get 10% of the initial health points of the monster    
*Params
*   int maxHPMOnster the maximum HP of the monster
*   Player *player a pointer to the player
*Returns:
*   void
*/
void monsterKilledMana(int maxHPMonster,Player *player);


/*
*If a monster survived the way the mana of the player decrease
*Params
*   int maxHPMonster the maximum HP of the monster
*   Player *player A pointer to the player
*Returns:
*   -1 if the player cant afford this mana amount and lost the game
*    0 if the player can afford this mana amount
*/
int monsterSurvivedTheWay(int maxHPMOnster,Player *player);

/**
 * Determine the mana the player get when forcing a new wave
 * Param
 *  Grid *grid pointer to the grid who contain all the info on the game
 */


void newWaveForcedMana(Grid *grid);

/*
*Apply a Pyro event
*The Pyro event make damage to monster that are in a determined zone around the hitPoint
*Params
*   Monster *monster list of monsters
*   int cntMonsters the amount of monsters 
*   Point centerPoint the hitPoint
*   Point *monstersWay a pointer to the way of monster
*Returns 
*   void
*/
void applyPyro(Monster *monsters,float centerXPoint,float centerYPoint,int cntMonsters,int shootTint,int shootLevel );

void applyPyroXHydro(Monster *monsters,float centerXPoint,float centerYPoint,int cntMonsters,int shootTint,int shootLevel,Monster *hittedMonster);


/*
*Update the timed waves of monster events
*If the time elapsed since the last wave is equal to 35 the time is reset to zero
*Param
*   TimedEvent *event pointer to the timed event of waves
*Returns
*   void
*
*
*/
void updateWaveTimeEvent(Grid *grid,double frametime,WaveNode **head);



/**
 * Determine the price of a new tower and decrease the mana price from the player's mana stock
 * Param
 *  Grid *grid the pointer to the grid
 * Returns 
 *  void
 * 
 * */
void newTowerManaPrice(Grid *grid);





/**
 * Determine if the player has enough mana to buy a tower
 * Param
 *  Grid grid
 * Returns
 *  1 if the player has enough mana
 *  0 if the player hasnt enough mana
 * 
 * 
 * */
int enoughManaTower(Grid grid);



/**
 * Add a gem on a tower of the grid
 * Params:
 *  Grid *grid the pointer to the grid who contain the Towers
 *  Gem *gem pointer to the gem to add
 *  Point *point pointer to the future position of the gem
 * Returns:
 *  0 if the gem correctly added
 *  1 if a gem is already on the tower and the gem couldnt be added
 * */
int addGemOnTower(Grid *grid,Gem *gem,Point *point);


#endif