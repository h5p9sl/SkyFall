#[derive(PartialEq, Copy, Clone, Debug)]
pub enum GameState {
    Invalid,
    MainMenu,
    InGame,
    Paused,
}
