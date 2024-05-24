#ifndef UI_C
#define UI_C

#include "../game.c"
#include "../game/context.h"
#include "../raywrapper.h"
#include "style.c"
#include <stdbool.h>

typedef enum {
    UI_SIMPLE = 0,
} UI_Style;

static struct Game *ui_game_ptr = NULL;

bool ui_button(UI_Style style, const char *text, Rect bounds) {
    bool hovered = CheckCollisionPointRec(ctx.mouse_pos, bounds);
    bool clicked =
        hovered && prev_ctx.left_mouse_down && !prev_ctx.left_mouse_down;

    Font *font = &(ui_game_ptr->assets.fonts.doomed);

    // button colors
    Color bg = BLACK, fg = WHITE, border;

    float font_size = 0.1 * bounds.width;

    // Where to place the text?
    Vec2 text_size = MeasureTextEx(*font, text, font_size, 1.0);

    Vec2 text_pos = {.x = bounds.x + ((bounds.width - text_size.x) / 2.0f),
                     .y = bounds.y + ((bounds.height - text_size.y) / 2.0f)};

    switch (style) {
    case UI_SIMPLE: {
        if (clicked) {
            border = RED;
            fg = RED;

            DrawRectangleRec(bounds, bg);
            DrawRectangleLinesEx(bounds, 2.0, border);
            DrawTextEx(*font, text, text_pos, font_size, 1.0, fg);

            printf("Hello\n");
            return true;
        } else if (hovered) {
            border = color_rgb(0, 162, 211);

            DrawRectangleRec(bounds, bg);
            DrawRectangleLinesEx(bounds, 2.0, border);
            DrawTextEx(*font, text, text_pos, font_size, 1.0, fg);
        } else {
            border = RAYWHITE;

            DrawRectangleRec(bounds, bg);
            DrawRectangleLinesEx(bounds, 2.0, border);
            DrawTextEx(*font, text, text_pos, font_size, 1.0, fg);
        }
    } break;
    default: {
    }
    }

    return false;
}

int ui_slider(UI_Style style, const char *text, int min, int max, int start_val,
              Rect bounds) {}

#endif // UI_C
