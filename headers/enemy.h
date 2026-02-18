#pragma once

#include "raylib.h"
#include "raymath.h"

#include "constants.h"
#include "player.h"

extern Player jogador;

extern int countProjectiles;
extern float cooldown;
extern float betweenProjectiles;

typedef struct enemy{
    Rectangle rect;
    Texture2D texture;
    
    float velocity;
    int life;
    Vector2 RangeDamage;

    Projectile projectile[10];
} Enemy;

Enemy CreateEnemy(Texture2D text, Vector2 position, float velocity, int life, Vector2 RangeDamage);

void EnemyUpdate(Enemy *e);
void EnemyDraw(Enemy e);
void EnemyUnload(Enemy *e);