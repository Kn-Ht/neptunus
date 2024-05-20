use crate::{Font, Image, Model, Texture};

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
    doomed: Font
}

pub struct Backgrounds {
    stars: Texture
}

pub struct Models {
    neptune: Model
}

pub struct Icons {
    big: Image
}

pub struct Sounds {

}

pub struct Music {

}

pub struct Assets {
    fonts: Fonts,
    bg: Backgrounds,
    models: Models,
    icons: Icons,
    sounds: Sounds,
    music: Music,
}

impl Assets {
    pub fn load() -> Self {
        Self {
            fonts: Fonts {
                doomed: Font::load_bytes(fonts::DOOMED, crate::FontType::TTF, 100, None, 0)
            },
            bg: Backgrounds {
                stars: Texture::from(Image::from_bytes(bg::STARS, crate::ImageType::PNG))
            },
            models: Models {
                neptune: Model::load("assets/models/neptune.obj").unwrap()
            },
            icons: Icons {
                big: Image::from_bytes(icons::ICON_BIG, crate::ImageType::PNG)
            },
            sounds: Sounds{},
            music: Music{}
        }
    }
}