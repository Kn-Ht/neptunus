use std::ffi::CString;

pub struct Model(raylib_ffi::Model);

crate::drop_impl!(Model: UnloadModel);

impl Model {
    pub fn load(path: impl AsRef<str>) -> anyhow::Result<Self> {
        let path_cstr = CString::new(path.as_ref())?;
        Ok(Self(unsafe {
            raylib_ffi::LoadModel(path_cstr.as_ptr())
        }))
    }
}