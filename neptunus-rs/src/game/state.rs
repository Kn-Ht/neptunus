use crate::{screen_height, screen_width, vec2, Mouse, Vector2};

pub struct State {
    screen_width: i32,
    screen_height: i32,
    mouse: Mouse
}

impl State {
    pub const fn new() -> Self {
        Self {
            screen_width: 0,
            screen_height: 0,
            mouse: Mouse {
                delta: vec2(0., 0.),
                position: vec2(0., 0.),
                left_down: false,
                right_down: false,
                scroll_move: 0.0
            }
        }
    }

    pub fn update(&mut self) {
        self.screen_width = screen_width();
        self.screen_height = screen_height();
        self.mouse.update();
    }
}