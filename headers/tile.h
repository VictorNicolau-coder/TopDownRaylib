#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include "raymath.h"

typedef enum TileType {UNKNOW = 0, BRICK, FLOOR} TileType;

typedef struct tile{
    Rectangle rect;
    Texture2D texture;
    TileType tileType;
} Tile;

void TileUpdate(Tile *t);
void TileDraw(Tile t);
void TileUnload(Tile *t);

#endif