#ifndef TINT_H
#define TINT_H
#include "Utils.h"
#include <MLV/MLV_all.h>

typedef enum{
    RED,
    GREEN,
    BLUE,
    MIXED
}Color;

typedef enum{
    PYRO,
    DENDRO,
    HYDRO,
    NO_ELEMENT,
    UNDER_DOUBLE_EFFECT
}Element;

//Print the color in the console
void showColor(Color color);

//Print the element in the console
void showElement(Element element);

Color aleatColor();

int aleatTint(Color color);

#endif 
