#include "headers\projectile.h"

Projectile CreateProjectile(Vector2 position, float size, float velocity, Vector2 RangeDamage, float duration, Vector2 target){
    Projectile p = {
        .active = true,
        .rect = (Rectangle){position.x, position.y, size, size},
        .velocity = velocity,
        .RangeDamage = (Vector2){RangeDamage.x, RangeDamage.y},

        .duration = duration,
        .timer = 0,

        .target = target,
        .direction = (Vector2){0,0}
    };
    return p;
}

void InitProjectile(Projectile *p){
    p->direction = Vector2Subtract(p->target, (Vector2){p->rect.x, p->rect.y});
    p->direction = Vector2Normalize(p->direction);
}

void UpdateProjectile(Projectile *p){
    if (p->timer >= p->duration){
        p->active = false;
        return;
    }

    float delta = GetFrameTime();

    p->rect.x += p->direction.x * p->velocity * delta;
    p->rect.y += p->direction.y * p->velocity * delta;
    
    p->timer += delta;
}

void DrawProjectile(Projectile p){
    DrawCircle(p.rect.x, p.rect.y, p.rect.height, paleta[0]);
}

void UnloadProjectile(Projectile *p){}
