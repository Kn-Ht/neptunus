#ifndef LOOP_C
#define LOOP_C

#include "../game.c"
#include "state.h"
#include "../raywrapper.h"

void loop_titlescreen(Game* self) {
    static Camera3D camera = {
        .fovy = 45,
        .position = {15.0f, 1.0f, 10.0f},
        .projection = CAMERA_PERSPECTIVE,
        .target = {0.0f, 0.0f, 12.0f},
        .up = {0.0f, 1.0f, 0.0f}
    };

    // Make the planet rotate
    float rotation_speed = 2.0f;
    static float rotation = 0.0f;

    // increment rotation until it has fully rotated
    if (rotation > 360.0f) rotation = 0.0f; 
    else rotation += rotation_speed * dt;

    self->assets.models.neptune.model.transform = MatrixRotateY(DEG2RAD*rotation);

    BeginDrawing();
        ClearBackground(BLACK);
        // Draw background
        DrawTexturePro(self->assets.img.stars,
                       rect(0, 0, self->assets.img.stars.width,
                            self->assets.img.stars.height),
                       rect(0, 0, state.window_width, state.window_height),
                       vec2(0, 0), 0.0, WHITE);

        // Draw the planet
        BeginMode3D(camera);
            DrawModel(self->assets.models.neptune.model, vec3(0.0f, 0.0f, 5.0f), 10.0f, WHITE);
        EndMode3D();

        // Draw the text
        DrawTextEx(self->assets.fonts.doomed, "NeptuNus", vec2(30.0, 30.0), state.window_width * 0.07, 1.0, WHITE);

        // Draw the buttons
        
     

        debug_fps();
    EndDrawing();
}

#endif // LOOP_C
