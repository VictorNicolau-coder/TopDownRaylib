#include "headers\player.h"

cProjectilesPlayer = 0;
cooldownPlayer = 1.0f;
bProjectilesPlayer = 1.0f;

flipH = 1; 
flipV = 1;

Player CreatePlayer(Texture2D text, Vector2 position, float velocity, int life){
    Player p = {
        .rect = (Rectangle){position.x, position.y, TILE_SIZE, TILE_SIZE},
        .texture = text,

        .velocity = velocity,
        .life = life,
        .move = position,
        .acceleration = 0.25
    };
    return p;
}

void PlayerUpdate(Player *p, Tile *tiles, int lenght){
    float delta = GetFrameTime();
    
    if (p->life > 0){

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

        p->rect.x = Lerp(p->rect.x, p->move.x, p->acceleration);
        p->rect.y = Lerp(p->rect.y, p->move.y, p->acceleration);

        for (int i = 0; i < lenght; i++){
            Tile *tile = tiles + i;

            if (CheckCollisionRecs(p->rect, tile->rect) && tile->tileType == BRICK){
                Rectangle intersection = GetCollisionRec(p->rect, tile->rect);
                // Resolve collision along X axis
                if (fabs(intersection.width) < fabs(intersection.height)) {
                    if (newMove.x > 0)
                        p->rect.x -= intersection.width;
                    else if (newMove.x < 0)
                        p->rect.x += intersection.width;
                    p->move.x = p->rect.x;
                }
                // Resolve collision along Y axis
                else {
                    if (newMove.y > 0)
                        p->rect.y -= intersection.height;
                    else if (newMove.y < 0)
                        p->rect.y += intersection.height;
                    p->move.y = p->rect.y;
                }
            }
        }

        if (bProjectilesPlayer >= cooldownPlayer && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            p->projectile[cProjectilesPlayer] = CreateProjectile(
                (Vector2){p->rect.x + (p->rect.width / 2), p->rect.y + (p->rect.height / 2)}, 
                8, 
                600, 
                (Vector2){6, 12}, 
                2, 
                (Vector2){GetMousePosition().x, GetMousePosition().y}
            ); 
            InitProjectile(&p->projectile[cProjectilesPlayer++]);

            if (cProjectilesPlayer >= 10) cProjectilesPlayer = 0;
            
            bProjectilesPlayer = 0;
        }
    }

    for (int i = 0; i < 10; i++) UpdateProjectile(&p->projectile[i]);
    bProjectilesPlayer += delta;

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

//Funções 
bool IsPlayerHittable(){
    return (LastHitTime == 0 || GetTime() > LastHitTime + 2) ? true : false;
}

void PlayerHit(Player *p, Vector2 RangeDamage){
    int randomValue = GetRandomValue(RangeDamage.x, RangeDamage.y);

    if (IsPlayerHittable()){
        p->life -= randomValue;
        if (p->life < 0) p->life = 0;

        printf("-%d\n", randomValue);
        LastHitTime = GetTime();
    }
}

bool IsPlayerDead(Player p){
    return (p.life > 0) ? false : true;
}