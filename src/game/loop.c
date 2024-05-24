#ifndef LOOP_C
#define LOOP_C

#include "../game.c"
#include "context.h"
#include "../raywrapper.h"

void loop_options(Game* self);
void loop_running(Game* self);

static RenderTexture titlescreen_target = {0};

void loop_menu(Game* self) {
    static Camera3D camera = {
        .fovy = 300,
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

    objects[OBJ_NEPTUNE].transform = MatrixRotateY(DEG2RAD*rotation);

    // draw to texture

    BeginDrawing();
        ClearBackground(BLACK);
        // Draw background
        DrawTexturePro(textures[TXT_STARS],
                       rect(0, 0, textures[TXT_STARS].width,
                            textures[TXT_STARS].height),
                       rect(0, 0, ctx.window_width, ctx.window_height),
                       vec2(0, 0), 0.0, WHITE);

        // Draw the planet
        BeginMode3D(camera);
            DrawModel(objects[OBJ_NEPTUNE], vec3(0.0f, 0.0f, 5.0f), 10.0f, WHITE);
        EndMode3D();

        const char* title = "NeptuNus";

        float title_size = ctx.window_width * 0.1;
        Vector2 title_dims = MeasureTextEx(fonts[FNT_DOOMED], title, title_size, 1.0);
        float title_x = (ctx.window_width - title_dims.x) / 2.0;

        // Draw the text
        DrawTextEx(fonts[FNT_DOOMED], title, vec2(title_x, 30.0), title_size, 1.0, WHITE);

        // button dimensions
        float top_padding = title_size + 40.0f;
        float btn_width = title_size * 4.0f;
        float btn_height = title_size * 0.8f;
        float btn_spacing = btn_height + 10.0 * 2.0;
        float btn_x = (ctx.window_width - btn_width) / 2.0;

        // Draw the buttons
        if (ui_button(UI_SIMPLE, "PLAY", rect(btn_x, top_padding, btn_width, btn_height))) {
            self->loop = LOOP_RUNNING;
            DisableCursor();
        }
        else if (ui_button(UI_SIMPLE, "OPTIONS", rect(btn_x, top_padding + btn_spacing, btn_width, btn_height))) {
            self->loop = LOOP_OPTIONS;
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
