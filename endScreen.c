#include "headers\scenes.h"
#include "headers\endScreen.h"

void EndInit(){

}

void EndUpdate(){
    if (IsKeyPressed(KEY_ENTER)){
        trasition(START);
    }
}

void EndDraw(){
    ClearBackground(BLACK);

    DrawTextEx(font, "U DIED", (Vector2){SCREEN_WIDTH / 2 - 64, SCREEN_HEIGHT / 2 - 32}, 64, 2, paleta[0]);

    if (counter - fadeVelocity > 0){
        counter -= fadeVelocity;
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){255, 255, 255, (unsigned char)counter});
    }
}

void EndUnload(){

}