use crate::gamestate::GameState;
use ::backend::{shapes, RenderWindow};
use ::input::InputManager;
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

    pub fn resize(&mut self, _size: shapes::Size) {}

    pub fn on_input(&mut self, input: &Input) -> GameState {
        match input {
            Input::Button(args) => {
                if args.button == Button::Keyboard(Key::Escape) {
                    return GameState::Paused;
                }
            }
            _ => {}
        }
        GameState::InGame
    }

    pub fn update(&mut self, delta: f64, input: &InputManager) {
        self.local_player.update(delta, input);
    }

    pub fn draw(&mut self, window: &mut RenderWindow) {
        window.clear(self.bg_color);
        self.local_player.draw(window);
    }
}
