#include "Graphic.h"

void drawGrid(Grid field,int taille_case){
    /*
        Draw the grid in a MLV window
        Parameter:
            Grid object grid.
            Int taille_case size of the element in the mlv window
    */
   int i,j;
   int specialWayCase=0;
   for(i=0;i<field.width;i++){
       for(j=0;j<field.length;j++){
           specialWayCase =0;
           if(field.grid[i][j].case_grid == '-'){
               
               MLV_draw_filled_rectangle(i*taille_case,j*taille_case,taille_case,taille_case,MLV_COLOR_SKY_BLUE);
               MLV_draw_rectangle(i*taille_case,j*taille_case,taille_case,taille_case,MLV_COLOR_BLACK);

           }
           if(field.grid[i][j].case_grid == 'X'){
               
               if(equals(field.grid[i][j],field.way[0])== 1){
                   specialWayCase =1;
                   
                   MLV_draw_filled_rectangle(i*taille_case,j*taille_case,taille_case,taille_case,MLV_COLOR_RED);
                   MLV_draw_rectangle(i*taille_case,j*taille_case,taille_case,taille_case,MLV_COLOR_BLACK);
               }
               if(equals(field.grid[i][j],field.way[field.size_way-1])== 1){
                   specialWayCase =1;
                   MLV_draw_filled_rectangle(i*taille_case,j*taille_case,taille_case,taille_case,MLV_COLOR_GREEN1);
                   MLV_draw_rectangle(i*taille_case,j*taille_case,taille_case,taille_case,MLV_COLOR_BLACK);
               }
               if(specialWayCase == 0){
                   MLV_draw_filled_rectangle(i*taille_case,j*taille_case,taille_case,taille_case,MLV_COLOR_WHITE);
                   MLV_draw_rectangle(i*taille_case,j*taille_case,taille_case,taille_case,MLV_COLOR_BLACK);

               }
           }
       }
   }
}


void drawSideBar(int widthWindow,int heightWindow){
    MLV_draw_filled_rectangle(widthWindow-300,0,300,heightWindow,MLV_COLOR_GREY);
}

void drawMonster(int tailleCase,Grid grid){
    MLV_draw_filled_circle((grid.way[1].i*tailleCase)+tailleCase/2,(grid.way[1].j*tailleCase)+tailleCase/2,tailleCase/4,MLV_COLOR_RED);
}

void drawZone(int tailleCase,Point pos){
    MLV_draw_circle((pos.i*tailleCase)+tailleCase/2,(pos.j*tailleCase)+tailleCase/2,3*tailleCase,MLV_COLOR_BLACK);
}

void drawTower(int tailleCase,Grid grid,int i ,int j ){
    MLV_draw_filled_rectangle((i*tailleCase)+tailleCase/4,(j*tailleCase)+tailleCase/4,tailleCase/2,tailleCase/2,MLV_COLOR_BLACK);
}


void drawGem(int tailleCase,Grid grid,int i,int j,Color color){
    MLV_draw_filled_circle(((i*tailleCase)+tailleCase/4)+(tailleCase/4),((j*tailleCase)+tailleCase/4)+(tailleCase/4),tailleCase/6,detEntityColor(color));

}

void drawAllTowers(int tailleCase,Grid grid){
    if(grid.num_towers == 0){
        return;
    }
    for(int i =0;i< grid.num_towers;i++){
        drawTower(tailleCase,grid,grid.towers[i].posTower->i,grid.towers[i].posTower->j);
        drawZone(tailleCase,*grid.towers[i].posTower);
        if(grid.towers[i].gem !=NULL){
            drawGem(tailleCase,grid,grid.towers[i].posTower->i,grid.towers[i].posTower->j,grid.towers[i].gem->color);
        }
    }
}

void drawNewGemButton(){
    int xSideBar = 1120;
    int ySideBar = 0;


    const char* text = "New Gem";
    MLV_draw_filled_rectangle(xSideBar+50,ySideBar+25,200,100,MLV_COLOR_BLACK);
    MLV_draw_text(xSideBar+120,ySideBar+60,text,MLV_COLOR_WHITE);
}

int clickOnNewGemButton(int xClick,int yClick,int tailleCase){
    int xSideBar = 1120;
    int ySideBar = 0;
    int xButton = xSideBar+50;
    int yButton = ySideBar+25;
    int widthButton = 200;
    int heightButton = 100;
    if((xClick >= xButton && xClick <= xButton+widthButton)&& (yClick >= yButton && yClick <= yButton+heightButton)){
        printf("GEM BUTTON\n");
        return 0;
    }
    else{
        return 1;
    }
}

void drawGetLevelBox(MLV_Input_box *box){
    int xSideBar = 1120;
    int ySideBar = 0;
    const char* text = "LEVEL OF GEM :";
    int xPos = xSideBar+50;
    int yPos = ySideBar +200;
    MLV_Color border = MLV_COLOR_BLACK;
    MLV_Color textColor = MLV_COLOR_BLACK;
    MLV_Color backgroundColor= MLV_COLOR_WHITE;
    box = MLV_create_input_box(xPos,yPos,200,100,border,textColor,backgroundColor,text);
    MLV_draw_input_box(box);
}

void drawNewLevelButton(){
    int xSideBar = 1120;
    int ySideBar = 0;


    const char* text = "Confirm level";
    MLV_draw_filled_rectangle(xSideBar+50,ySideBar+300,200,50,MLV_COLOR_BLACK);
    MLV_draw_text(xSideBar+100,ySideBar+320,text,MLV_COLOR_WHITE);
}

int clickOnNewLevelButton(int xClick,int yClick,int tailleCase){
    int xSideBar = 1120;
    int ySideBar = 0;
    int xButton = xSideBar+50;
    int yButton = ySideBar+300;
    int widthButton = 200;
    int heightButton = 50;
    if((xClick >= xButton && xClick <= xButton+widthButton)&& (yClick >= yButton && yClick <= yButton+heightButton)){
        printf("Level BUTTON\n");
        return 0;
    }
    else{
        return 1;
    }
}









void drawNewTower(){
    const char* text = "New Tower";
    int xSideBar = 1120;
    int ySideBar = 0;
    MLV_draw_filled_rectangle(xSideBar+50,ySideBar+425,200,100,MLV_COLOR_BLACK);
    MLV_draw_text(xSideBar+110,ySideBar+460,text,MLV_COLOR_WHITE);
}

int clickOnTowerButton(int xClick,int yClick,int tailleCase){
    int xSideBar = 1120;
    int ySideBar = 0;
    int xButton = xSideBar+50;
    int yButton = ySideBar+425;

    if((xClick >= xButton && xClick <= xButton+200)&& (yClick >= yButton && yClick <= yButton+100)){
       
        return 0;
    }
    else{
        return 1;
    }
}


void drawInputText(char * text){
    int xSideBar = 1120;
    int ySideBar = 0;
    int xPos = xSideBar+50;
    int yPos = ySideBar +200;
    MLV_draw_text(xPos+110,yPos+43,text,MLV_COLOR_BLACK);

}

void drawPlayerStats(Player player){
    int xSideBar = 1120;
    int ySideBar = 0;   
    int xPos = xSideBar+50;
    int yPos = ySideBar + 560;
    char manaStat[50];
    char manaLevelStat[50];
    char maxManaStat[50];

    snprintf(manaStat, sizeof(manaStat), "MANA: %d", player.mana);
    snprintf(manaLevelStat, sizeof(manaLevelStat), "MANA LEVEL: %d", player.levelMana);
    snprintf(maxManaStat, sizeof(maxManaStat), "MAX MANA: %d", player.manaMax);

    MLV_draw_text(xPos, yPos, manaStat, MLV_COLOR_BLACK);
    MLV_draw_text(xPos, yPos + 15, manaLevelStat, MLV_COLOR_BLACK);
    MLV_draw_text(xPos, yPos + 30, maxManaStat, MLV_COLOR_BLACK);
}

void drawInventory(int tailleCase){
    int xSideBar = 1120;
    int ySideBar = 0;   
    int xInv = xSideBar+50;
    int yInv = ySideBar+660;
    int witdhInv = 210; 
    int heightInv = 210;
    MLV_draw_filled_rectangle(xInv,yInv,witdhInv,heightInv,MLV_COLOR_BLACK);

    for(int i =0;i<3;i++){
        MLV_draw_line(xInv,yInv+i*70,xInv+witdhInv,yInv+i*70,MLV_COLOR_WHITE);
    }
    
    for(int j =0;j<3;j++){
        MLV_draw_line(xInv+j*70,yInv,xInv+j*70,yInv+heightInv,MLV_COLOR_WHITE);
    }

}

void drawGemsInInventory(Grid grid){
    int xGemInv,yGemInv;
    int xSideBar = 1120;
    int ySideBar = 0;   
    int xInv = xSideBar+50;
    int yInv = ySideBar+660;
    char gemLevelStr[5];
    if(grid.cntGems == 0) return;
    for(int i =0;i< grid.cntGems;i++){
     
        xGemInv = i%3;
        yGemInv = i/3;
        sprintf(gemLevelStr,"%d",grid.gems[i].level);
        MLV_draw_filled_ellipse((xInv+(xGemInv*70)/2)+(xGemInv+1)*35,(yInv+(yGemInv*70)/2)+(yGemInv+1)*35,15,20,detEntityColor(grid.gems[i].color));
        MLV_draw_text((xInv+(xGemInv*70)/2)+(xGemInv+1)*35-15,(yInv+(yGemInv*70)/2),gemLevelStr,MLV_COLOR_WHITE);
        memset(gemLevelStr, '\0', sizeof(gemLevelStr));
        
        
    }    
}

int clickOnInventory(int xClick,int yClick){
    int xSideBar = 1120;
    int ySideBar = 0;   
    int xInv = xSideBar+50;
    int yInv = ySideBar+660;
    int iClick,jClick;
    if((xClick >= xInv && xClick <= xInv +210) && (yClick >= yInv && yClick <=yInv+210)){
        iClick = (xClick-xInv)/70;
        jClick = (yClick -yInv)/70;
        return iClick +(jClick*3);
    }
    return -1;
}


Point* clickOnGridCase(int xClick,int yClick,int tailleCase){
    Point *pClick;
    pClick = malloc(sizeof(Point));
    if(xClick <= 1120){
        pClick->i = xClick/tailleCase;
        pClick->j = yClick/tailleCase;
            return pClick;
    }
    else return NULL;



}



void draw_all(Grid gameData, int tile_size,MLV_Input_box *box,char *boxText,int gameState){
    MLV_clear_window(MLV_COLOR_WHITE);
    drawGrid(gameData, tile_size);
    drawSideBar(1420,880);
    drawNewGemButton();
    if(gameState == 1){
        drawNewLevelButton();
        drawGetLevelBox(box);
        drawInputText(boxText);
    }
    
    drawAllTowers(tile_size,gameData);
    drawNewTower();
    drawInventory(tile_size);
    drawGemsInInventory(gameData);
    drawPlayerStats(*gameData.player);
    drawMonsters(gameData, tile_size);
    MLV_update_window();
}

void draw_allInit(Grid gameData, int tile_size,MLV_Input_box *box){
    MLV_clear_window(MLV_COLOR_WHITE);
    drawGrid(gameData, tile_size);
    drawSideBar(1420,880);
    drawNewGemButton();
    
    drawNewTower();
    drawInventory(tile_size);
    drawPlayerStats(*gameData.player);
    drawMonsters(gameData, tile_size);
    MLV_update_window();

}

void drawShot(ShootArray arr, int tile_size, int offset){
    int i;
    
    for(i = 0; i< arr.size; i++){
        MLV_draw_filled_circle(arr.array[i].xPosition * tile_size + offset,arr.array[i].yPosition * tile_size + offset, 4, detEntityColor(arr.array[i].gem->color));
    }
}
void drawMonsters(Grid gameData, int tile_size){
    int i;
    int offset, healthBarWidth, healthBarX;
    offset = tile_size / 2;

    for(i = 0; i < gameData.monstersArr->size; i++){
        MLV_Color monsterColorGraph;

        healthBarWidth = (gameData.monstersArr->array[i].monsterHealth / gameData.monstersArr->array[i].monsterMaxHealth) * (tile_size - 5);

        healthBarX = (gameData.monstersArr->array[i].posX * tile_size + offset) - (healthBarWidth / 2);

        monsterColorGraph = detEntityColor(gameData.monstersArr->array[i].monsterColor);

        MLV_draw_filled_circle(gameData.monstersArr->array[i].posX * tile_size + offset, gameData.monstersArr->array[i].posY * tile_size + offset, tile_size / 2 - 5, monsterColorGraph);

        MLV_draw_filled_rectangle(healthBarX, gameData.monstersArr->array[i].posY * tile_size - (tile_size / 4), healthBarWidth, (tile_size / 4), monsterColorGraph);

        drawShot(*(gameData.monstersArr->array[i].shootArray), tile_size, offset);
    }
}



MLV_Color detEntityColor(Color entityColor){
    switch (entityColor)
    {
    case  RED:
        return MLV_COLOR_RED;
    
    case  BLUE:
        return MLV_COLOR_CORNFLOWER_BLUE;
    case  GREEN:
        return MLV_COLOR_GREEN;
    case  MIXED:

        return MLV_COLOR_NAVAJOWHITE1;    
    default:
  
        return MLV_COLOR_BLACK;
    }
}


