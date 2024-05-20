use std::ffi::CString;

pub struct Image(raylib_ffi::Image);
pub struct Texture(raylib_ffi::Texture);
pub type Texture2D = Texture;

crate::drop_impl!(Texture: UnloadTexture);

impl From<Image> for Texture {
    fn from(value: Image) -> Self {
        Self(
            unsafe {
                raylib_ffi::LoadTextureFromImage(value.0)
            }
        )
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
        format!("{}\0", self.as_str()).as_ptr() as *const i8
    }
}

// Impls
impl Image {
    pub fn from_file(path: impl AsRef<str>) -> anyhow::Result<Self> {
        let path_cstr = CString::new(path.as_ref())?;
        Ok(Image(unsafe { raylib_ffi::LoadImage(path_cstr.as_ptr()) }))
    }
    pub fn from_bytes(bytes: &[u8], filetype: ImageType) -> Self {
        Self(
            unsafe {
                raylib_ffi::LoadImageFromMemory(
                    filetype.as_ptr(),
                    bytes.as_ptr(),
                    bytes.len() as i32
                )
            }
        )
    }
}