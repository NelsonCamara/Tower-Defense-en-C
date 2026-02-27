#ifndef GEM_H
#define GEM_H

#include "Tint.h"
#include <stdbool.h>
/*
*The Gem structure,a gem can shoot a monster
*fields :
*   Color color the Type of the gem
*   Element gemElement The element of the gem
*   int tint the tint of the gem 
*   int level the level of the gem
*   Point the Position on the grid
*   int gemState 1 if on the grid 0 if in the inventory -1 if not in nowhere
*/
typedef struct 
{
    Color color;
    Element gemElement;
    int tint;
    int level;
    Point *gemPosition;
    float damage;
    int gemState;
}Gem;


Gem *newGem(int level);


/*
*Initialize the fields of a Gem's object pointer
*Params:
*   Gem* gem pointer the gem 
*   Color gemColor the future color of the gem
*   Element gemElement the element of the future gem
*   int tint the tint of the future gem

*Return:
*   void   
*/
void initializeGem(Gem *gem,Color gemColor,Element gemElement,int tint);




/*
*Print a gem in the console
*Param:
*   Gem gem the gem to print
*
*/
void showGem(Gem gem);

void showGems(Gem *gems,int cntGems);

/*
*Fusion two gems and their caracteristics
*Increment the level by one and the new tint is the median tint of the two gems
*The new gem is mixed if the two gems arent the same Color and arent mixed themselves
*   Params:
*       pointer to two Gems
*
*   Returns:
*       pointer to a Gem
*
*/

Gem* gemFusion(Gem* gemFirst,Gem* gemSecond);

/*
*Fusion two gems and their caracteristics only if they are the same level
*Increment the level by one and the new tint is the median tint of the two gems
*The new gem is mixed if the two gems arent the same Color and arent mixed themselves
*   Params:
*       pointer to two Gems
*
*   Returns:
*       1 if the fusion is ok 
*       0 if the fusion is not possible
*/
int gemFusion2(Gem *gemFirst,Gem *gemSecond);


/**
 * prevents holes in inventory gems
 * Params
 *  Gem **gems array of pointers to the gems 
 *  int cntGems the number of gems
 * Returns
 *  void
 * 
 * */
void fillInventoryHoles(Gem **gems, int cntGems);
#endif 
