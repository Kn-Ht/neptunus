#ifndef GAME_C
#define GAME_C

#include "game/state.h"
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
    LOOP_RUNNING,
    LOOP_PAUSED
} GameLoop;

typedef struct Game {
    GameLoop loop_type;
    void (*loop)(struct Game*); // callback
    Assets assets;
} Game;

#include "game/loop.c"

Game game_init() {
    Game game;
    game.loop = &loop_titlescreen;
    game.loop_type = LOOP_TITLESCREEN;
    return game;
}

void game_start(Game* self) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(500, 500, WINDOW_TITLE);
    self->assets = assets_load();
    get_monitor_info();
    SetWindowSize(monitor_info.width / 2, monitor_info.height / 2);
}

void game_close(Game* self) {
    CloseWindow();
}

void game_deinit(Game* self) {
    assets_unload(&(self->assets));
}

bool game_running() {
    return !WindowShouldClose();
}

void game_update(Game* self) {
    update_state();
    self->loop(self);
}

#endif // GAME_C