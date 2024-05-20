use std::ffi::{c_char, CString};

pub struct Font(raylib_ffi::Font);

crate::drop_impl!(Font: UnloadFont);

#[derive(Clone, Copy, Debug)]
pub enum FontType {
    TTF,
    OTF,
    FNT,
}

impl FontType {
    fn as_ptr(self) -> *const c_char {
        match self {
            Self::TTF => ".ttf\0",
            Self::FNT => ".fnt\0",
            Self::OTF => ".otf\0",
        }
        .as_ptr() as *const i8
    }
}

impl Font {
    pub fn load(path: impl AsRef<str>) -> anyhow::Result<Self> {
        let path_cstr = CString::new(path.as_ref())?;
        Ok(Self(unsafe { raylib_ffi::LoadFont(path_cstr.as_ptr()) }))
    }
    pub fn load_bytes(
        bytes: &[u8],
        filetype: FontType,
        font_size: i32,
        codepoints: Option<&mut i32>,
        codepoint_count: i32,
    ) -> Self {
        Self(unsafe {
            raylib_ffi::LoadFontFromMemory(
                filetype.as_ptr(),
                bytes.as_ptr(),
                bytes.len() as i32,
                font_size,
                codepoints
                    .and_then(|c| Some(c as *mut i32))
                    .unwrap_or(std::ptr::null_mut()),
                codepoint_count,
            )
        })
    }
}
