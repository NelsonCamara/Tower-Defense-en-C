#ifndef __MAP__
#define __MAP__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Utils.h"
#include "Tower.h"

/*
*This structure represents the Player
*Fields :
*   Gem *gems a list of gems
*   int mana the mana of the player
*   int levelMana the level of the player's mana stock
*   int cntGems the amount of Gems the player has
*   int manaMax the maximum amount of mana of the player 
*
*/


typedef struct Player
{
    Gem gems[9];
    int mana;
    int levelMana;
    int cntGems;
    int manaMax;
 
}Player;



typedef struct 
{
    /*
    Grid structure representing the game's field.
    Fields:
        Double dimension Point array for the grid.
        Integer for the width.
        Integer for the length.
        Point array for the monsters's way
        Integer for the length of this way
        Array of Tower for the Towers on the grid
    */
    Point **grid;
    int width;
    int length;
    Point *way;
    int size_way;
    Tower* towers;
    int num_towers;
    //Monster *monsters;
    //int monsterNumber;
    TimedEvent *waveTimed;
    int cntWaves;
    Player *player;
    Gem gems[9];
    int cntGems;
    MonsterArray * monstersArr;

    
}Grid;





/*
*Initialize a pointer to a player
*Params:
*   Player* player to initialize
*Return:
    void
*/
void initializePlayer(Player **player);

int min(int a, int b);
int dist(Point p1,Point p2);
void init_grid(Grid *grid);
void display_grid(Grid field);
Point coordToPoint(int i,int j);
void init_point(Point *point, int i, int j, Direction dir);
int dist_point_to_board3(Point point,Grid field);
int dist_point_to_board(Point point,Grid field);
int getRandomInteger(int min, int max);
void caseAleat(Grid field, Point *point);
int colisionWithWayOrEndOfMap(Point point,Grid field);
int extent(Grid field, Point origin, Direction direction);
int extentCurrentDir(Grid *grid ,Direction currentDir);
int max(int a,int b);
int caseToAddDirection(Direction direction ,int extentOfDirection);
Direction detNewDir(Grid field, Point origin) ;
void displayway(Grid *grid);
int checkway(Point *way,int sizeway);
void addNCases(Grid *grid, int N, Direction dir, int lastIndex);
void deletegrid(Grid *grid);
Direction getDir(Grid field, Point point);
void startOfway(Grid *grid, Point point);
void startManhattan(Grid *grid);
int makeway(Grid *grid, Direction currentDir);
void growway(Grid *grid);
void endway(Grid *grid);
int Manhattan(Grid *grid);
int equals(Point p1,Point p2);

/*Check if a Tower is within the grid dimensions
*Params:
*   Grid grid 
*   Tower tower
*Return:
*   Returns true if within and false if not
*
*
*/
bool isWithinGrid(Grid grid, Tower tower);


/*Check if a Tower is not inside the way of monster
*Params:
*   Grid grid 
*   Tower tower
*Return:
*   Returns true if not inside the way and false if yes
*
*/
bool isNotOnWay(Grid grid, Tower tower);

/*Check if a Tower is not placed on another tower of the grid
*Params:
*   Grid grid 
*   Point towerPos
*Return:
*   Returns true if position is not on another tower position  and false if yes
*
*/
bool isUniquePosition(Grid grid,Point towerPos);

/*Check if a Tower placement on the grid is Valid 
*Params:
*   Grid grid 
*   Tower tower
*Return:
*   Returns true if yes and false if not
*
*/
bool isValidTowerPlacement(Grid grid, Tower tower);



/**
 * Add a tower to the array of towers the grid
 * Param
 *  Grid *grid the grid to update
 *  Point towerPos the future position of the point
 * Returns
 *  void
 * 
 * */
void addTower(Grid *grid,Point towerPos);


/**
 * Setup an array of pointer to the elements in the array of gems in the inventory
 * Params
 *  Grid *grid who contains the array of gems needed
 *
 * 
 * */
void fillInventoryHolesCaller(Grid *grid);
#endif