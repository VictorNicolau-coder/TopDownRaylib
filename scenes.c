#include "headers\scenes.h"
#include "raymath.h" // Para a função Lerp

// Definição das Variáveis (Onde a memória é realmente alocada)
currentScene cs = GAMEPLAY;
Camera2D camera = { 0 };
float timerMorte = 0;
int counter = 0;
int fadeVelocity = 4;
float intensity = 0;
float duration = 0;
float timer = 0;
Vector2 originalTarget = {0, 0};
Player jogador;
Enemy enemy;
Tile parede[ColunmsMap * RowsMap];
Tile arrival;

// Implementação das Funções
void trasition(currentScene c) {
    counter = 255;
    switch (c) {
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
    originalTarget = camera.target; // Salva o alvo atual da câmera
}

void ApplyCameraShake(Camera2D *camera) {
    if (timer <= duration) {
        camera->target.x = originalTarget.x + (GetRandomValue(-intensity, intensity));
        camera->target.y = originalTarget.y + (GetRandomValue(-intensity, intensity));
        timer += GetFrameTime();
    } else {
        camera->target = originalTarget;
    }
}

// As funções StartInit, GameplayUpdate, etc., devem ser implementadas 
// aqui ou em arquivos específicos de cada fase.
