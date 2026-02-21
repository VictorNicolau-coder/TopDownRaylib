#pragma once

#include "raylib.h"
#include "raymath.h"

#include "constants.h"
#include "projectile.h"

extern int countProjectiles;
extern float cooldown;
extern float betweenProjectiles;

typedef struct {
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

void EnemyShoot(Enemy *e, Vector2 target);
void EnemyHit(Enemy *e, Vector2 RangeDamage);
bool IsEnemyDead(Enemy e);