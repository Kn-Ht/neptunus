mod assets;
mod game;

use game::game::Game;
use rl_wrapper::prelude::*;
use assets::*;
use crate::rl_wrapper::window::Window;

mod rl_wrapper;

fn main() {
    let mut game = Game::new();

    while game.running() {
        game.update();
    }
}
