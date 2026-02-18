#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "scenes.h"

#define QtdButtons 4

// Estrutura para representar um botão
typedef struct button {
    Rectangle rect;
    char label[50];
} Button;

// Cria um botão com posição, tamanho e label
Button CreateButton(float X, float Y, float W, float H, char *label);

// Atualiza o botão: verifica clique e muda de cena se necessário
void UpdateButton(Button b, Rectangle rect, enum currentScene cs);

// Desenha o botão na tela
void DrawButton(Button b);

// Inicializa os elementos da tela inicial (botões, variáveis)
void StartInit(void);

// Atualiza a tela inicial (interações do mouse)
void StartUpdate(void);

// Desenha a tela inicial
void StartDraw(void);

// Libera recursos da tela inicial (se necessário)
void StartUnload(void);

// Botões e mouse usados na tela inicial (podem ser extern se usados em outro módulo)
extern Button buttons[QtdButtons];
extern Rectangle mouse;

#endif // STARTSCREEN_H
