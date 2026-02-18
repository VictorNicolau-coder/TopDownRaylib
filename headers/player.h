#pragma once

#include "raylib.h"
#include "raymath.h"

#include "constants.h"
#include "tile.h"
#include "projectile.h"

extern int cProjectilesPlayer;
extern float cooldownPlayer;
extern float bProjectilesPlayer;

extern float flipH, flipV;
extern int LastHitTime;

typedef struct player{
    Rectangle rect;
    Texture2D texture;

    float velocity;
    int life;
    Vector2 move;
    float acceleration;

    Projectile projectile[10];
} Player;

Player CreatePlayer(Texture2D text, Vector2 position, float velocity, int life);

void PlayerUpdate(Player *p, Tile *tiles, int lenght);
void PlayerDraw(Player p);
void PlayerUnload(Player *p);

void PlayerHit(Player *p, Vector2 RangeDamage);
bool IsPlayerHittable();
bool IsPlayerDead(Player p);