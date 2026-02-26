#include "headers\enemy.h"
#include "headers\projectile.h"  // garante que Projectile é conhecido
#include "raylib.h"
#include <stdio.h>

int countProjectiles = 0;
float cooldown = 2.0f;
float betweenProjectiles = 0;

Enemy CreateEnemy(Texture2D text, Vector2 position, float velocity, int life, Vector2 RangeDamage){
    Enemy e = {
        .rect = (Rectangle){position.x, position.y, 80, 80},
        .texture = text,

        .velocity = velocity,
        .life = life,
        .RangeDamage = RangeDamage,

        .isHit = false,
        .hitTimer = 0.0f
    };
    return e;
}

void EnemyUpdate(Enemy *e, Vector2 target){
    float delta = GetFrameTime();

    if (e->isHit){
        e->hitTimer -= delta;
        if (e->hitTimer <= 0) e->isHit = false;
    }

     // Movimento simples (pode ser AI mais complexa depois)
    Vector2 direction = Vector2Subtract((Vector2){target.x, target.y}, (Vector2){e->rect.x, e->rect.y});
    direction = Vector2Normalize(direction);

    e->rect.x += direction.x * e->velocity * delta;
    e->rect.y += direction.y * e->velocity * delta;

    for (int i = 0; i < 10; i++) UpdateProjectile(&e->projectile[i]);

    //Informa o tempo em que o último projétil foi lançado
    betweenProjectiles += delta;
}

void EnemyDraw(Enemy e){
    Rectangle source = {0, 0, 128, 128};
    Vector2 position = {e.rect.x - 24, e.rect.y - 25};

    if (e.isHit) {
        // ativa modo de mistura (a cor do DrawTexture se mistura com o branco)
        BeginBlendMode(BLEND_ADDITIVE);
        DrawTextureRec(e.texture, source, position, WHITE);
        EndBlendMode();
    } else {
        DrawTextureRec(e.texture, source, position, WHITE);
    }

    //Debug colisão
    //DrawRectangle(e.rect.x, e.rect.y, e.rect.width, e.rect.height, BLACK);
    for (int i = 0; i < 10; i++){
        if (e.projectile[i].active == true)
            DrawProjectile(e.projectile[i]);
    }
}

void EnemyUnload(Enemy *e){
    UnloadTexture(e->texture);
}

// === FUNÇÕES DE ESTADO ===
void EnemyShoot(Enemy * e, Vector2 target){
    // Disparo automático (em direção fixa por enquanto)
    if (betweenProjectiles >= cooldown) {
        
        e->projectile[countProjectiles] = CreateProjectile(
            (Vector2){e->rect.x + e->rect.width / 2, e->rect.y + e->rect.height / 2},
            8, 600, (Vector2){6, 12}, 2, (Vector2){e->rect.x, e->rect.y}
        );

        InitProjectile(&e->projectile[countProjectiles], (Vector2){e->rect.x + 40, e->rect.y + 40}, target);
        countProjectiles = (countProjectiles + 1) % 10;
        betweenProjectiles = 0;
    }
}

void EnemyHit(Enemy *e, Vector2 RangeDamage){
    if (IsEnemyDead(*e)) return;
    
    int damage = GetRandomValue((int)RangeDamage.x, (int)RangeDamage.y);
    
    e->isHit = true;
    e->hitTimer = 0.1f;
    e->life -= damage;
}

bool IsEnemyDead(Enemy e){
    return e.life <= 0;
}