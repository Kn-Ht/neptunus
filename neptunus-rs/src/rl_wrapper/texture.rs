use std::ffi::CString;

pub struct Image(raylib_ffi::Image);
pub struct Texture(raylib_ffi::Texture);
pub type Texture2D = Texture;

crate::drop_impl!(Texture: UnloadTexture);

pub use raylib_ffi::NPatchInfo;
use raylib_ffi::Rectangle;

use super::prelude::rect;

impl From<Image> for Texture {
    fn from(value: Image) -> Self {
        Self(unsafe { raylib_ffi::LoadTextureFromImage(value.0) })
    }
}

#[derive(Clone, Copy)]
pub enum ImageType {
    PNG,
    BMP,
    TGA,
    GIF,
    QOI,
    PSD,
    DDS,
    HDR,
    KTX,
    ASTC,
    PKM,
    PVR,
}

impl ImageType {
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::PNG => ".png",
            Self::BMP => ".bmp",
            Self::TGA => ".tga",
            Self::GIF => ".gif",
            Self::QOI => ".qoi",
            Self::PSD => ".psd",
            Self::DDS => ".dds",
            Self::HDR => ".hdr",
            Self::KTX => ".ktx",
            Self::ASTC => ".astc",
            Self::PKM => ".pkm",
            Self::PVR => ".pvr",
        }
    }
    pub fn as_ptr(self) -> *const i8 {
        match self {
            Self::PNG => ".png\0",
            Self::BMP => ".bmp\0",
            Self::TGA => ".tga\0",
            Self::GIF => ".gif\0",
            Self::QOI => ".qoi\0",
            Self::PSD => ".psd\0",
            Self::DDS => ".dds\0",
            Self::HDR => ".hdr\0",
            Self::KTX => ".ktx\0",
            Self::ASTC => ".astc\0",
            Self::PKM => ".pkm\0",
            Self::PVR => ".pvr\0",
        }
        .as_ptr() as *const i8
    }
}

// Impls
impl Image {
    pub fn raw(&self) -> &raylib_ffi::Image {
        &self.0
    }
    pub const fn width(&self) -> i32 {
        self.0.width
    }
    pub const fn height(&self) -> i32 {
        self.0.height
    }
    pub fn from_file(path: impl AsRef<str>) -> anyhow::Result<Self> {
        let path_cstr = CString::new(path.as_ref())?;
        Ok(Image(unsafe { raylib_ffi::LoadImage(path_cstr.as_ptr()) }))
    }
    pub fn from_bytes(bytes: &[u8], filetype: ImageType) -> Self {
        Self(unsafe {
            raylib_ffi::LoadImageFromMemory(filetype.as_ptr(), bytes.as_ptr(), bytes.len() as i32)
        })
    }
}

impl Texture {
    pub fn raw(&self) -> &raylib_ffi::Texture {
        &self.0
    }
    pub const fn width(&self) -> i32 {
        self.0.width
    }
    pub const fn height(&self) -> i32 {
        self.0.height
    }
    pub const fn bounds(&self) -> Rectangle {
        rect(0., 0., self.width() as f32, self.height() as f32)
    }
}
