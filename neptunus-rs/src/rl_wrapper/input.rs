use raylib_ffi::{enums::MouseButton, Vector2};

use crate::{return_wrap, vec2};

return_wrap! {
    mouse_wheel_move -> f32 = GetMouseWheelMove,
    last_key_pressed -> i32 = GetKeyPressed,
    mouse_delta -> Vector2 = GetMouseDelta,
}

pub struct Mouse {
    pub position: Vector2,
    pub left_down: bool,
    pub right_down: bool,
    pub scroll_move: f32,
    pub delta: Vector2,
}

impl Mouse {
    pub fn get() -> Self {
        let mut s = Self {position: vec2(0., 0.), left_down: false, right_down: false, scroll_move: 0., delta: vec2(0., 0.)};
        s.update();
        s
    }
    pub fn update(&mut self) {
        self.position = Self::position();
        self.left_down = Self::is_down(MouseButton::Left);
        self.right_down = Self::is_down(MouseButton::Right);
        self.scroll_move = Self::scroll_move();
        self.delta = Self::delta();
    }
    pub fn position() -> Vector2 {
        unsafe {
            raylib_ffi::GetMousePosition()
        }
    }
    pub fn scroll_move() -> f32 {
        unsafe {
            raylib_ffi::GetMouseWheelMove()
        }
    }
    pub fn delta() -> Vector2 {
        unsafe {
            raylib_ffi::GetMouseDelta()
        }
    }
    pub fn is_down(mouse_button: MouseButton) -> bool {
        unsafe {
            raylib_ffi::IsMouseButtonDown(mouse_button as i32)
        }
    }
    pub fn is_pressed(mouse_button: MouseButton) -> bool {
        unsafe {
            raylib_ffi::IsMouseButtonPressed(mouse_button as i32)
        }
    }
    pub fn is_released(mouse_button: MouseButton) -> bool {
        unsafe {
            raylib_ffi::IsMouseButtonReleased(mouse_button as i32)
        }
    }
}