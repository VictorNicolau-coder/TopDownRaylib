#include "scenes.h"

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

    Texture2D CeilingBrick = LoadTexture("../resources/ceil_brick.png");
    Texture2D WallBrick = LoadTexture("../resources/wall_brick.png");
    Texture2D ArrivalBrick = LoadTexture("../resources/arrival.png");

    Texture2D FloorBrick[4] = {
        LoadTexture("../resources/floor_brick.png"),
        LoadTexture("../resources/floor_brick2.png"),
        LoadTexture("../resources/floor_brick3.png"),
        LoadTexture("../resources/floor_brick4.png")
    };

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

    jogador = CreatePlayer(LoadTexture("../resources/cat.png"), (Vector2){256.0f, 64.0f}, 250, 30);
    enemy = CreateEnemy(LoadTexture("../resources/eye.png"), (Vector2){532.0f, 256.0f}, 50, 100, (Vector2){12, 18});

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
    EnemyUpdate(&enemy);
    PlayerUpdate(&jogador, parede, sizeof(parede)/sizeof(parede[0]));
    
    if (IsPlayerDead(jogador) == false){    
        for (int j = 0; j < 10; j++){
            if (CheckCollisionRecs(jogador.rect, enemy.projectile[j].rect) && IsPlayerHittable()){
                if (timer >= duration)
                    InitCameraShake(2.0f, 0.5f);
                PlayerHit(&jogador, enemy.projectile[j].RangeDamage);
            }
        }

        if (CheckCollisionRecs(jogador.rect, enemy.rect) && IsPlayerHittable()){
            if (timer >= duration)
                InitCameraShake(10.0f, 1.0f);
            PlayerHit(&jogador, enemy.RangeDamage);
        }    
    } else if (IsPlayerDead(jogador)){
        timerMorte += GetFrameTime();
        if (timerMorte > 2) trasition(END);
    }
    
    ApplyCameraShake(&camera);
}

void GameplayDraw(){
    ClearBackground(BLACK);

    BeginMode2D(camera);

        for (int i = 0; i < ColunmsMap*RowsMap; i++) TileDraw(parede[i]);
        PlayerDraw(jogador);
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
    TileUnload(&arrival);
    PlayerUnload(&jogador);
}