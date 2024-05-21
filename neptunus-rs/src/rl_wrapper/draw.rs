use raylib_ffi::{Color, NPatchInfo, Rectangle, Vector2};

use crate::{Circle, Sphere};

macro_rules! wrap {
    ($($fn_name:ident = $equivalent:ident,)+) => {
        $(
            pub fn $fn_name() {
                unsafe {
                    raylib_ffi::$equivalent();
                }
            }
        )*

    };
}

wrap! {
    begin_drawing = BeginDrawing,
    end_drawing = EndDrawing,
    close_window = CloseWindow,
    toggle_fullscreen = ToggleFullscreen,
}

#[macro_export]
macro_rules! draw {
    ($($block:tt)*) => {
        crate::begin_drawing();
        $(
            $block
        )*
        crate::end_drawing();
    };
}

pub fn clear_background(color: raylib_ffi::Color) {
    unsafe {
        raylib_ffi::ClearBackground(color);
    }
}

#[macro_export]
macro_rules! debug_fps {
    () => {
        unsafe {
            if cfg!(debug_assertions) {
                raylib_ffi::DrawFPS(0, 0);
            }
        }
    };
}

// ************** Draw traits **************
pub trait DrawRect {
    fn draw(&self, x: i32, y: i32, w: i32, h: i32, tint: Color);
    fn draw_vec(&self, pos: Vector2, size: Vector2, tint: Color);
    fn draw_rect(&self, bounds: Rectangle, tint: Color);
}

pub trait DrawTexture {
    fn draw(&self, x: i32, y: i32, tint: Color);
    fn draw_vec(&self, pos: Vector2, tint: Color);
    fn draw_ex(&self, pos: Vector2, rotation: f32, scale: f32, tint: Color);
    fn draw_pro(
        &self,
        source: Rectangle,
        dest: Rectangle,
        origin: Vector2,
        rotation: f32,
        tint: Color,
    );
    fn draw_npatch(
        &self,
        npatch_info: NPatchInfo,
        dest: Rectangle,
        origin: Vector2,
        rotation: f32,
        tint: Color,
    );
}

pub trait Draw {
    fn draw(&self, tint: Color);
}

pub trait DrawCircle {
    fn draw(&self, center_x: i32, center_y: i32, radius: f32, color: Color);
    fn draw_sector(
        &self,
        center: Vector2,
        radius: f32,
        start_angle: f32,
        end_angle: f32,
        segments: i32,
        color: Color,
    );
    fn draw_sector_lines(
        &self,
        center: Vector2,
        radius: f32,
        start_angle: f32,
        end_angle: f32,
        segments: i32,
        color: Color,
    );
    fn draw_gradient(
        &self,
        center_x: i32,
        center_y: i32,
        radius: f32,
        color1: Color,
        color2: Color,
    );
}
// *****************************************

impl Draw for Rectangle {
    fn draw(&self, tint: Color) {
        unsafe {
            raylib_ffi::DrawRectangleRec(*self, tint);
        }
    }
}

impl Draw for Sphere {
    fn draw(&self, tint: Color) {
        unsafe {
            raylib_ffi::DrawSphere(self.center_pos, self.radius, tint);
        }
    }
}

impl Draw for Circle {
    fn draw(&self, tint: Color) {
        unsafe {
            raylib_ffi::DrawCircle(
                self.center_pos.x as i32,
                self.center_pos.y as i32,
                self.radius,
                tint,
            );
        }
    }
}

impl DrawTexture for crate::Texture {
    fn draw(&self, x: i32, y: i32, tint: Color) {
        unsafe {
            raylib_ffi::DrawTexture(*self.raw(), x, y, tint);
        }
    }
    fn draw_vec(&self, pos: Vector2, tint: Color) {
        unsafe {
            raylib_ffi::DrawTextureV(*self.raw(), pos, tint);
        }
    }
    fn draw_ex(&self, pos: Vector2, rotation: f32, scale: f32, tint: Color) {
        unsafe {
            raylib_ffi::DrawTextureEx(*self.raw(), pos, rotation, scale, tint);
        }
    }
    fn draw_pro(
        &self,
        source: Rectangle,
        dest: Rectangle,
        origin: Vector2,
        rotation: f32,
        tint: Color,
    ) {
        unsafe {
            raylib_ffi::DrawTexturePro(*self.raw(), source, dest, origin, rotation, tint);
        }
    }
    fn draw_npatch(
        &self,
        npatch_info: NPatchInfo,
        dest: Rectangle,
        origin: Vector2,
        rotation: f32,
        tint: Color,
    ) {
        unsafe {
            raylib_ffi::DrawTextureNPatch(*self.raw(), npatch_info, dest, origin, rotation, tint);
        }
    }
}
