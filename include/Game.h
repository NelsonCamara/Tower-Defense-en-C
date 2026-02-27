#ifndef _GAME_
#define _GAME_
#include "Map.h"
#include "Inventory.h"
#include "Graphic.h"
#include <MLV/MLV_all.h>





void iterateUpdates(Grid *gameData, double frametime, int mustShot) ;


/*
*The game loop 
*Params
*   Grid *grid pointer to the grid
*   int tile_size the size of a tile of the grid for the graphic rendering
*Return
*   void
*
*/
void loop_test(Grid *grid, int tile_size,MLV_Input_box *box);



/**
 * Updates each wave in the linked list with the elapsed frame time and triggers monster spawning.
 * This function iterates through each wave in the list, updates its elapsed total time, and checks
 * if it's time to spawn monsters based on the elapsed time since the last event. If the elapsed time
 * since the last event is greater than or equal to the frequency, it triggers monster spawning and
 * displays the wave type.
 * 
 * Params:
 *   WaveNode *head - Pointer to the head of the linked list of waves.
 *   double frametime - The time elapsed in the current frame, used to update the wave timings.
 */
void updateWavesAndSpawnMonsters(WaveNode *head, double frametime,Grid *grid);


/**
 * Spawn a monster on the way of the grid with his stats from the struct Wave
 * Params:
 *  Grid *grid a pointer to the grid where the monster will spawn
 *  Wave *wave the wave of the monster
 * 
 * 
 */
void spawnMonster(Grid *grid,Wave *wave);


/**
 * Updates the times of the gems which are on a tower on the grid
 * Params
 *  Tower *towers the array of tower who contains the gems
 *  int cntTowers the number of towers
 *  float the frametime to add
 */
void updateGemsOnTowers(Tower *towers,int cntTowers,double frametime);

#endif