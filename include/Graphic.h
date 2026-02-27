#ifndef __GRAPHIC__
#define __GRAPHIC__

#include "PlayerEvents.h"
#include <MLV/MLV_all.h>
#include <string.h>

void drawGrid(Grid field,int taille_case);

void drawSideBar(int heightWindow,int widthWindow);

void drawMonster(int tailleCase,Grid grid);

void drawTower(int tailleCase,Grid grid,int i,int j);

void drawGem(int tailleCase,Grid grid,int i,int j,Color color);

void drawNewGemButton();

void drawGetLevelBox(MLV_Input_box *box);

void drawNewLevelButton();

void drawNewTower();

void drawInputText(char * text);

int clickOnNewGemButton(int xClick,int yClick,int tailleCase);

int clickOnNewLevelButton(int xClick,int yClick,int tailleCase);

int clickOnTowerButton(int xClick,int yClick,int tailleCase);


Point* clickOnGridCase(int xClick,int yClick,int tailleCase);

void drawZone(int tailleCase,Point pos);

void drawInventory(int tailleCase);

int clickOnInventory(int xClick,int yClick);

void draw_allInit(Grid gameData, int tile_size,MLV_Input_box *box);

void draw_all(Grid gameData, int tile_size,MLV_Input_box *box,char *boxText,int gameState);


MLV_Color detEntityColor(Color entityColor);


void drawMonsterHealthBar(float health,MLV_Color color);

void drawPlayerStats(Player player);

void drawShot(ShootArray arr, int tile_size, int offset);

void drawMonsters(Grid gameData, int tile_size);

void drawAllTowers(int tailleCase,Grid grid);
#endif