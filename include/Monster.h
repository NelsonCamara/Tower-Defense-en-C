#ifndef MONSTER_H
#define MONSTER_H
#include <stdlib.h>
#include <stdio.h>
#include "Tint.h"
#include "Shoot.h"
#include <MLV/MLV_all.h>



/*
*The Monster structure
*   fields:
*       float posX the float position of the monster in the X axis
*       float posY the float position of the monster in the Y axis
*       Point posCaseMonster int position of the monster in the grid
*       int monsterHealth the health of the monster
*       A COMPLETER
*/

typedef struct Monster
{
    double posX;
    double posY;
    Point *posCaseMonster;
    float   monsterHealth;

    Element monsterElement;
    Color monsterColor;
    int posWay;
    float speed;
    float monsterMaxHealth;
    float initialSpeed;
    Direction direction;
    int tint;
    ElementalEvent *elemEvent;
    ShootArray *shootArray;
}Monster;




/*
*Struct reprensenting a array of Shoot element
*Fields :
*    Shoot* array an array of Shoot element
*    size_t size the number of element in the array;
*    size_t sizeMax the maximum number of Shoot that the array can contain
*/
typedef struct MonsterArray{
    Monster * array;
    size_t size;
    size_t sizeMax;
}MonsterArray;




/*
*initialize a dynamic array of monster 
*Params
*   int sizeMax : the desired max length of  
*Return
*   MonsterArray*
*/
MonsterArray* initMonsterArray(int sizeMax) ;

/*
* Free the memory allocated to a array of monster
*Params
*   MonsterArray *arr : a pointer to the array that need to be freed
*Return
*   void
*/
void freeMonsterArray(MonsterArray *arr) ;

/*
*initialize a dynamic array of monster 
*Params
*   MonsterArray *arr : a pointer to the array we'll add the monster to
*   Monster *monster : a pointer to the monster we will add 
*Return
*   void
*/
void addElemMonsterArray(MonsterArray *arr, Monster *monster);

/*
*initialize a dynamic array of monster 
*Params
*   MonsterArray *arr : a pointer to the array we'll add the monster to
*   Monster *monster : a pointer to the monster we will add 
*Return
*/
void delElemAtIndexMonsterArray(MonsterArray *arr, int index) ;

/*
*The type of monster wave
*   Boss more hp
*   Agile faster movespeed
*   foule more monsters
*   Base basic wave
*/
typedef enum{
    BOSS,
    AGILE,
    FOULE,
    BASE

}WaveType;

void showWaveType(WaveType waveType);
WaveType waveTypeFromInt(int cntWaves);

/*
*the structure who represent a wave of monsters
*Fields
*   WaveType type the type of the wave
*   int cntMonster the nb of Monsters in the wave
*   double speedMonsters the speed of the monsters in the wave
*/

typedef struct Wave
{
    WaveType waveType;
    int cntMonsters;
    double speedMonsters;
    TimedEvent *spawnEvent;
}Wave;

void showWave(Wave wave);
/*
*Initialize a wave from a WaveType 
*Params
*   Wave *wave a pointer to a wave to initialize
*   WaveType type the type of the future wave
*  
*   
*
*/
void initWave(Wave *wave,WaveType type);

/*
*Return
*   pointer to a new wave
*/
Wave* newWave(void);

void showMonster(Monster monster);

/*
*Initialize the fields of a Monster structure
*Params:
*   Monster* monster pointer to the monster to initialize 
*   float posX the float position in the X axis
*   float posY the float position in the Y axis 
*   int intXPos the int position in the X axis
*   int intYPos the int position in the Y axis
*   float monsterHealth the health of the monster
*   bool isOnTheWay true if the Monster in on the way of the grid and false if not
*   Color monsterColor The color of the monster
*   int tint the tint of the monster
*Returns:
*   void
*/
void initializeMonster(Monster *monster,double posX,double posY,int intXPos,int intYPos,float monsterHealth,Element monsterElement,Color monsterColor,int tint,float speed,Direction dir);



/*
*Initialize a new ElementalEvent 
*Params
*   double frametime the time of the actual frame at the initialisation
*   EventType type the type of the event
*Return
*   ElementalEvent* pointer to the ElementalEvent object initialized
*
*
*/
ElementalEvent* newElemEvent(double frametime,EventType type,Shoot *shoot);




/*
*Do the operations needed when a monster is hit by a shoot
*Params:
*   Monster *monster the monster hitted
*   Shoot *shoot the shoot who hit the monster
*Returns:
*   int 1 if the monster is still alive
*   int 0 if the monster died

*/
int monsterHittedByShoot(Monster *monster,Shoot *shoot,double frametime);


/*
*Linked list of Waves structure
*/
typedef struct WaveNode {
    Wave *wave;
    struct WaveNode *next;
} WaveNode;

/*
 * Creates a new WaveNode node.
 * 
 * Params:
 *   Wave *wave - Pointer to a Wave structure to be stored in the node.
 * 
 * Returns:
 *   WaveNode* - A pointer to the newly created WaveNode.
 */

WaveNode* createWaveNode(Wave *wave); 

/*
 * Inserts a Wave into the linked list in a sorted manner based on the time left to spawn the wave.
 * 
 * Params:
 *   WaveNode *head - Pointer to the head of the linked list.
 *   Wave *wave - Pointer to the Wave structure to be inserted.
 * 
 * Returns:
 *   WaveNode* - The head of the modified linked list.
 */

WaveNode* insertWaveSorted(WaveNode *head, Wave *wave);

/*
 * Finds the appropriate insertion point in the linked list for a new Wave based on the time left for spawning.
 * 
 * Params:
 *   WaveNode *head - Pointer to the head of the linked list.
 *   Wave *newWave - Pointer to the new Wave structure to be inserted.
 * 
 * Returns:
 *   WaveNode* - Pointer to the node after which the new node should be inserted.
 */

WaveNode* findInsertionPoint(WaveNode *head, Wave *newWave);

/*
 * Deletes a specified node from the linked list.
 * 
 * Params:
 *   WaveNode **head - Double pointer to the head of the linked list.
 *   WaveNode *nodeToDelete - Pointer to the node to be deleted.
 */

void deleteWaveNode(WaveNode **head, WaveNode *nodeToDelete);


/*
 * Removes all expired waves from the linked list based on their elapsed total time.
 * 
 * Params:
 *   WaveNode **head - Double pointer to the head of the linked list.
 */

void removeExpiredWaves(WaveNode **head);


/*
 * Prints the details of each Wave in the linked list.
 * 
 * Params:
 *   WaveNode *head - Pointer to the head of the linked list.
 */
void showWaveList(WaveNode *head);




#endif 
