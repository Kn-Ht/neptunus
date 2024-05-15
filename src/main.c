#include "game.c"

int main(void) {
    Game game = game_init();

    game_start(&game);

    while (game_running()) {
        game_update(&game);   
    }

    game_close(&game);
    game_deinit(&game);
}
