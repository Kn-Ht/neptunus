#ifndef LOOP_C
#define LOOP_C

#include "../game.c"
#include "../raywrapper.h"
 
void loop_titlescreen(Game* self) {
    BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureRec(self->assets.bg_stars, rect(0, 0, state.window_width, state.window_height), vec2(0, 0), WHITE);
        debug_fps();
    EndDrawing();
}

#endif // LOOP_C