#include "headers/scenes.h"
#include "headers/gameplay.h"

Texture2D CeilingBrick;
Texture2D WallBrick;
Texture2D ArrivalBrick;

Texture2D FloorBrick[4];

void GameplayInit(){
    int position = 0;

    int MAP[RowsMap][ColunmsMap] = {
        {9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {9, 9, 9, 9, 9, 9, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {9, 9, 9, 9, 9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
    };

    CeilingBrick = LoadTexture("resources/ceil_brick.png");
    WallBrick = LoadTexture("resources/wall_brick.png");
    ArrivalBrick = LoadTexture("resources/arrival.png");

    FloorBrick[0] = LoadTexture("resources/floor_brick.png");
    FloorBrick[1] = LoadTexture("resources/floor_brick2.png");
    FloorBrick[2] = LoadTexture("resources/floor_brick3.png");
    FloorBrick[3] = LoadTexture("resources/floor_brick4.png");

    //Valor random
    int r;

    for (int y = 0; y < RowsMap; y++){
        for (int x = 0; x < ColunmsMap; x++){
            switch (MAP[y][x]){
                case 0: 
                    r = GetRandomValue(0, 30);
                    if (r > 3) r = 0;

                    parede[position++] = (Tile){{x*32.0f, y*32.0f, TILE_SIZE, TILE_SIZE}, FloorBrick[r], FLOOR};
                    break;
                case 1: parede[position++] = (Tile){{x*32.0f, y*32.0f, TILE_SIZE, TILE_SIZE}, CeilingBrick, BRICK}; break;
                case 2: parede[position++] = (Tile){{x*32.0f, y*32.0f, TILE_SIZE, TILE_SIZE}, WallBrick, BRICK}; break;
                case 3: arrival = (Tile){{x*32.0f, y*32.0f, TILE_SIZE, TILE_SIZE}, ArrivalBrick, BRICK}; break;
            }
        }        
    }

    jogador = CreatePlayer(LoadTexture("resources/cat.png"), (Vector2){256.0f, 64.0f}, 250, 30);
    enemy = CreateEnemy(LoadTexture("resources/eye.png"), (Vector2){532.0f, 256.0f}, 30, 100, (Vector2){12, 18});

    camera.rotation = 0;
    camera.offset = (Vector2){0, 0};
    camera.target = (Vector2){0, 0};
    camera.zoom = 1.33;

    intensity = 0;
    duration = 0.;
    timer = 0;
    originalTarget = (Vector2){0, 0};

    timerMorte = 0;
}

void GameplayUpdate(){
    EnemyUpdate(&enemy, (Vector2){jogador.rect.x, jogador.rect.y});
    PlayerUpdate(&jogador, parede, sizeof(parede)/sizeof(parede[0]));

    // === PLAYER SHOOT ===
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !IsPlayerDead(&jogador)) {
        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
        PlayerShoot(&jogador, mouseWorld);
    }
    
    // === ENEMY SHOOT ===
    if (!IsPlayerDead(&jogador))
        EnemyShoot(&enemy, jogador.move);

    // === PLAYER VS ENEMY PROJECTILES ===
    for (int i = 0; i < 10; i++) {
        if (enemy.projectile[i].active &&
            CheckCollisionRecs(jogador.rect, enemy.projectile[i].rect) &&
            IsPlayerHittable()) {

            PlayerHit(&jogador, enemy.RangeDamage);
            enemy.projectile[i].active = false;
            InitCameraShake(2.0f, 0.5f);
        }
    }

    // === ENEMY VS PLAYER PROJECTILES ===
    for (int i = 0; i < 10; i++) {
        if (jogador.projectile[i].active &&
            CheckCollisionRecs(jogador.projectile[i].rect, enemy.rect) &&
            !IsEnemyDead(enemy)) {

            EnemyHit(&enemy, (Vector2){6, 12});
            jogador.projectile[i].active = false;
            InitCameraShake(3.0f, 0.3f);
        }
    }

    // === PLAYER VS ENEMY (corpo a corpo) ===
    if (CheckCollisionRecs(jogador.rect, enemy.rect) && IsPlayerHittable() && !IsPlayerDead(&jogador)) {
        InitCameraShake(10.0f, 1.0f);
        PlayerHit(&jogador, enemy.RangeDamage);
    }

    // === Morte do player ===
    if (IsPlayerDead(&jogador)){
        timerMorte += GetFrameTime();
        if (timerMorte > 2) trasition(END);
    }
    
    ApplyCameraShake(&camera);
}

void GameplayDraw(){
    ClearBackground(BLACK);

    BeginMode2D(camera);

        for (int i = 0; i < ColunmsMap*RowsMap; i++) TileDraw(parede[i]);
        PlayerDraw(&jogador);
        TileDraw(arrival);
        EnemyDraw(enemy);

    EndMode2D();
    
    if (counter - fadeVelocity > 0){
        counter -= fadeVelocity;
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, (unsigned char)counter});
    }

    DrawTextEx(font, "Floor", (Vector2){64, 16}, 90, 2, paleta[0]);
    DrawRectangleLinesEx((Rectangle){84, 90, 90 , 48}, 2, paleta[0]);
    DrawTextEx(font, "01", (Vector2){115, 87}, 60, 2, paleta[0]);

    char txtVida[10];
    sprintf(txtVida, "Vida: %d", jogador.life);
    DrawTextEx(font, txtVida, (Vector2){80, 145}, 60, 2, paleta[0]);
}

void GameplayUnload(){
    UnloadTexture(CeilingBrick);
    UnloadTexture(WallBrick);
    UnloadTexture(ArrivalBrick);

    for (int i = 0; i < 4; i++)
        UnloadTexture(FloorBrick[i]);

    PlayerUnload(&jogador); // apenas se ele tiver textura própria
    EnemyUnload(&enemy); 

    PlayerUnload(&jogador);
    EnemyUnload(&enemy);
}