#include "Tint.h"
#include <stdlib.h>
#include <stdio.h>

void showColor(Color color){
    switch (color)
    {
    case RED:
        printf("Color :RED\n");
        break;
    case GREEN:
        printf("Color :GREEN\n");
        break;
    case BLUE:
        printf("Color :BLUE\n");
        break;
    case MIXED:
        printf("Color :MIXED\n");
        break;
    
    default:
        break;
    }
}

void showElement(Element element){
    printf("--------------ELEMENT--------------------\n");
    switch (element)
    {
    case PYRO:
        printf("Element :PYRO\n");
        break;
    case DENDRO:
        printf("Element :DENDRO\n");
        break;
    case HYDRO:
        printf("Element :HYDRO\n");
        break;
    case NO_ELEMENT:
        printf("NO ELEMENT\n");
        break;
    
    default:
        break;
    }
}

Color aleatColor(){
    int res;
    res = MLV_get_random_integer(0,3);
    if(res == 0) return RED;
    if(res == 1) return GREEN;
    if (res == 2) return BLUE;
}


int aleatTint(Color color){
    int firstRange,secondRange,thirdRange,res;
    switch (color)
    {
    case RED:
        firstRange = MLV_get_random_integer(0,30);
        secondRange = MLV_get_random_integer(330,359);

        if(MLV_get_random_integer(0,1) == 0) return firstRange;
        return secondRange;
    case GREEN:
        return MLV_get_random_integer(90,150);
    case BLUE:
        return MLV_get_random_integer(210,270);
    case MIXED:
        
        firstRange = MLV_get_random_integer(31,89);
        secondRange = MLV_get_random_integer(151,209);
        thirdRange = MLV_get_random_integer(271,329);

        
        res = MLV_get_random_integer(0,2);
        switch (res)
        {
        case 0:
            return firstRange;
        case 1:
            return secondRange;
        case 2:
            return thirdRange;
        default:
            printf("ALEAT TINT ERROR\n");
            exit(EXIT_FAILURE);
        }
    
    default:
        printf("ALEAT TINT ERROR\n");
        exit(EXIT_FAILURE);
    }
}   