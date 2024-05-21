use raylib_ffi::{
    enums::{CameraMode, CameraProjection},
    Vector3,
};

pub struct Camera2D(raylib_ffi::Camera2D);
pub struct Camera3D(raylib_ffi::Camera3D);

impl Camera3D {
    pub const fn new(
        position: Vector3,
        target: Vector3,
        up: Vector3,
        fovy: f32,
        projection: CameraProjection,
    ) -> Self {
        Self(raylib_ffi::Camera3D {
            position,
            target,
            up,
            fovy,
            projection: projection as i32,
        })
    }

    pub fn scene<F: Fn(&mut Self)>(&mut self, f: F) {
        unsafe {
            raylib_ffi::BeginMode3D(self.0);
        }
        f(self);
        unsafe {
            raylib_ffi::EndMode3D();
        }
    }
    /// Prefer to use Camera3D::scene()
    pub fn begin_mode3D(&self) {
        unsafe {
            raylib_ffi::BeginMode3D(self.0);
        }
    }
    /// call after begin_mode3D()
    pub fn end_mode3D(&self) {
        unsafe {
            raylib_ffi::EndMode3D();
        }
    }
    pub fn update(&mut self, mode: CameraMode) {
        unsafe {
            raylib_ffi::UpdateCamera(&mut self.0, mode as i32);
        }
    }
    pub fn update_pro(&mut self, movement: Vector3, rotation: Vector3, zoom: f32) {
        unsafe {
            raylib_ffi::UpdateCameraPro(&mut self.0, movement, rotation, zoom);
        }
    }
}
