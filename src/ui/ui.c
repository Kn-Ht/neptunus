#ifndef UI_C
#define UI_C

#include <stdbool.h>

typedef enum {
    UI_SIMPLE = 0,
} UI_Style;

bool ui_button(UI_Style style, int x, int y, const char* text) {
    switch (style) {
        case UI_SIMPLE: {
            
        } break;
    }
}

#endif // UI_C