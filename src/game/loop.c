#ifndef LOOP_C
#define LOOP_C

#include "../game.c"
#include "../raywrapper.h"

typedef enum {
    LOOP_TITLESCREEN,
    LOOP_RUNNING,
    LOOP_PAUSED
} GameLoop;

void loop_titlescreen(struct Game* self) {
    BeginDrawing();
        ClearBackground(BLACK);
    EndDrawing();
}

#endif // LOOP_C