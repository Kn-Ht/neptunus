#ifndef GAME_C
#define GAME_C

#include "game/context.h"
#include "game/assets.c"
#include "game/settings.c"
#include "raywrapper.h"
#include "ui/monitor_info.h"

#if DEBUG
#  define WINDOW_TITLE "Neptunus (DEBUG) [" __DATE__ "  ~  " __TIME__ "]"
#else
#  define WINDOW_TITLE "Neptunus"
#endif

typedef enum {
    LOOP_MENU,
    LOOP_OPTIONS,
    LOOP_RUNNING,
    LOOP_PAUSED
} GameLoop;

typedef struct Game {
    GameLoop loop;
    Settings settings;
} Game;

#include "ui/ui.c"
#include "game/loop.c"

Game game_init() {
    return (Game) { .loop = LOOP_MENU, .settings = settings_default() };
}

void game_start(Game* self) {
    // give the ui a handle to `self`
    ui_game_ptr = self;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(200);
    InitWindow(500, 500, WINDOW_TITLE);
    // The window must be opened for assets and monitor info te be loaded.
    load_assets();

    get_monitor_info();

    // Load UI style
    GuiLoadStyleDark();

    int min_w = monitor_info.width / 2;
    int min_h = monitor_info.height / 2;

    SetWindowMinSize(min_w, min_h);
    SetWindowSize(min_w, min_h);
    SetExitKey(0);

    // Start the audio service
    InitAudioDevice();
}

void game_close(Game* self) {
    EnableCursor();
    CloseWindow();
    CloseAudioDevice();
}

void game_deinit(Game* self) {
    unload_assets();
}

bool game_running() {
    return !WindowShouldClose();
}

void game_update(Game* self) {
    update_ctx();

#ifdef DEBUG
    if (IsKeyPressed(KEY_F5)) { // reload assets
        unload_assets();
        load_assets();
    }
#endif

    switch (self->loop) {
        case LOOP_MENU: {
            loop_menu(self);
        } break;
        case LOOP_OPTIONS: {
            loop_options(self);
        } break;
        case LOOP_RUNNING: {
            loop_running(self);
        } break;
        default: {}
    }
}

#endif // GAME_C
