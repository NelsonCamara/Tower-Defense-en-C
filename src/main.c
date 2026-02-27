#include <stdio.h>
#include <stdlib.h>
#include "ManageFramerate.h"
#include "Tower.h"
#include "Game.h"

int main(void){
    Grid field;
    MLV_Input_box *box;
    char* boxText;
    boxText= (char*) malloc( 1*sizeof(char) );
    boxText= "\0";
    srand((unsigned int)time(NULL));

    Manhattan(&field);
    field.monstersArr =initMonsterArray(100);

    MLV_create_window("towerdefense","towerdefense",1420,880);
    draw_allInit(field, 40,box);

    loop_test(&field, 40,box);
    MLV_update_window();
    deletegrid(&field);
    
    return 0;
}