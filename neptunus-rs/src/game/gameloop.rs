#[derive(Clone, Copy, Debug)]
pub enum GameLoop {
    TitleScreen,
    Options,
    Running,
    Paused
}