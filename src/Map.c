#include "Map.h"

void initializePlayer(Player **player){
    *player = malloc(sizeof(Player));
    if(*player == NULL){
        perror("Unable to allocate memory for new player");
        exit(EXIT_FAILURE);
    }
    (*player)->mana = 150;
    (*player)->manaMax = 2000;
    (*player)->levelMana = 1;
    (*player)->cntGems = 0;
}

int min(int a, int b) {
     /* Returns the smallest of two integers.
       Parameters:
           a: first integer.
           b: second integer.
       Return:
           the smallest integer.
    */
    return (a < b) ? a : b;
}

int dist(Point p1,Point p2){
    /*Calculate the Manhattan distance between two points.
        Paramètres:
            Two Points objects.
        Retour :
            Integer Distance of Manhattan. 
    */
    return abs(p1.i-p2.i)+abs(p1.j-p2.j);
}

void init_grid(Grid *grid){
    /*Create an empty grid.
        Parameter:
            pointer on a grid to create.
        
    */
    int i,j;
    
    grid->grid= (Point **)malloc(28*sizeof(Point *));
    grid->waveTimed = malloc(sizeof(TimedEvent));

    grid->waveTimed->frequency = 35;
    grid->waveTimed->elapsed_total = 0;
    grid->waveTimed->elapsed_since_last_event=0;
    grid->num_towers=0;
    grid->way = NULL;
    grid->size_way =0;
    grid->width = 28;
    grid->length=22;
    grid->cntWaves = 0;
    grid->cntGems = 0;
    grid->towers = NULL;
    initializePlayer(&(grid->player));
    for(i=0;i<grid->width;i++){
        grid->grid[i] = (Point*)malloc(22*sizeof(Point));
        for(j=0;j<grid->length;j++){
           
            grid->grid[i][j].case_grid ='-';
            grid->grid[i][j].i =i;
            grid->grid[i][j].j =j;
            grid->grid[i][j].dir =NO_DIR;


        }
    }
    
}


void display_grid(Grid field){
    /*Display the grid in the console.
        Paramètre:
            Grid object field.
    */
    int i,j;

    for(i=0;i<28;i++){
        for(j=0;j<22;j++){
            
            printf("%c",field.grid[i][j].case_grid);
            

        }
        printf("\n");
    }

}

Point coordToPoint(int i,int j){
    /* Takes two coordinates and returns a Point.
       Parameters:
           Two integers representing coordinates of the future point.
       Return:
           Returns a Point.
    */
    Point point;
    point.i = i;
    point.j = j;

    return point;
    

}



void init_point(Point *point, int i, int j, Direction dir) {
    /* Initializes a point.
       Parameters:
           Point point.
           Int i, a coordinate.
           Int j, a coordinate.
           Direction posNextPoint.
       Return:
           void
    */
    if (point != NULL) {
        point->i = i;
        point->j = j;
        point->case_grid = 'X'; 
        point->dir = dir;
    }
}




int dist_point_to_board3(Point point,Grid field){
    /* Checks the Manhattan distance between the point and the grid limits plus 3; the distance must be >= 3.
       Parameters:
           A point represented by its Point structure.
           A field represented by its Grid structure.
       Return:
           Returns a boolean indicating if the point is valid or not according to this condition.
    */
    int manDist;
    int manDistBis;
    int manDist2,manDist3;
    Point p1,p2,p3,p4;

    p1.i =0;
    p1.j =0;

    p2.i=field.width;
    p2.j = field.length;

    p3.i= 0;
    p3.j = field.length;

    p4.i = field.width;
    p4.j =0;

    manDist = dist(point,p1);
    manDistBis =dist(point,p2);
    manDist2 = dist(point,p3);
    manDist3 = dist(point,p4);



    if(manDist >= 3 && manDistBis >= 3 && manDist2 >=3 && manDist3 >=3){
        return 1;
    }
    return 0;
    
}

int dist_point_to_board(Point point,Grid field){
    /* Checks the Manhattan distance between the point and the grid limits; the distance must be >= 3.
       Parameters:
           A point represented by its Point structure.
           A field represented by its Grid structure.
       Return:
           Returns 0 if the point is within a Manhattan distance of 3 or less from the grid limits, and 1 if the point is inside the grid.
    */
    int manDist;
    int manDistBis;
    int manDist2,manDist3;
    Point p1,p2,p3,p4;

    p1.i =0;
    p1.j =0;

    p2.i=field.width-1;
    p2.j = field.length-1;

    p3.i= 0;
    p3.j = field.length-1;
    
    p4.i = field.width-1;
    p4.j =0;
    manDist = dist(point,p1);
    manDistBis =dist(point,p2);
    manDist2 = dist(point,p3);
    manDist3 = dist(point,p4);



    if(manDist >= 3 && manDistBis >= 3 && manDist2 >=3 && manDist3 >=3){
        


        return 1;
    }
    

    return 0;
    
}


int getRandomInteger(int min, int max) {
    /* Returns an integer between two integers.
       Parameters: 
           Two integers.
       Return:
           An integer.
    */
     int randomNum = min + rand() % (max - min + 1);

    return randomNum;
}



void caseAleat(Grid field, Point *point) {
    /* Modifies a point to be a random point in the grid at a distance from the edges of the grid.
       Parameters:
           field - an instance of the Grid structure.
           point - a pointer to an instance of the Point structure.
    */
    do {
        point->i = getRandomInteger(3, field.width - 4); 
        point->j = getRandomInteger(3, field.length - 4);
    } while (dist_point_to_board3(*point, field) != 1);
}


int colisionWithWayOrEndOfMap(Point point,Grid field){
    /* Detects a collision between a point and the edges of the map or the way.
       Parameters:
           point representing an object of the Point structure.
           field representing an object of the Grid structure.
       Return:
           Returns 0 if a collision has been detected and 1 if no collision has been detected.
    */
    int i;
    

    if(dist_point_to_board(point,field) == 1){
        if(field.size_way > 0){
            for(i=0;i<field.size_way;i++){
                if(dist(point,field.way[i]) <=2 && (field.size_way-1)-i > 2){
                    
                    
                    return 0;
                }
            }
            
            return 1;
        }
        return 1;
    }
   
    return 0;
}

int extent(Grid field, Point origin, Direction direction) {
    /* Calculates the extent of a square in a given direction.
       Parameters:
           field an object of the Grid structure.
           origin an object of the Point structure.
           direction an object of the Direction structure.
       Return:
           Returns the calculated extent.
    */
    
    Point tmp_origin = origin;
    

    int extent_NORTH=0;
    int extent_SOUTH =0;
    int extent_EAST =0;
    int extent_WEST =0;
    switch (direction) {
        
        case NORTH:
            
            while (tmp_origin.j - 1 >= 2 && colisionWithWayOrEndOfMap(tmp_origin, field) != 0) {
               
                tmp_origin.j--;
                extent_NORTH++;
                
            }
            
            
            return extent_NORTH;

        case SOUTH:
            
            while (tmp_origin.j + 1 < field.length-1-2 && colisionWithWayOrEndOfMap(tmp_origin, field) != 0) {
                
                tmp_origin.j++;
                extent_SOUTH++;
                
            }
            
            return extent_SOUTH;

        case EAST:
            
            while (tmp_origin.i + 1 < field.width-1-2 && colisionWithWayOrEndOfMap(tmp_origin, field) != 0) {
                 
                tmp_origin.i++;
                extent_EAST++;
                
            }
            
            return extent_EAST;

        case WEST:
            
            while (tmp_origin.i - 1 >= 2 && colisionWithWayOrEndOfMap(tmp_origin, field) != 0) {
                
                tmp_origin.i--;
                extent_WEST++;
                
            }
           
            return extent_WEST;

        default:
            
            return -1; 
    }
    
    return 0;
}


int extentCurrentDir(Grid *grid ,Direction currentDir) {
    /*
    Calculates the extent of the last point's direction in the way within the grid.
    Parameters:
        grid *grid: A pointer to the Grid structure.
    Return:
        The extent of the last point's direction in the way.
    */

    if (grid == NULL || grid->way == NULL || grid->size_way == 0) {
        return 0; 
    }

   
    Point lastPoint = grid->way[grid->size_way - 1];
    

    
    return extent(*grid, lastPoint,currentDir);
}

int max(int a,int b){
    /* Determines the maximum between two integers.
       Parameters:
           Two integers to compare.
       Return:
           The maximum.
    */
    if(a>b){
        return a;
    }
    return b;
}

int caseToAddDirection(Direction direction ,int extentOfDirection){
    /* Determines the extent of the current direction of the way; if it is less than or equal to 2, the function stops, otherwise, N cases are added to the way (N is determined according to the logic imposed in step 4) in the current direction.
       Parameters:
           The current direction.
           The extent of the current direction.
       Return:
           The number of cases to add.
    */
    
    int sum = 0;
    if(extentOfDirection <=2){
        return -1;
    }
    else{
        
        for(int i = 0; i < extentOfDirection; i++) {
        
            if ((double)rand() / RAND_MAX < 0.75) {
                sum += 1;
            }
        }
        return max(sum,3);

    }

}



Direction detNewDir(Grid field, Point origin) {
    /* Determines the new direction to follow for the continuation of the way.
       Parameters:
           Grid field representing the game field.
           Point origin as the starting point of the algorithm to determine the new direction.
       Return:
           Direction object with the new direction to follow.
    */

    Direction left, right;

    
    switch (origin.dir) {
        case NORTH:
            left = WEST;
            right = EAST;
            break;
        case SOUTH:
            left = EAST;
            right = WEST;
            break;
        case EAST:
            left = NORTH;
            right = SOUTH;
            break;
        case WEST:
            left = SOUTH;
            right = NORTH;
            break;
        default:
        
            return NO_DIR; 
    }
    ////printf("extent DEBUT CALCUL\n");
    int extentleft = extent(field, origin, left);
    int extentright = extent(field, origin, right);
    int totalextent = extentleft + extentright;
    ////printf("G:%d|D:%d\n",extentleft,extentright);
    if (totalextent == 0) {
        ////printf("extent ZERO IF\n");
        return NO_DIR; 
    }

    int randValue = rand() % totalextent;
    
    if (randValue < extentleft) {
        return left;
    } else {
        return right;
    }
}

void displayway(Grid *grid) {
    /* Displays the way stored in the grid.
       Parameter:
           grid: A pointer to a Grid structure.
    */
    if (grid == NULL || grid->way == NULL) {
        ////printf("Aucun way à displayr.\n");
        return;
    }

    ////printf("way:\n");
    for (int i = 0; i < grid->size_way; i++) {
        ////printf("(%d, %d) Dir: %d\n", grid->way[i].i, grid->way[i].j, grid->way[i].dir);
    }
}

int checkway(Point *way,int sizeway){
    /* Checks if the way is valid or not according to step 7 of the generation algorithm.
       Parameters:
           Point *way, an array of points representing the way.
           int sizeway, the length of this way.
       Return:
           Returns 1 if the way is valid and 0 if it is not.
    */
    int i;
    int turns =0;

    if(sizeway>= 75){
        for(i=0;i<sizeway-1;i++){
            
            if(turns >= 7){
                return 1;
            }
            if(way[i].dir != way[i+1].dir){
                
                turns++;
            }
            

        }
        if(turns >= 7){
            return 1;
        }
        else{
            return 0;
        }

    }
    else{
        return 0;
    }
}

void addNCases(Grid *grid, int N, Direction dir, int lastIndex) {
    /* Adds N points to the way and therefore to the grid.
       Parameters:
           grid *grid: the grid containing the way and the points.
           int N: the number of cases to add.
           Direction dir: the direction to follow for placing the point.
       Return:
           void
    */
    if (grid == NULL) {
        return;
    }

    Point *newway = (Point*)realloc(grid->way, (grid->size_way + N) * sizeof(Point));
    if (newway == NULL) {
        return;
    }
    grid->way = newway;

    Point lastPoint = grid->way[lastIndex];

    for (int i = 0; i < N; i++) {
        Point newPoint;
        newPoint.dir = dir;
        newPoint.case_grid = 'X';

        
        switch (dir) {
            case EAST:
                newPoint.i = min(lastPoint.i + i + 1, grid->width - 1);
                newPoint.j = lastPoint.j;
                break;
            case WEST:
                newPoint.i = max(lastPoint.i - i - 1, 0);
                newPoint.j = lastPoint.j;
                break;
            case SOUTH:
                newPoint.i = lastPoint.i;
                newPoint.j = min(lastPoint.j + i + 1, grid->length - 1);
                break;
            case NORTH:
                newPoint.i = lastPoint.i;
                newPoint.j = max(lastPoint.j - i - 1, 0);
                break;
            default:
                
                break;
        }

        
        grid->way[grid->size_way + i] = newPoint;
        grid->grid[newPoint.i][newPoint.j] = newPoint;

       
    }

    grid->size_way += N;
}


void deletegrid(Grid *grid) {
    /*
    Frees the memory allocated for a grid and its components.
    Parameters:
        grid: A pointer to a Grid structure.
    */

    if (grid != NULL) {
        
        if (grid->grid != NULL) {
            for (int i = 0; i < grid->width; i++) {
                if (grid->grid[i] != NULL) {
                    free(grid->grid[i]);
                }
            }
            
            free(grid->grid);
        }

        
        if (grid->way != NULL) {
            free(grid->way);
        }
        
        
        grid->grid = NULL;
        grid->way = NULL;
        grid->width = 0;
        grid->length = 0;
        grid->size_way = 0;
    }
}

Direction getDir(Grid field, Point point) {
    /*
    Calculates the extents in all cardinal directions for a given Point, then randomly chooses the initial direction with a probability proportional to the extent of each.
    Parameters:
        Grid field: The grid to operate on.
        Point point: The point for which to determine the direction.
    Return:
        Direction: The chosen direction.
    */

    int extentNORTH = extent(field, point, NORTH);
    int extentSOUTH = extent(field, point, SOUTH);
    int extentEAST = extent(field, point, EAST);
    int extentWEST = extent(field, point, WEST);
    int totalextent = extentNORTH + extentSOUTH + extentEAST + extentWEST;

    int randValue = rand() % totalextent;

    
    if (randValue < extentNORTH) {
        return NORTH;
    } else if (randValue < extentNORTH + extentSOUTH) {
        return SOUTH;
    } else if (randValue < extentNORTH + extentSOUTH + extentEAST) {
        return EAST;
    } else {
        return WEST;
    }
}

void startOfway(Grid *grid, Point point) {
    /*
    Adds the first point to the dynamic array way contained in the grid.
    Parameters:
        grid *grid: A pointer to the Grid structure.
        Point point: The point to add as the first element of the way.
    */

    if (grid == NULL) {
        return; 
    }

    
    grid->way = (Point*)malloc(sizeof(Point));
    if (grid->way == NULL) {
        
        return;
    }

    
    grid->way[0].i = point.i;
    grid->way[0].j = point.j;
    grid->way[0].case_grid = point.case_grid;
    grid->way[0].dir = point.dir;
    grid->grid[point.i][point.j].case_grid=point.case_grid;
    ////printf("CHECK PERTE DE DONNEE START OF way (%d|%d)\n",point.i,point.j);
   
    grid->size_way = 1;
}

void startManhattan(Grid *grid){
     /*
     Starts the Manhattan algorithm for the grid.
     Parameters :
        Grid *grid the grid with the algoritm will start on.
    */
    Point point;
    ////printf("DEBUT MANHATTAN-----------------------------------------------------------------------------\n");
    init_grid(grid);
    caseAleat(*grid,&point);
    
    ////printf("(%d|%d)\n",point.i,point.j);
    point.dir = getDir(*grid,point);
    ////printf("DIRECTION:%d\n",point.dir);
    point.case_grid ='X';
    startOfway(grid,point);
}

int makeway(Grid *grid, Direction currentDir) {
     /*
    Continues building the way in the grid.
    Parameters:
        grid *grid: The grid.
        Direction currentDir: The current direction.
    Return:
        The state of the algorithm.
    */
    int currentextent, nbCaseToAdd;
    currentextent = extentCurrentDir(grid,currentDir);

    if (currentextent < 2) {
        return 7;
    } else {
        nbCaseToAdd = caseToAddDirection(currentDir, currentextent);
        if (nbCaseToAdd == 0 || nbCaseToAdd == -1) {
            return 8;
        }
        addNCases(grid, nbCaseToAdd, currentDir, grid->size_way - 1);
        return 5;
    }
}

void growway(Grid *grid) {
    /*
        Algorithm to build the way.
            Parameters:
                Grid grid the field.
    */
    int algoState;
    Direction currentDir = grid->way[grid->size_way - 1].dir;
    algoState = makeway(grid, currentDir);

    while (algoState != 7) {
        if (algoState == 8) {
            break;
        }
        
        currentDir = detNewDir(*grid, grid->way[grid->size_way - 1]);
        if (currentDir == NO_DIR) {
            break;
        }

        
        algoState = makeway(grid, currentDir);
    }

    return;
}


void endway(Grid *grid){
    /*Check if the way respects the rules and if not delete the grid.
        Parameter:
            Grid *grid: the field.
    */
    if(checkway(grid->way,grid->size_way) == 1){
        //printf("FIN\n");
        return;
    }
    else{
        //printf("ECHEC GEN way TAIILLE :%d\n",grid->size_way);
        deletegrid(grid);
        
        return;
    }
}

int Manhattan(Grid *grid){
    /*
        Algoritm who generates a correct field and his way.
            Parameter:
                Grid *grid:the field.
            Return:
                Returns 1 at the end.
    */
    int exit =0;
    while (exit != 1)
    {
        
        startManhattan(grid);
        growway(grid);
        
        display_grid(*grid); 
        displayway(grid); 
        exit =checkway(grid->way,grid->size_way);  
        if(exit == 1){
            break;
        }
        deletegrid(grid);
        
    }
    
    return 1;
}


int equals(Point p1,Point p2){
    /*
        Check if two point are in the same location.
        Parameters:
            Two Point objects
        Return:
            Returns 1 if true and 0 if false.
    */
   if(p1.i == p2.i && p1.j == p2.j){
       return 1;
   }
   else{
       return 0;
   }
}



bool isWithinGrid(Grid grid, Tower tower) {
    return tower.posTower->i >= 0 && tower.posTower->i < grid.width &&
           tower.posTower->j >= 0 && tower.posTower->j < grid.length;
}

bool isNotOnWay(Grid grid, Tower tower) {
    for (int i = 0; i < grid.size_way; i++) {
        if (grid.way[i].i == tower.posTower->i && grid.way[i].j == tower.posTower->j) {
            return false;
        }
    }
    return true;
}

bool isUniquePosition(Grid grid,Point towerPos) {
    for (int i = 0; i < grid.num_towers; i++) {
        if (grid.towers[i].posTower->i == towerPos.i &&
            grid.towers[i].posTower->j == towerPos.j) {
            return false;
        }
    }
    return true;
}


void addTower(Grid *grid,Point towerPos){
    if(grid->num_towers == 0){
        grid->towers = malloc(1*sizeof(Tower));
        initializeTower((&grid->towers[grid->num_towers]),towerPos.i,towerPos.j);
        grid->num_towers++;
    }
    else{
        Tower *tmpTowers;
        tmpTowers =realloc(grid->towers,(grid->num_towers+1)*sizeof(Tower));
        if(tmpTowers == NULL){
            perror("New tower allocation failed\n");
        }
        else{
            grid->towers = tmpTowers;
            initializeTower((&grid->towers[grid->num_towers]),towerPos.i,towerPos.j);
            grid->num_towers++;
        } 
        
    }
}




void fillInventoryHolesCaller(Grid *grid) {
    Gem *pointersToGems[9];
    for (int i = 0; i < 9; i++) {
        pointersToGems[i] = &(grid->gems[i]);
    }

    fillInventoryHoles(pointersToGems, grid->cntGems);
}