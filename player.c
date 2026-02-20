#include "headers\player.h"

float flipH = 1; 
float flipV = 1;

double LastHitTime = 0;
const double INVULNERABILITY_TIME = 1.0; // 1 segundo de invulnerabilidade

Player CreatePlayer(Texture2D text, Vector2 position, float velocity, int life){
    Player p = {
        .rect = (Rectangle){position.x, position.y, TILE_SIZE, TILE_SIZE},
        .texture = text,

        .velocity = velocity,
        .life = life,
        .move = position,
        .smoothing = 0.35,

        .currentProjectile = 0,
        .cooldown = 0.2f,
        .projectileTimer = 1.0f
    };
    return p;
}

void PlayerUpdate(Player *p, Tile *tiles, int length){
    float delta = GetFrameTime();
    if (p->life <= 0) return;
    
    //===MOVIMENTAÇÃO===
    Vector2 newMove = {0};
    float hor_move = (IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT));
    float ver_move = (IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP));

    if (hor_move != 0 || ver_move != 0){
        
        newMove = (Vector2){hor_move, ver_move};
        if (hor_move != 0)
            flipH = hor_move;  

        // Normaliza o movimento diagonal, se necessário
        if (newMove.x != 0 && newMove.y != 0)
            newMove = Vector2Normalize(newMove);

        // Atualiza a posição do jogador
        p->move.x += newMove.x * p->velocity * delta;
        p->move.y += newMove.y * p->velocity * delta;
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

    // === TIRO DO PLAYER ===
    if (p->projectileTimer >= p->cooldown && IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        p->projectile[p->currentProjectile] = CreateProjectile(
            (Vector2){p->rect.x + (p->rect.width / 2), p->rect.y + (p->rect.height / 2)}, 
            8, 600, (Vector2){6, 12}, 1.5f, GetMousePosition()
        ); 
        InitProjectile(&p->projectile[p->currentProjectile]);

        p->currentProjectile = (p->currentProjectile + 1) % 10;
        p->projectileTimer = 0;
    }

    for (int i = 0; i < 10; i++) UpdateProjectile(&p->projectile[i]);
    p->projectileTimer += delta;
}

void PlayerDraw(Player p){
    Rectangle source = {32 * (float)IsPlayerDead(p), 0, 32 * flipH, 32 * flipV};
    Rectangle dest = {p.rect.x, p.rect.y, 32, 32};
    Color color = {255, 255, 255, 255};

    //Debug colisão
    //DrawRectangle(p.rect.x, p.rect.y, p.rect.width, p.rect.height, BLACK);

    if (!IsPlayerHittable() && p.life > 0) color = (Color){255, 255, 255, 125};
    DrawTexturePro(p.texture, source, dest, (Vector2){0, 0}, 0, color);

    for (int i = 0; i < 10; i++){
        if (p.projectile[i].active == true)
            DrawProjectile(p.projectile[i]);
    }
}

void PlayerUnload(Player *p){
    UnloadTexture(p->texture);
}

//=== FUNÇÕES DE ESTADO ===
bool IsPlayerHittable(){
    return (GetTime() > LastHitTime + INVULNERABILITY_TIME);
}

void PlayerHit(Player *p, Vector2 RangeDamage){
    if (!IsPlayerHittable()) return;

    int damage = GetRandomValue((int)RangeDamage.x, (int)RangeDamage.y);
    p->life -= damage;
    if (p->life < 0) p->life = 0;

    LastHitTime = GetTime();
    printf("Dano recebido: -%d\n", damage);
}

bool IsPlayerDead(Player p){
    return p.life <= 0;
}