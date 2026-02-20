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
        .RangeDamage = RangeDamage
    };
    return e;
}

void EnemyUpdate(Enemy *e){
    float delta = GetFrameTime();

     // Movimento simples (pode ser AI mais complexa depois)
    e->rect.x += sin(GetTime()) * e->velocity * delta;

    // Disparo automático (em direção fixa por enquanto)
    if (betweenProjectiles >= cooldown) {
        e->projectile[countProjectiles] = CreateProjectile(
            (Vector2){e->rect.x + e->rect.width / 2, e->rect.y + e->rect.height / 2},
            8, 600, (Vector2){6, 12}, 2, (Vector2){e->rect.x + 300, e->rect.y}
        ); 
        InitProjectile(&e->projectile[countProjectiles]);
        countProjectiles = (countProjectiles + 1) % 10;
        betweenProjectiles = 0;
    }

    /* float velocity = 0.3;

    e->rect.y = 210 + sin(GetTime()*velocity) * 140;
    e->rect.x = 530 + cos(GetTime()*velocity) * 266; */


    for (int i = 0; i < 10; i++) UpdateProjectile(&e->projectile[i]);

    //Informa o tempo em que o último projétil foi lançado
    betweenProjectiles += delta;
  
}

void EnemyDraw(Enemy e){
    Rectangle source = {0, 0, 128, 128};
    Vector2 position = {e.rect.x - 24, e.rect.y - 25};

    DrawTextureRec(e.texture, source, position, WHITE);

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
void EnemyHit(Enemy *e, Vector2 RangeDamage){
    if (IsEnemyDead(*e)) return;
    int damage = GetRandomValue((int)RangeDamage.x, (int)RangeDamage.y);
    e->life -= damage;
    if (e->life < 0) e->life = 0;
    printf("Inimigo recebeu %d de dano\n", damage);
}

bool IsEnemyDead(Enemy e){
    return e.life <= 0;
}