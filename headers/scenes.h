#ifndef SCENES_H
#define SCENES_H

#include <string.h>

#include "constants.h"
#include "player.h"
#include "enemy.h"

#define ColunmsMap 30
#define RowsMap 16

typedef enum currentScene {START = 0, GAMEPLAY, QUIT, END} currentScene;
currentScene cs = GAMEPLAY;

Camera2D camera;

float timerMorte = 0;

//Transition
int counter = 0;
int fadeVelocity = 4;

//Shake camera
float intensity = 0;
float duration = 0.;
float timer = 0;
Vector2 originalTarget = {0};

Player jogador;
Enemy enemy;

Tile parede[ColunmsMap*RowsMap];
Tile arrival;

//Start screen
void StartInit();
void StartUpdate();
void StartDraw();
void StartUnload();

//End screen
void EndInit();
void EndUpdate();
void EndDraw();
void EndUnload();

//First level
void GameplayInit();
void GameplayUpdate();
void GameplayDraw();
void GameplayUnload();

void trasition(enum currentScene c){
    counter = 255;
    
    switch (c){
        case START: StartInit(); cs = START; break;
        case GAMEPLAY: GameplayInit(); cs = GAMEPLAY; break;
        case QUIT: CloseWindow(); break;
        case END: EndInit(); cs = END; break;
    }
}

void InitCameraShake(float INTENSITY, float DURATION) {
    intensity = INTENSITY;
    duration = DURATION;
    timer = 0.0f;
    originalTarget = (Vector2){0, 0};
}

void ApplyCameraShake(Camera2D *camera) {
    if (timer <= duration) {
        camera->target.x = originalTarget.x + (GetRandomValue(0, intensity * 2)) - intensity;
        camera->target.y = originalTarget.y + (GetRandomValue(0, intensity * 2)) - intensity;
        timer += GetFrameTime();
    } else {
        // Retorna à posição original suavemente
        camera->target.x = Lerp(camera->target.x, originalTarget.x, 1);
        camera->target.y = Lerp(camera->target.y, originalTarget.y, 1);
    }
}

#endif // !SCENES_H
