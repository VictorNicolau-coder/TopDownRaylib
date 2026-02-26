#include "headers\player.h"
#include <math.h>

double LastHitTime = 0;
const double INVULNERABILITY_TIME = 1.0; // 1 segundo de invulnerabilidade

Player CreatePlayer(Texture2D text, Vector2 position, float velocity, int life){
    Player p = {
        .rect = (Rectangle){position.x, position.y, TILE_SIZE, TILE_SIZE},
        .texture = text,
        .scale = 1.0,
        .rotation = 0.0f,
        .flipH = 1,
        .flipV = 1,

        .velocity = velocity,
        .life = life,
        .move = position,
        .smoothing = 0.15,

        .currentProjectile = 0,
        .cooldown = 0.2f,
        .projectileTimer = 1.0f,

        .state = IDLE
    };
    
    return p;
}

void PlayerUpdate(Player *p, Tile *tiles, int length){
    float delta = GetFrameTime();
    
    for (int i = 0; i < 10; i++) UpdateProjectile(&p->projectile[i]);
    p->projectileTimer += delta;
    
    if (p->life <= 0) return;
    
    //===MOVIMENTAÇÃO===
    Vector2 newMove = {0};
    float hor_move = (IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT));
    float ver_move = (IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP));

    if (hor_move != 0 || ver_move != 0){
        
        newMove = (Vector2){hor_move, ver_move};
        if (hor_move != 0)
            p->flipH = hor_move;  

        // Normaliza o movimento diagonal, se necessário
        if (newMove.x != 0 && newMove.y != 0)
            newMove = Vector2Normalize(newMove);

        // Atualiza a posição do jogador
        p->move.x += newMove.x * p->velocity * delta;
        p->move.y += newMove.y * p->velocity * delta;
        
        p->state = WALKING;
    } else {
        p->state = IDLE;
    }

    p->rect.x = Lerp(p->rect.x, p->move.x, p->smoothing);
    p->rect.y = Lerp(p->rect.y, p->move.y, p->smoothing);

    //===COLISÃO COM PAREDES===
    for (int i = 0; i < length; i++) {
        Tile *tile = &tiles[i];
        if (tile->tileType == BRICK && CheckCollisionRecs(p->rect, tile->rect)) {
            Rectangle inter = GetCollisionRec(p->rect, tile->rect);

            if (inter.width > 0 && inter.height > 0) {
                // Decide o eixo de resolução
                if (inter.width < inter.height) {
                    p->rect.x += (p->rect.x < tile->rect.x) ? -inter.width : inter.width;
                    p->move.x = p->rect.x;
                } else {
                    p->rect.y += (p->rect.y < tile->rect.y) ? -inter.height : inter.height;
                    p->move.y = p->rect.y;
                }
            }
        }
    }

}

void PlayerDraw(Player *p){
    //DrawRectangle(p->rect.x, p->rect.y, p->rect.width, p->rect.height, BLACK);
    float offsetY = 0.0;

    float centerX = p->rect.x + p->rect.width / 2;
    float centerY = p->rect.y + p->rect.height / 2;

    Rectangle source = {TILE_SIZE * (float)IsPlayerDead(p), 0, TILE_SIZE * p->flipH, TILE_SIZE * p->flipV};
    Color color = {255, 255, 255, 255};
    
    switch (p->state) {
        case IDLE:
            // Suaviza rotação de volta ao neutro
            p->rotation = Lerp(p->rotation, 0.0f, 0.05f);

            // Animação de "respiração" suave
            // Oscila entre 0.9x e 1.1x do tamanho original
            float time = GetTime();
            float breath = sinf(time * 2.0);
            float idleScale = 1.0f + 0.1f * sinf(time * 2.0f); // frequência ajustável
            p->scale = Lerp(p->scale, idleScale, 0.05f);
            
            offsetY = breath * -1.0f;
            break;
        
        case WALKING:
            // Retorna suavemente ao tamanho normal
            p->scale = Lerp(p->scale, 1.0f, 0.1f);
            p->rotation = sinf(GetTime() * 12) * 10; // Multiplicador de fora dita qual será a angulação
            break;
        
        case DEAD:
            p->scale = Lerp(p->scale, 1.0f, 0.1f);
            p->rotation = Lerp(p->rotation, 0.0f, 0.05f);
            break;

        default:
        break;
    }
    
    Rectangle dest = {centerX, centerY + offsetY, TILE_SIZE * p->scale, TILE_SIZE * p->scale};
    
    if (!IsPlayerHittable() && p->life > 0) color = (Color){255, 255, 255, 125};
    DrawTexturePro(p->texture, source, dest, (Vector2){dest.width/2, dest.height/2}, p->rotation, color);
    
    for (int i = 0; i < 10; i++){
        if (p->projectile[i].active == true)
        DrawProjectile(p->projectile[i]);
    }

}

void PlayerUnload(Player *p){
    UnloadTexture(p->texture);
}

//=== FUNÇÕES DE ESTADO ===
void PlayerShoot(Player *p, Vector2 targetWorld) {
    if (p->projectileTimer >= p->cooldown && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        p->projectile[p->currentProjectile] = CreateProjectile(
            (Vector2){p->rect.x + (p->rect.width / 2), p->rect.y + (p->rect.height / 2)}, 
            8, 600, (Vector2){6, 12}, 1.5f, GetMousePosition()
        );
        InitProjectile(&p->projectile[p->currentProjectile], Vector2Add(p->move, (Vector2){16,16}), targetWorld);

        p->currentProjectile = (p->currentProjectile + 1) % 10;
        p->projectileTimer = 0;
    }
}

bool IsPlayerHittable(){
    return (LastHitTime == 0 || GetTime() > LastHitTime + INVULNERABILITY_TIME);
}

void PlayerHit(Player *p, Vector2 RangeDamage){
    if (!IsPlayerHittable()) return;

    int damage = GetRandomValue((int)RangeDamage.x, (int)RangeDamage.y);
    p->life -= damage;
    if (p->life < 0){ 
        p->life = 0;    
        p->state = DEAD;
    }
    
    LastHitTime = GetTime();
    printf("Dano recebido: %d\n", damage);
}

bool IsPlayerDead(Player *p){
    return p->life <= 0;
}