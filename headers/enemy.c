#include "enemy.h"

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

    Vector2 direction = Vector2Subtract((Vector2){jogador.rect.x, jogador.rect.y}, (Vector2){e->rect.x, e->rect.y});
    direction = Vector2Normalize(direction);

    e->rect.x += direction.x * e->velocity * delta;
    e->rect.y += direction.y * e->velocity * delta;

    if (betweenProjectiles >= cooldown && IsPlayerDead(jogador) == false){
        e->projectile[countProjectiles] = CreateProjectile(
            (Vector2){e->rect.x + (e->rect.width / 2), e->rect.y + (e->rect.height / 2)}, 
            8, 
            600, 
            (Vector2){6, 12}, 
            2, 
            (Vector2){jogador.rect.x + 16, jogador.rect.y + 16}
        ); 
        InitProjectile(&e->projectile[countProjectiles++]);

        if (countProjectiles >= 10) countProjectiles = 0;
        
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
