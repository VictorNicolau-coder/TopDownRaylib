#ifndef SCENES_HANDLER_H
#define SCENES_HANDLER_H

#include "startScreen.c"
#include "endScreen.c"
#include "gameplay.c"

void SceneInit();
void SceneUpdate();
void SceneDraw();
void SceneUnload();

#endif