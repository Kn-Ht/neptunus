#ifndef CTX_H
#define CTX_H

#include "../raywrapper.h"
#include <stdbool.h>

struct Context {
    int window_width;
    int window_height;
    int last_key;
    Vec2 mouse_pos;
    float mouse_wheel_move;
    bool left_mouse_down;
    bool right_mouse_down;
};

static struct Context prev_ctx = {0};
static struct Context ctx = {0};
static float dt = 0.0f;

void update_ctx() {
    prev_ctx = ctx;
    
    ctx.left_mouse_down = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    ctx.right_mouse_down = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
    ctx.last_key = GetKeyPressed();
    ctx.mouse_wheel_move = GetMouseWheelMove();
    ctx.window_width = GetScreenWidth();
    ctx.window_height = GetScreenHeight();
    ctx.mouse_pos = GetMousePosition();
    dt = GetFrameTime();
}

#endif // CTX_H
