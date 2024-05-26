#ifndef OPTIONS_C
#define OPTIONS_C

#include "../game.c"
#include "../game/main.c"

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
        DrawTexturePro(
            textures[TXT_NEPTUNE_SURFACE],
            rect(x, 0, textures[TXT_NEPTUNE_SURFACE].width, 40),
            rect(0, 0, ctx.window_width, ctx.window_height),
            vec2(0, 0), 0.0, bg_tint
        );

        const char* title = "OptioNs";

        float title_size = ctx.window_width * 0.05;
        v2 title_dims = MeasureTextEx(fonts[FNT_DOOMED], title, title_size, 1.0);
        float title_x = (ctx.window_width - title_dims.x) / 2.0;

        // Draw the text
        DrawTextEx(fonts[FNT_DOOMED], title, vec2(title_x, 30.0), title_size, 1.0, WHITE);

        bool returning_to_game = self->loop == LOOP_PAUSED_OPTIONS;
        bool go_back = GuiLabelButton(rect(10, 10, 150, 50), returning_to_game? "< BACK TO GAME" : "< BACK TO MENU") ||
                       IsKeyPressed(KEY_ESCAPE);
                       
        if (go_back) self->loop = returning_to_game? LOOP_PAUSED : LOOP_MENU;

        // ************************************************************* //
        // controls
        static int changed;
        static const char* text;

        // Slider (volume)
        Rectangle bounds = {
            .x = 170,
            .y = 200,
            .width = ctx.window_width / 3,
            .height = 30.0,
        };

        float volume = settings.volume;
        changed = GuiSlider(bounds, "Volume ", 0, &volume, VOLUME_MIN, VOLUME_MAX);

        settings.volume = (int)volume;

        if (changed) SetMasterVolume(settings.volume);

        text = TextFormat(" %u%%", (uint32_t)settings.volume);
        GuiLabel(rect(bounds.x + bounds.width, bounds.y, 100.0, 30.0), text);

        // ************************************************************* //
        // Slider (FPS)
        bounds.y += bounds.height + 10;

        float fps = settings.frame_limit;
        changed = GuiSlider(bounds, "FPS Limit ", 0, &fps, FPS_MIN, FPS_MAX);

        settings.frame_limit = (uint32_t)fps;
        
        if (changed) SetTargetFPS(settings.frame_limit);

        text = TextFormat(" %u", settings.frame_limit);

        GuiLabel(rect(bounds.x + bounds.width, bounds.y, 100.0, 30.0), text);

        // ************************************************************* //
        // Slider (sens)
        bounds.y += bounds.height + 10;

        float sens = settings.sensitivity;
        GuiSlider(bounds, "Sensitivity ", 0, &sens, SENS_MIN, SENS_MAX);

        settings.sensitivity = (uint32_t)sens;

        text = TextFormat(" %u", settings.sensitivity);

        GuiLabel(rect(bounds.x + bounds.width, bounds.y, 100.0, 30.0), text);


        // ************************************************************* //
        // Slider (fov)
        bounds.y += bounds.height + 10;

        float fov = main_camera.fovy;
        GuiSlider(bounds, "FOV ", 0, &fov, FOV_MIN, FOV_MAX);

        main_camera.fovy = (int)fov;

        text = TextFormat(" %u", (unsigned)main_camera.fovy);

        GuiLabel(rect(bounds.x + bounds.width, bounds.y, 100.0, 30.0), text);

        // ************************************************************* //
        // Toggles
        bounds.y += bounds.height * 2 + 10;

        changed = GuiToggle(bounds, "Antialiasing", &settings.antialiasing);

        if (changed) {
            ClearWindowState(FLAG_MSAA_4X_HINT);
            if (settings.antialiasing) SetWindowState(FLAG_MSAA_4X_HINT);
        }

        GuiLabel(rect(bounds.x + bounds.width, bounds.y, 100.0, 30.0), settings.antialiasing? " On" : " Off");

        debug_fps();
    EndDrawing();
}

#endif // OPTIONS_C