#ifndef UTILS_H
#define UTILS_H
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef enum {
    /*
    Enumerative structure to implement directions.
    */
    NORTH,  
    SOUTH,   
    EAST,   
    WEST,
    NO_DIR  
} Direction;


typedef struct
{
    /*
    Point structure representing a point with its fields i, j.
    The field case_grid simulates the state of the square.
    */
    char case_grid;
    int i;
    int j;
    Direction dir;
}Point;


/*
*This structure represents timed events 
*fields
*   double frequency The time within occurencies of the event ex: hp decreasing each 2.5 seconds
*   double duration  The total duration of the event in seconds
*   double elapsed_since_last_event the time elapsed since the last occurence of this event
*   double elapsed_total The time elapsed since the event has started
*   bool active if the event is active or not
*
*/
typedef struct TimedEvent {
    double frequency; 
    double duration; 
    double elapsed_since_last_event; 
    double elapsed_total; 
    bool active; 
} TimedEvent;


void showTimedEvent(TimedEvent tEv);


/*
*This enumerative structure represents the type of an event (PYRO,DENDRO,HYDRO)
*/
typedef enum {
    EVENT_TYPE_PYRO,
    EVENT_TYPE_DENDRO,
    EVENT_TYPE_HYDRO,
    PYRO_AND_DENDRO,
    PYRO_HYDRO,
    DENDRO_HYDRO,



}EventType;

void showEventType(EventType type);


/*
*This structure represent an ElementalEvent and his action
*Fields
*   TimedEvent timedEvent Manage the timed part of the event
*   EventType type the type of the event
*   double damage the damage of the ElementalEvent 
*   int radius    the eventual radius of the zone of the event
*   double slowFactor the slowing rate 
*   int shootTint the tint of a shoot is needed to get the damage for the other monster hitted by the effect
*/


typedef struct ElementalEvent{
    TimedEvent *timedEvent; 
    EventType type;         
    int shootTint;
    int shootLevel;   
    
} ElementalEvent;


void showElementalEvent(ElementalEvent event);




/*
*Initialize a new TimedEvent 
*Params
*   double frametime the time of the actual frame at the initialisation
*   EventType type the type of the event
*Return
*   TimedEvent* pointer to the TimedEvent object initialized
*
*
*/
TimedEvent* newTimedEvent(double frametime,EventType type);


/*
*Determine if a Point is within a zone
*Params
*   Point checkPoint the point to check
*   Point centerPoint the center of the zone
*   int radiusZone the radius of the zone
*Returns
*   0 if the point is in the zone
*   1 if the point isnt in the zone
*
*/
int pointInZone (Point checkPoint,Point centerPoint,int radiusZone);





/*
*Determine if a float position if within a zone of float positions
*Params
*   float xPos
*   float yPos
*   float centerPointX
*   float centerPointY
*   float radiusZone
*
*Returns
*   0 if the point is in the zone
*   1 if the point isnt in the zone
*/
int posFlInZone(float xPos,float yPos,float centerPointX,float centerPointY,float radiusZone);



/*
*Compare to float positions
*Params
*   float p1X the position in the X axis of the first point
*   float p1Y the position in the Y axis of the second point
*   float p2X the position in the X axis of the second point
*   float p2Y the position in the Y axis of the second point
*
*Returns
* 0 if same position
* 1 if not
*/

int compareFlPoints(float p1X,float p1Y,float p2X,float p2Y);


/**
 * Check if a point is on the way of monsters or not
 * Params
 *  Point point the point to check 
 *  Point *way An array of points which represents the way of monsters
 * Returns
 *  1 if on the way
 *  O if not on the way
 * 
 * */
int pointInWay(Point point,Point *way,int taille);


/**
 * Check if a char contain only digits
 * Param   
 *  the char to analyse
 * Returns
 *  true if only digits and false if not
 * 
 * */
bool isAllDigits(const char *str);





#endif 