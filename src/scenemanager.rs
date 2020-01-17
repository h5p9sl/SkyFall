use crate::gamestate::GameState;
use ::backend::{shapes, RenderWindow};
use piston::{keyboard::Key, Button, Input};

use crate::local_player::LocalPlayer;

pub struct SceneManager {
    bg_color: [f32; 4],
    local_player: LocalPlayer,
}

impl SceneManager {
    pub fn new() -> SceneManager {
        SceneManager {
            bg_color: [0.40, 0.14, 0.16, 1.0],
            local_player: LocalPlayer::new(),
        }
    }

    pub fn resize(&mut self, size: shapes::Size) {}

    pub fn on_input(&mut self, input: &Input) -> GameState {
        self.local_player.on_input(input);
        match input {
            Input::Button(args) => {
                if args.button == Button::Keyboard(Key::Escape) {
                    return GameState::MainMenu;
                }
            }
            _ => {}
        }
        GameState::InGame
    }

    pub fn update(&mut self, delta: f64) {
        self.local_player.update(delta);
    }

    pub fn draw(&mut self, window: &mut RenderWindow) {
        window.clear(self.bg_color);
        self.local_player.draw(window);
    }
}
