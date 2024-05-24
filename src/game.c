#ifndef GAME_C
#define GAME_C

#include "game/context.h"
#include "game/assets.c"
#include "raywrapper.h"
#include "ui/monitor_info.h"

#if DEBUG
#  define WINDOW_TITLE "Neptunus (DEBUG) [" __DATE__ "  ~  " __TIME__ "]"
#else
#  define WINDOW_TITLE "Neptunus"
#endif

typedef enum {
    LOOP_TITLESCREEN,
    LOOP_OPTIONS,
    LOOP_RUNNING,
    LOOP_PAUSED
} GameLoop;

typedef struct Game {
    GameLoop loop_type;
    void (*loop)(struct Game*); // callback
    Assets assets;
} Game;

#include "ui/ui.c"

#include "game/loop.c"

Game game_init() {
    return (Game) { .loop_type = LOOP_TITLESCREEN, .loop = &loop_titlescreen };
}

void game_start(Game* self) {
    // give the ui a handle to `self`
    ui_game_ptr = self;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(200);
    InitWindow(500, 500, WINDOW_TITLE);
    // The window must be opened for assets and monitor info te be loaded.
    self->assets = assets_load();
    get_monitor_info();

    // Load UI style
    GuiLoadStyleDark();

    int min_w = monitor_info.width / 2;
    int min_h = monitor_info.height / 2;

    SetWindowMinSize(min_w, min_h);
    SetWindowSize(min_w, min_h);
    SetExitKey(0);
}

void game_close(Game* self) {
    EnableCursor();
    CloseWindow();
}

void game_deinit(Game* self) {
    assets_unload(&(self->assets));
}

bool game_running() {
    return !WindowShouldClose();
}

void game_update(Game* self) {
    update_ctx();
    self->loop(self);
}

#endif // GAME_C
