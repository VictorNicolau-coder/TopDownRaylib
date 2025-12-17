#ifndef CONSTANT_H
#define CONSTANT_H

#include <stdio.h>
#include <stddef.h>

#include "raylib.h"
#include "raymath.h"

#define TILE_SIZE 32
#define PROPORCAO 85
#define SCREEN_WIDTH 15 * PROPORCAO
#define SCREEN_HEIGHT 8 * PROPORCAO

Font font; 
Color paleta[5] = {
    {235, 206, 235, 255},
    {145, 87, 145, 255},
    {105, 56, 105, 255},
    {66, 33, 66, 255},
    {51, 19, 51, 255}
};

#endif