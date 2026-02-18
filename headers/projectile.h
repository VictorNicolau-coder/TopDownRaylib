#pragma once

#include "raylib.h"
#include "raymath.h"

#include "constants.h"

typedef struct projectile{
    bool active;
    Rectangle rect;
    float velocity;
    Vector2 RangeDamage;

    float duration;
    float timer;

    Vector2 target;
    Vector2 direction;
} Projectile;

Projectile CreateProjectile(Vector2 position, float size, float velocity, Vector2 RangeDamage, float duration, Vector2 target);
void InitProjectile(Projectile *p);

void UpdateProjectile(Projectile *p);
void DrawProjectile(Projectile p);
void UnloadProjectile(Projectile *p);
