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
        .fovy = 60,
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

    int out_width_loc = GetShaderLocation(shaders[SHD_PIXELATE], "renderWidth");
    int out_height_loc = GetShaderLocation(shaders[SHD_PIXELATE], "renderHeight");

    SetShaderValue(shaders[SHD_PIXELATE], out_width_loc, &ctx.window_width, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders[SHD_PIXELATE], out_height_loc, &ctx.window_height, SHADER_UNIFORM_FLOAT);

    BeginTextureMode(render_texture);
        BeginShaderMode(shaders[SHD_PIXELATE]);
            ClearBackground(BLACK);

            BeginMode3D(camera);
                DrawModel(objects[OBJ_NEPTUNE], vec3(0.0f, 0.0f, 5.0f), 10.0f, WHITE);
            EndMode3D();

        EndShaderMode();
    EndTextureMode();

    BeginDrawing();
        ClearBackground(BLACK);
        // Draw background
        DrawTextureRec(textures[TXT_STARS], rect(0, 0, ctx.window_width, ctx.window_height), vec2(0, 0), WHITE);

        DrawTexturePro(
            render_texture.texture, rect(
                0, 0, render_texture.texture.width, render_texture.texture.height
            ),
            rect(0, 0, ctx.window_width, ctx.window_height),
            vec2(0, 0),
            0.0,
            WHITE
        );

        const char* title = "NeptuNus";

        float title_size = ctx.window_width * 0.1;
        Vector2 title_dims = MeasureTextEx(fonts[FNT_DOOMED], title, title_size, 1.0);
        float title_x = (ctx.window_width - title_dims.x) / 2.0;

        // Draw the text
        DrawTextEx(fonts[FNT_DOOMED], title, vec2(title_x, 30.0), title_size, 1.0, WHITE);

        // button dimensions
        float top_padding = title_size + 40.0f;
        float btn_width = title_size * 2.3;
        float btn_height = title_size * 0.3f;
        float btn_spacing = btn_height + 10.0 * 2.0;
        float btn_x = (ctx.window_width - btn_width) / 2.0;

        // Draw the buttons
        if (GuiButton(rect(btn_x, top_padding, btn_width, btn_height), "PLAY")) {
            self->loop = LOOP_RUNNING;
            DisableCursor();
        }
        else if (GuiButton(rect(btn_x, top_padding + btn_spacing, btn_width, btn_height), "OPTIONS")) {
            self->loop = LOOP_OPTIONS;
        }

        debug_fps();
    EndDrawing();
}

void loop_options(Game* self) {
    static Color bg_tint = {
        .r = 150,
        .g = 150,
        .b = 150,
        .a = 255,
    };

    static float x = 0.0;
    x = (x > textures[TXT_NEPTUNE_SURFACE].width)? 0.0f : x + 100 * dt;

    BeginDrawing();
        ClearBackground(BLACK);
        GuiSlider(rect(20, 200, 100, 50), "Left", "Right", &(self->settings.volume), 0.0, 100.0);
    EndDrawing();
    return;

        DrawTexturePro(
            textures[TXT_NEPTUNE_SURFACE],
            rect(x, 0, textures[TXT_NEPTUNE_SURFACE].width, 40),
            rect(0, 0, ctx.window_width, ctx.window_height),
            vec2(0, 0), 0.0, bg_tint
        );

        const char* title = "OptioNs";

        float title_size = ctx.window_width * 0.05;
        Vector2 title_dims = MeasureTextEx(fonts[FNT_DOOMED], title, title_size, 1.0);
        float title_x = (ctx.window_width - title_dims.x) / 2.0;

        // Draw the text
        DrawTextEx(fonts[FNT_DOOMED], title, vec2(title_x, 30.0), title_size, 1.0, WHITE);

        if (GuiLabelButton(rect(10, 10, 150, 50), "< BACK TO MENU")) {
            self->loop = LOOP_MENU;
        }

        // ************************************************************* //
        Rectangle slider_bounds;
        slider_bounds.width = 100.0;
        slider_bounds.height = 50.0;
        slider_bounds.x = ctx.window_width / 2.0;
        slider_bounds.y = ctx.window_height / 3.0 - slider_bounds.height;

        


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
