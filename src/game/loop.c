#ifndef LOOP_C
#define LOOP_C

#include "../game.c"
#include "state.h"
#include "../raywrapper.h"

void loop_options(Game* self);
void loop_running(Game* self);

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

        float title_size = state.window_width * 0.07;

        // Draw the text
        DrawTextEx(self->assets.fonts.doomed, "NeptuNus", vec2(30.0, 30.0), title_size, 1.0, WHITE);

        // button dimensions
        float top_padding = title_size + 40.0f;
        float btn_width = title_size * 4.0f;
        float btn_height = title_size * 0.8f;
        float btn_spacing = btn_height + 10.0 * 2.0;


        // Draw the buttons
        if (ui_button(UI_SIMPLE, "PLAY", rect(30, top_padding, btn_width, btn_height))) {
            self->loop_type = LOOP_RUNNING;
            self->loop = &loop_running;
            DisableCursor();
        }
        else if (ui_button(UI_SIMPLE, "OPTIONS", rect(30, top_padding + btn_spacing, btn_width, btn_height))) {
            self->loop_type = LOOP_OPTIONS;
            self->loop = &loop_options;
        }

        debug_fps();
    EndDrawing();
}

void loop_options(Game* self) {
    BeginDrawing();
        ClearBackground(BLACK);

        debug_fps();
    EndDrawing();
}
void loop_running(Game* self) {
    static Camera camera = {
        .fovy = 90,
        .position = {1.0f, 1.0f, 1.0f},
        .projection = CAMERA_PERSPECTIVE,
        .up = {0.0f, 1.0f, 0.0f}
    };

    UpdateCamera(&camera, CAMERA_FIRST_PERSON);
    
    BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
            DrawPlane(vec3(0, 0, 0), vec2(100, 100), WHITE);
        EndMode3D();

        debug_fps();
    EndDrawing();
}
#endif // LOOP_C
