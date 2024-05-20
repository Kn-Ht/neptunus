#ifndef STATE_H
#define STATE_H

#include "../raywrapper.h"
#include <stdbool.h>

struct GameState {
    int window_width;
    int window_height;
    int last_key;
    Vec2 mouse_pos;
    float mouse_wheel_move;
    bool left_mouse_down;
    bool right_mouse_down;
};

static struct GameState prev_state = {0};
static struct GameState state = {0};
static float dt = 0.0f;

void update_state() {
    prev_state = state;
    
    state.left_mouse_down = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    state.right_mouse_down = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
    state.last_key = GetKeyPressed();
    state.mouse_wheel_move = GetMouseWheelMove();
    state.window_width = GetScreenWidth();
    state.window_height = GetScreenHeight();
    state.mouse_pos = GetMousePosition();
    dt = GetFrameTime();
}

#endif // STATE_H
