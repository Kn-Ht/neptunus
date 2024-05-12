#ifndef GAME_C
#define GAME_C

typedef struct Game Game;

#include "game/state.h"
#include "game/loop.c"
#include "game/assets.c"
#include "raywrapper.h"
#include "ui/monitor_info.h"

struct Game {
    GameLoop loop_type;
    void (*loop)(struct Game*); // callback
    Assets assets;
};

Game game_init() {
    Game game;
    game.loop = &loop_titlescreen;
    game.loop_type = LOOP_TITLESCREEN;
    game.assets = assets_load();
    return game;
}

void game_start(Game* self) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
    InitWindow(500, 500, "Neptunus");
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