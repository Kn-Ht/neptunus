pub mod audio;
pub mod camera;
pub mod collision;
pub mod color;
pub mod draw;
pub mod input;
pub mod math;
pub mod texture;
pub mod window;
pub mod text;
pub mod model;
pub mod state;

#[macro_export]
macro_rules! cstr {
    ($str:literal) => {
        concat!($str, "\0").as_ptr() as *const i8
    };
    ($var:ident) => {
        format!("{}\0", $var).as_ptr() as *const i8
    };
}

#[macro_export]
macro_rules! drop_impl {
    ($($for:ident: $unload_fn:ident),* $(,)?) => {
        $(
            impl Drop for $for {
                fn drop(&mut self) {
                    unsafe {
                        raylib_ffi::$unload_fn(self.0);
                    }
                }
            }
        )*
    };
}

pub mod prelude {
    pub use super::{
        audio::*, camera::*, collision::*, color::*, draw::*, input::*, math::*, texture::*,
        window::*, text::*, model::*, state::*
    };
    pub use raylib_ffi::colors;
}
