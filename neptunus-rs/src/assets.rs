use raylib_ffi::{enums::MaterialMapIndex, MaterialMap};

use crate::{Font, Image, Model, Object, Texture};

use self::textures::NEPTUNE_SURFACE;

macro_rules! include_assets {
    ($($name:ident: $path:literal),*) => {
        $(
            pub const $name: &[u8] = include_bytes!(concat!("../assets/", $path));
        )*
    };
}

pub mod fonts {
    include_assets!(DOOMED: "fonts/doomed.ttf");
}

pub mod bg {
    include_assets!(STARS: "bg/stars.png");
}

pub mod models {
    include_assets!(NEPTUNE: "models/neptune.obj");
}

pub mod textures {
    include_assets!(NEPTUNE_SURFACE: "textures/2k_neptune.png");
}

pub mod icons {
    include_assets!(ICON_BIG: "icons/icon-big.ico");
}

pub struct Fonts {
    pub doomed: Font,
}

pub struct Backgrounds {
    pub stars: Texture,
}

pub struct Objects {
    pub neptune: Object,
}

pub struct Icons {
    pub big: Image,
}

pub struct Sounds {}

pub struct Music {}

pub struct Assets {
    pub fonts: Fonts,
    pub bg: Backgrounds,
    pub objects: Objects,
    pub icons: Icons,
    pub sounds: Sounds,
    pub music: Music,
}

impl Assets {
    pub fn load() -> Self {
        Self {
            fonts: Fonts {
                doomed: Font::load_bytes(fonts::DOOMED, crate::FontType::TTF, 100, None, 0),
            },
            bg: Backgrounds {
                stars: Texture::from(Image::from_bytes(bg::STARS, crate::ImageType::PNG)),
            },
            objects: Objects {
                neptune: Object::new(
                    Model::load("assets/models/neptune.obj").unwrap(), // FIXME
                    Texture::from(Image::from_bytes(NEPTUNE_SURFACE, crate::ImageType::PNG))
                )

            },
            icons: Icons {
                big: Image::from_bytes(icons::ICON_BIG, crate::ImageType::PNG),
            },
            sounds: Sounds {},
            music: Music {},
        }
    }
}
