#include "scenes.h"

typedef struct button{
    Rectangle rect;
    char label[50];
} Button;

Button CreateButton(float X, float Y, float W, float H, char *label){
    Button b;
    b.rect = (Rectangle) {X, Y, W, H};
    strncpy(b.label, label, sizeof(b.label) - 1);
    b.label[sizeof(b.label) - 1] = '\0'; // Garante que a string seja terminada corretamente
    
    return b;
}

void UpdateButton(Button b, Rectangle rect, enum currentScene cs){
    if (CheckCollisionRecs(b.rect, rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        trasition(cs);
}

void DrawButton(Button b){
    //DrawRectangleRec(b.rect, WHITE);
    DrawTextEx(font, b.label, (Vector2){b.rect.x + 10, b.rect.y + 5}, 80, 2, BLACK);
}

const int QtdButtons = 4;
Button buttons[QtdButtons]; 

Rectangle mouse = {0, 0, 32, 32};

void StartInit(){
    buttons[0] = CreateButton(32, 256, 150, 75, "Play");
    buttons[1] = CreateButton(32, 346, 300, 75, "Configuration");
    buttons[2] = CreateButton(32, 436, 200, 75, "Quit");
}

void StartUpdate(){
    mouse.x = GetMouseX();
    mouse.y = GetMouseY();

    UpdateButton(buttons[0], mouse, GAMEPLAY);
    UpdateButton(buttons[1], mouse, GAMEPLAY);
    UpdateButton(buttons[2], mouse, QUIT);
}

void StartDraw(){
    ClearBackground(BLUE);

    for (int i = 0; i < QtdButtons; i++) DrawButton(buttons[i]);

    DrawRectangleRec(mouse, PURPLE);

    if (counter - fadeVelocity > 0){
        counter -= fadeVelocity;
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){255, 255, 255, (unsigned char)counter});
    }
}

void StartUnload(){

}