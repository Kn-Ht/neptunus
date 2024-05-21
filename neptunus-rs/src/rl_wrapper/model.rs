use std::ffi::CString;

use raylib_ffi::{enums::MaterialMapIndex, Color, Matrix, Vector3};

use super::prelude::Texture;

pub struct Model(raylib_ffi::Model);

crate::drop_impl!(Model: UnloadModel);

pub trait ModelDraw {
    fn draw(&self, position: Vector3, scale: f32, tint: Color);
}

impl Model {
    pub fn raw(&self) -> &raylib_ffi::Model {
        &self.0
    }
    pub fn load(path: impl AsRef<str>) -> anyhow::Result<Self> {
        let path_cstr = CString::new(path.as_ref())?;
        Ok(Self(unsafe { raylib_ffi::LoadModel(path_cstr.as_ptr()) }))
    }
    pub fn set_transform(&mut self, matrix: Matrix) {
        self.0.transform = matrix;
    }
    pub fn set_material_texture(&mut self, texture: &Texture, material_map: MaterialMapIndex) {
        unsafe {
            raylib_ffi::SetMaterialTexture(
                &mut *self.0.materials,
                material_map as i32,
                *texture.raw(),
            );
        }
    }
}

impl ModelDraw for Model {
    fn draw(&self, position: Vector3, scale: f32, tint: Color) {
        unsafe {
            raylib_ffi::DrawModel(self.0, position, scale, tint);
        }
    }
}

pub struct Object {
    pub model: Model,
    pub texture: Texture,
}

impl ModelDraw for Object {
    fn draw(&self, position: Vector3, scale: f32, tint: Color) {
        unsafe {
            raylib_ffi::DrawModel(self.model.0, position, scale, tint);
        }
    }
}

impl Object {
    pub fn new(mut model: Model, texture: Texture) -> Self {
        model.set_material_texture(&texture, MaterialMapIndex::Albedo);
        Self { model, texture }
    }
}
