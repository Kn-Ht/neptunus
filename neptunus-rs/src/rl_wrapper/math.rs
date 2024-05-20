use std::ops::{Add, Sub, Mul, Div};

// Math
pub use raylib_ffi::{Rectangle, Vector2, Vector3, Vector4};

pub struct Circle {
    pub center_pos: Vector2,
    pub radius: f32,
}

pub struct Sphere {
    pub center_pos: Vector3,
    pub radius: f32,
}

pub const fn vec2(x: f32, y: f32) -> Vector2 {
    Vector2 { x, y }
}

pub const fn vec3(x: f32, y: f32, z: f32) -> Vector3 {
    Vector3 { x, y, z }
}

pub const fn vec4(x: f32, y: f32, z: f32, w: f32) -> Vector4 {
    Vector4 { x, y, z, w }
}

pub const fn rect(x: f32, y: f32, w: f32, h: f32) -> Rectangle {
    Rectangle {
        x,
        y,
        width: w,
        height: h,
    }
}

pub const fn sphere(center_x: f32, center_y: f32, center_z: f32, radius: f32) -> Sphere {
    Sphere {
        center_pos: vec3(center_x, center_y, center_z),
        radius
    }
}

pub const fn sphere_v(center_pos: Vector3, radius: f32) -> Sphere {
    Sphere {
        center_pos, radius
    }
}


pub const fn circle(center_x: f32, center_y: f32, radius: f32) -> Circle {
    Circle {
        center_pos: vec2(center_x, center_y),
        radius
    }
}

pub const fn circle_v(center_pos: Vector2, radius: f32) -> Circle {
    Circle {
        center_pos, radius

    }
}

// Operations