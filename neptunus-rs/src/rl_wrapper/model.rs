use std::ffi::CString;

use raylib_ffi::{Color, Matrix, Vector3};

use super::prelude::Texture;

pub struct Model(raylib_ffi::Model);

crate::drop_impl!(Model: UnloadModel);

impl Model {
    pub fn load(path: impl AsRef<str>) -> anyhow::Result<Self> {
        let path_cstr = CString::new(path.as_ref())?;
        Ok(Self(unsafe { raylib_ffi::LoadModel(path_cstr.as_ptr()) }))
    }
    pub fn set_transform(&mut self, matrix: Matrix) {
        self.0.transform = matrix;
    }
    pub fn draw(&self, position: Vector3, scale: f32, tint: Color) {
        unsafe {
            raylib_ffi::DrawModel(self.0, position, scale, tint);
        }
    }
    pub fn set_material_texture(&mut self, texture: Texture) {
        unsafe {
            raylib_ffi::SetMaterialTexture(&mut self.0.materials[0]);
        }
    }
}
