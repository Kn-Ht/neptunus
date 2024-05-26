#ifndef GAME_C
#define GAME_C

#include "game/context.h"
#include "game/assets.c"
#include "game/settings.c"
#include "raywrapper.h"
#include "ui/monitor_info.h"
#include "ui/style.c"

#if DEBUG
#  define WINDOW_TITLE "Neptunus (DEBUG) [" __DATE__ "  ~  " __TIME__ "]"
#else
#  define WINDOW_TITLE "Neptunus"
#endif

typedef enum {
    LOOP_MENU,
    LOOP_OPTIONS,
    LOOP_RUNNING,
    LOOP_PAUSED,
    LOOP_PAUSED_OPTIONS,
} GameLoop;

typedef struct Game {
    GameLoop loop;
    bool should_close;
} Game;

#include "game/main.c"
#include "ui/menu.c"

Game game_init() {
    return (Game) { .loop = LOOP_MENU, .should_close = false };
}

void game_start(Game* self) {
    uint32_t flags = FLAG_WINDOW_RESIZABLE;
    if (settings.antialiasing) flags |= FLAG_MSAA_4X_HINT;

    SetConfigFlags(flags);
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

    // Set the state
    apply_settings();

    // prepare the menu screen
    prepare_menu();
}

/// Close the window and all related
void game_close(Game* self) {
    EnableCursor();
    CloseWindow();
    CloseAudioDevice();
}

/// Free all allocated objects
void game_deinit(Game* self) {
    unload_assets();
}

bool game_running(Game* self) {
    return !(WindowShouldClose() || self->should_close);
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
        case LOOP_PAUSED_OPTIONS:
        case LOOP_OPTIONS: {
            loop_options(self);
        } break;
        case LOOP_PAUSED:
        case LOOP_RUNNING: {
            loop_running(self);
        } break;
        default: {}
    }
}

#endif // GAME_C
