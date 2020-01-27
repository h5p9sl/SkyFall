use crate::gamestate::GameState;
use ::backend::{Camera, shapes, RenderWindow};
use ::input::InputManager;
use piston::{keyboard::Key, Button, Input};

use crate::local_player::LocalPlayer;

pub struct SceneManager {
    bg_color: [f32; 4],
    local_player: LocalPlayer,
    point: shapes::Point,
}

impl SceneManager {
    pub fn new() -> SceneManager {
        SceneManager {
            bg_color: [0.40, 0.14, 0.16, 1.0],
            local_player: LocalPlayer::new(),
            point: shapes::Point::from([0., 0.]),
        }
    }

    pub fn resize(&mut self, _size: shapes::Size) {}

    pub fn on_input(&mut self, input: &Input) -> GameState {
        match input {
            Input::Button(args) => {
                if args.button == Button::Keyboard(Key::Escape) {
                    return GameState::Paused;
                }
                if args.button == Button::Keyboard(Key::F2) {
                    if args.state == piston::ButtonState::Press {
                        self.local_player.toggle_debug();
                    }
                }
            }
            _ => {}
        }
        GameState::InGame
    }

    pub fn update(&mut self, delta: f64, input: &InputManager, camera: &Camera) {
        self.local_player.update(delta, input, camera);
    }

    pub fn draw(&mut self, window: &mut RenderWindow, camera: &mut Camera) {
        window.clear(self.bg_color);
        self.local_player.draw(window);
        self.point.x = -self.local_player.get_position().x + window.size().w / 2.0;
        camera.set_position(self.point);
    }
}
