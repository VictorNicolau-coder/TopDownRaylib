#pragma once

#include "raylib.h" // Necessário para Camera2D, Vector2, etc.
#include "constants.h"
#include "player.h"
#include "enemy.h"

#define ColunmsMap 30
#define RowsMap 16

typedef enum currentScene {START = 0, GAMEPLAY, QUIT, END} currentScene;

// Variáveis Globais (Apenas declarações)
extern currentScene cs;
extern Camera2D camera;
extern float timerMorte;
extern int counter;
extern int fadeVelocity;
extern float intensity;
extern float duration;
extern float timer;
extern Vector2 originalTarget;
extern Player jogador;
extern Enemy enemy;
extern Tile parede[ColunmsMap*RowsMap];
extern Tile arrival;

// Protótipos das Funções
void StartInit();
void StartUpdate();
void StartDraw();
void StartUnload();
void EndInit();
void EndUpdate();
void EndDraw();
void EndUnload();
void GameplayInit();
void GameplayUpdate();
void GameplayDraw();
void GameplayUnload();

void trasition(currentScene c);
void InitCameraShake(float INTENSITY, float DURATION);
void ApplyCameraShake(Camera2D *camera);
