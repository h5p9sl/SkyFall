use piston::{keyboard::Key, Button, ButtonArgs, ButtonState, Input};

use crate::skyfall;

use ::backend::{shapes::Point, RectangleShape, RenderWindow};

pub struct LocalPlayer {
    rect: RectangleShape,
    vel: Point,
    movement: Point,
    on_ground: bool,
}

impl LocalPlayer {
    pub fn new() -> LocalPlayer {
        LocalPlayer {
            rect: RectangleShape::new().size([80., 120.]),
            vel: Point::from([0., 0.]),
            movement: Point::from([0., 0.]),
            on_ground: false,
        }
    }

    fn on_key(&mut self, key: &Key, state: ButtonState) {
        let press: f64 = (state == ButtonState::Press) as i64 as f64;
        match key {
            Key::W => self.movement.y = -1.0 * press,
            Key::A => self.movement.x = -1.0 * press,
            Key::D => self.movement.x = 1.0 * press,
            _ => {}
        }
    }

    fn on_button(&mut self, args: &ButtonArgs) {
        match args.button {
            Button::Keyboard(key) => {
                self.on_key(&key, args.state);
            }
            _ => {}
        }
    }

    pub fn on_input(&mut self, input: &Input) {
        match input {
            Input::Button(args) => {
                self.on_button(&args);
            }
            _ => {}
        };
    }

    pub fn update(&mut self, delta: f64) {
        let mut pos = self.rect.get_position();

        // Update velocity
        self.vel.y += skyfall::GRAVITY_RATE * delta;
        if self.on_ground {
            self.vel.y += self.movement.y * 5.0;
        }
        self.vel.x += self.movement.x * 30.0 * delta;

        // Decay velocity
        self.vel.x *= 0.9;

        // Update position
        pos.y += self.vel.y;
        pos.x += self.vel.x;
        if pos.y >= 600.0 - 120.0 {
            pos.y = 600.0 - 120.0;
            self.vel.y = 0.0;
            self.on_ground = true;
        } else {
            self.on_ground = false;
        }
        self.rect.set_position(pos);
    }

    pub fn draw(&mut self, window: &mut RenderWindow) {
        window.draw(&mut self.rect);
    }
}
