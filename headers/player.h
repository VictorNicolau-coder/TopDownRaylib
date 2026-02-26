#pragma once

#include "raylib.h"
#include "raymath.h"

#include "constants.h"
#include "tile.h"
#include "projectile.h"

extern double LastHitTime;

typedef enum {
    IDLE,
    WALKING, 
    DEAD
} PlayerState;

typedef struct {
    Rectangle rect;
    Texture2D texture;
    double scale;
    float rotation;
    float flipH;
    float flipV;

    float velocity;
    int life;
    Vector2 move;
    float smoothing;

    Projectile projectile[10];
    int currentProjectile;
    float cooldown;
    float projectileTimer;

    PlayerState state;
} Player;

Player CreatePlayer(Texture2D text, Vector2 position, float velocity, int life);

void PlayerUpdate(Player *p, Tile *tiles, int lenght);
void PlayerDraw(Player *p);
void PlayerUnload(Player *p);

void PlayerShoot(Player *p, Vector2 targetWorld);
void PlayerHit(Player *p, Vector2 RangeDamage);
bool IsPlayerHittable();
bool IsPlayerDead(Player *p);