#include <stdio.h>
#include "raywrapper.h"

int main(void) {
    InitWindow(500, 500, "Hello");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();
}