#ifndef LOOP_C
#define LOOP_C

static Camera main_camera;

#include "../game.c"
#include "view.c"
#include "../ui/options.c"
#include "context.h"
#include "../raywrapper.h"

void loop_options(Game* self);
void loop_running(Game* self);

static RenderTexture titlescreen_target = {0};
static Camera main_camera = {
    .fovy = 90,
    .position = {1.0f, 1.0f, 1.0f},
    .projection = CAMERA_PERSPECTIVE,
    .up = {0.0f, 1.0f, 0.0f}
};

#define camera main_camera

enum GameStage {
    GST_INTRO_SCREEN,
    GST_NORMAL,
};

void loop_running(Game* self) {
    static enum GameStage stage = GST_INTRO_SCREEN;
    static float fade_in_seconds = 5.0;
    static float passed_time = 0.0f;

    switch (stage) {
        case GST_INTRO_SCREEN: {
            if (IsCursorHidden()) EnableCursor();
            float new_passed = passed_time + dt;

            BeginDrawing();
            ClearBackground(BLACK);
            if (new_passed < fade_in_seconds) {
                passed_time = new_passed;

                DrawTextureRec(textures[TXT_NEPTUNE_SURFACE], rect(0, 0, ctx.window_width, ctx.window_height), Vector2Zero(), DARKBLUE);

                DrawRectangle(
                    0, 0, ctx.window_width, ctx.window_height, (Color){0, 0, 0, (5.0 - passed_time) * 51}
                );
            } else {
                DisableCursor();
                stage = GST_NORMAL;
            }
            EndDrawing();

        } return;
        default: {}
    }

    bool paused = self->loop == LOOP_PAUSED;

    if (IsKeyPressed(KEY_ESCAPE)) {
        if (self->loop == LOOP_RUNNING) {
            self->loop = LOOP_PAUSED;
            EnableCursor();
        } else {
            self->loop = LOOP_RUNNING;
            DisableCursor();
        }
    }

    if (!paused) update_view(&camera);
    
    BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
            DrawPlane(vec3(0, 0, 0), vec2(100, 100), WHITE);
        EndMode3D();

        if (paused) {
            float title_font_size = ctx.window_width * 0.06;

            DrawRectangle(0, 0, ctx.window_width, ctx.window_height, (Color){0, 0, 10, 200});
            v2 text_size = MeasureTextEx(fonts[FNT_DOOMED], "PauSed", title_font_size, 1.0);

            float title_x = (ctx.window_width - text_size.x) / 2;

            DrawTextEx(fonts[FNT_DOOMED], "PauSed", (v2){title_x, 40.0}, title_font_size, 1.0, WHITE);
        
            // Buttons
            Rectangle bounds = {
                .y = 100 + title_font_size,
                .width = ctx.window_width / 2.5,
                .height = 50.0,
            };
            bounds.x = (ctx.window_width - bounds.width) / 2;

            float spacing = bounds.height + 10.0;

            if (GuiButton(bounds, "RESUME")) {
                self->loop = LOOP_RUNNING;
                DisableCursor();
            }
            bounds.y += spacing;
            if (GuiButton(bounds, "OPTIONS")) self->loop = LOOP_PAUSED_OPTIONS;
            bounds.y += spacing;
            if (GuiButton(bounds, "SAVE AND EXIT TO MENU")) {
                self->loop = LOOP_MENU;
            }
        }
        debug_fps();
    EndDrawing();
}

#undef camera
#endif // LOOP_C
