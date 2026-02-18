#include "headers\scenesHandler.h"

void SceneInit(){
    switch (cs){
        case START: StartInit(); break;
        case GAMEPLAY: GameplayInit(); break;
        case END: EndInit(); break;
    }
}

void SceneUpdate(){
    switch (cs){
        case START: StartUpdate(); break;
        case GAMEPLAY: GameplayUpdate(); break;
        case END: EndUpdate(); break;
    }
}

void SceneDraw(){
    switch (cs){
        case START: StartDraw(); break;
        case GAMEPLAY: GameplayDraw(); break;
        case END: EndDraw(); break;
    }
}

void SceneUnload(){
    switch (cs){
        case START: StartUnload(); break;
        case GAMEPLAY: GameplayUnload(); break;
        case END: EndUnload(); break;
    }
}