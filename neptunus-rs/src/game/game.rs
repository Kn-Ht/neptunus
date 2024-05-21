use raylib_ffi::enums::CameraProjection;

use super::gameloop;
use super::gameloop::GameLoop;
use super::state::State;
use crate::{cstr, debug_fps, draw};
use crate::{rl_wrapper::prelude::*, Assets};

struct TitleScreen {
    camera: Camera3D,
    rotation: f32,
}

pub struct Game {
    pub assets: Assets,
    pub gameloop: fn(&mut Self),
    pub gameloop_type: GameLoop,
    pub state: State,
    window: Window,
    _audio_device: AudioDevice,
    titlescreen: TitleScreen,
}

impl Game {
    pub fn new() -> Self {
        const WINDOW_TITLE: &str = if cfg!(debug_assertions) {
            concat!("Neptunus [DEBUG] v", env!("CARGO_PKG_VERSION"))
        } else {
            concat!("Neptunus v", env!("CARGO_PKG_VERSION"))
        };

        // start the window first, required for certain actions
        let window = Window::new(WINDOW_TITLE).resizable().size(800, 600).init();

        set_exit_key(KeyboardKey::Null);

        Self {
            window,
            assets: Assets::load(),
            gameloop: Self::titlescreen,
            gameloop_type: GameLoop::TitleScreen,
            _audio_device: AudioDevice::init(),
            state: State::new(),
            titlescreen: TitleScreen {
                camera: Camera3D::new(
                    vec3(15.0, 1.0, 10.0),
                    vec3(0.0, 0.0, 12.0),
                    vec3(0.0, 1.0, 0.0),
                    45.0,
                    CameraProjection::Perspective,
                ),
                rotation: 0.0,
            },
        }
    }

    pub fn titlescreen(&mut self) {
        const ROTATION_SPEED: f32 = 2.0;

        // update state
        self.titlescreen.rotation = if self.titlescreen.rotation > 360.0 {
            0.0
        } else {
            self.titlescreen.rotation + ROTATION_SPEED * self.state.dt
        };
        // update transform
        self.assets
            .objects
            .neptune
            .model
            .set_transform(matrix_rotate_y(self.titlescreen.rotation.to_radians()));

        draw! {
            clear_background(colors::BLACK);

            self.assets.bg.stars.draw_pro(
                self.assets.bg.stars.bounds(),
                rect(0., 0., self.state.screen_width as f32, self.state.screen_height as f32),
                vec2(0., 0.),
                0.0,
                colors::WHITE
            );

            self.titlescreen.camera.scene(|_camera| {
                self.assets.objects.neptune.draw(
                    vec3(0.0, 0.0, 5.0),
                    10.0, colors::WHITE
                );
            });

            debug_fps!();
        }
    }


    pub fn running(&self) -> bool {
        !self.window.should_close()
    }

    pub fn update(&mut self) {
        self.state.update();
        (self.gameloop)(self);
    }
}
