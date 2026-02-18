#include <stdlib.h>
#include "headers\tile.h"

void TileUpdate(Tile *t){

}

void TileDraw(Tile t){
    Rectangle source = {0, 0, 32, 32};
    Vector2 position = {t.rect.x, t.rect.y};
    
    //DrawRectangle(t.rect.x, t.rect.y, t.rect.width, t.rect.height, t.cor);
    if (t.tileType != UNKNOW)
        DrawTextureRec(t.texture, source, position, WHITE);
}

void TileUnload(Tile *t){
    UnloadTexture(t->texture);
    free(t);
}