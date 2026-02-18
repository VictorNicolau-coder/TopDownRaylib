#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "raymath.h"

#include "constants.h"

extern Player jogador;

int countProjectiles = 0;
float cooldown = 2.0f;
float betweenProjectiles = 0;

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

#endif