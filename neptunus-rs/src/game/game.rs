use super::gameloop;
use super::gameloop::GameLoop;
use super::state::State;
use crate::{debug_fps, draw};
use crate::{rl_wrapper::prelude::*, Assets};

pub struct Game {
    pub assets: Assets,
    pub gameloop: fn(&mut Self),
    pub gameloop_type: GameLoop,
    pub state: State,
    window: Window,
    _audio_device: AudioDevice,
}

impl Game {
    pub fn titlescreen(&mut self) {
        draw! {
            clear_background(colors::BLACK);

            for i in 0..10000 {
                rect(i as f32, i as f32, 100.0, 50.0).draw(colors::RED);
            }

            debug_fps!();
        }
    }
    pub fn new() -> Self {
        const WINDOW_TITLE: &str = if cfg!(debug_assertions) {
            concat!("Neptunus [DEBUG] v", env!("CARGO_PKG_VERSION"))
        } else {
            concat!("Neptunus v", env!("CARGO_PKG_VERSION"))
        };

        Self {
            window: Window::new(WINDOW_TITLE).resizable().size(800, 600).init(),
            assets: Assets::load(),
            gameloop: Self::titlescreen,
            gameloop_type: GameLoop::TitleScreen,
            _audio_device: AudioDevice::init(),
            state: State::new(),
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
