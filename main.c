#include "headers/constants.h"
#include "headers/scenesHandler.h"

int main(){
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MAZE GAME");
    SetTargetFPS(60);

    //SetWindowState(FLAG_FULLSCREEN_MODE);

    font = LoadFontEx("../resources/Enchanted Land.otf", 100, 0, 250);
    SceneInit();

    while (!WindowShouldClose()){
        SceneUpdate();

        BeginDrawing();
            
            SceneDraw();

        EndDrawing();
    }

    UnloadFont(font);
    SceneUnload();

    CloseWindow();
    return 0;
}

