#ifndef UI_C
#define UI_C

#include "../game.c"
#include "../game/state.h"
#include "../raywrapper.h"
#include <stdbool.h>

typedef enum {
    UI_SIMPLE = 0,
} UI_Style;

static struct Game *ui_game_ptr = NULL;

bool ui_button(UI_Style style, const char *text, Rect bounds) {
    bool hovered = CheckCollisionPointRec(state.mouse_pos, bounds);
    bool clicked = hovered && state.left_mouse_down;

    Font *font = &(ui_game_ptr->assets.fonts.doomed);

    // button colors
    Color bg, fg, border;

    float font_size = 0.1 * bounds.width;

    // Where to place the text?
    Vec2 text_size = MeasureTextEx(*font, text, font_size, 1.0);

    Vec2 text_pos = {
        .x = bounds.x + ((bounds.width / 2.0f)  - text_size.x),
        .y = bounds.y + ((bounds.height / 2.0f) - text_size.y)
    };

    switch (style) {
    case UI_SIMPLE: {
        if (clicked) {}
        else if (hovered) {}
        else {
            bg = BLACK;
            fg = WHITE;
            border = RAYWHITE;

            DrawRectangleRec(bounds, bg);
            DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, border);
            DrawTextEx(*font, text, text_pos, font_size, 1.0, fg);
        }
    } break;
    default: {}
    }
}

#endif // UI_C
