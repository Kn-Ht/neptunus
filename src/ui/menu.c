#ifndef MENU_C
#define MENU_C

#include "../game.c"

static int light_location;

void prepare_menu() {
    Shader shader = shaders[SHD_LIGHTING];

    light_location = GetShaderLocation(shader, "lightDir");
    objects[OBJ_NEPTUNE].materials[0].shader = shader;
}

void loop_menu(Game* self) {
    static Camera3D camera = {
        .fovy = 60,
        .position = {15.0f, 1.0f, 10.0f},
        .projection = CAMERA_PERSPECTIVE,
        .target = {0.0f, 0.0f, 12.0f},
        .up = {0.0f, 1.0f, 0.0f}
    };

    static v3 light = {
        0.0f, 1.0f, -1.0f
    };

    // Make the planet rotate
    float rotation_speed = 2.0f;
    static float rotation = 0.0f;

    // increment rotation until it has fully rotated
    if (rotation > 360.0f) rotation = 0.0f; 
    else rotation += rotation_speed * dt;

    objects[OBJ_NEPTUNE].transform = MatrixRotateY(DEG2RAD*rotation);

    // draw to texture
#ifdef DEBUG
    SetShaderValue(shaders[SHD_LIGHTING], light_location, &light, SHADER_UNIFORM_VEC3);
#endif

    BeginDrawing();
        ClearBackground(BLACK);
        // Draw background
        DrawTextureRec(textures[TXT_STARS], rect(0, 0, ctx.window_width, ctx.window_height), vec2(0, 0), WHITE);

        BeginMode3D(camera);
            DrawModel(objects[OBJ_NEPTUNE], vec3(0.0f, 0.0f, 5.0f), 10.0f, WHITE);
        EndMode3D();

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
        v2 title_dims = MeasureTextEx(fonts[FNT_DOOMED], title, title_size, 1.0);
        float title_x = (ctx.window_width - title_dims.x) / 2.0;

        // Draw the text
        DrawTextEx(fonts[FNT_DOOMED], title, vec2(title_x, 30.0), title_size, 1.0, WHITE);

        // button dimensions
        float top_padding = title_size + 40.0f;

        Rectangle button_bounds = {
            .width = title_size * 2.3,
            .height = title_size * 0.3f,
            .y = top_padding
        };
        button_bounds.x = (ctx.window_width - button_bounds.width) / 2.0;

        float btn_spacing = button_bounds.height + 10.0 * 2.0;

        // Draw the buttons
        if (GuiButton(button_bounds, "PLAY")) {
            self->loop = LOOP_RUNNING;
            DisableCursor();
        }
        button_bounds.y += btn_spacing;
        if (GuiButton(button_bounds, "OPTIONS")) {
            self->loop = LOOP_OPTIONS;
        }
        button_bounds.y += btn_spacing;
        if (GuiButton(button_bounds, "EXIT")) {
            self->should_close = true;
        }

        debug_fps();
    EndDrawing();
}

#endif // MENU_C