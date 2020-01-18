use piston::{keyboard::Key, Button, ButtonArgs, ButtonState, Input};

use crate::skyfall;

use ::backend::shapes::Point;
use ::backend::{Asset, RectangleShape, RenderWindow, SpriteSheet};

pub struct LocalPlayer {
    sprite: SpriteSheet,
    rect: RectangleShape,
    vel: Point,
    movement: Point,
    on_ground: bool,

    counter: f32,
    current_frame: [u32; 2],
}

impl LocalPlayer {
    pub fn new() -> LocalPlayer {
        let sprite = SpriteSheet::new(Asset::graphic("player/original_light.png"))
            .rows(3)
            .columns(7)
            .size([20., 32.]);
        LocalPlayer {
            sprite: sprite.clone(),
            rect: RectangleShape::new().size([80., 120.]).sprite(&sprite),
            vel: Point::from([0., 0.]),
            movement: Point::from([0., 0.]),
            on_ground: false,

            counter: 999.0,
            current_frame: [0, 0],
        }
    }

    fn on_key(&mut self, key: &Key, state: ButtonState) {
        let mut press: f64 = 1.0;
        if state != ButtonState::Press {
            press = -1.0;
        }
        match key {
            // Movement.y becomes -1.0 on key press and 0.0 on key release
            Key::W => self.movement.y -= press,
            // movement.x becomes -1.0 on key press and 0.0 on key release
            Key::A => self.movement.x -= press,
            // movement.x becomes 1.0 on key press and 0.0 on key release
            Key::D => self.movement.x += press,
            _ => {}
        }
        // Clamp movement values
        self.movement.x = self.movement.x.min(1.0).max(-1.0);
        self.movement.y = self.movement.y.min(1.0).max(-1.0);
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

    fn set_sprite(&mut self) {
        self.rect
            .set_texture_rect(self.sprite.get_sprite_at(self.current_frame));
    }

    fn next_frame(&mut self) {
        // If player is moving backwards
        if self.movement.x < 0.0 {
            // Prevent overflow panic
            if self.current_frame[0] == 0 {
                self.current_frame[0] = 2;
            } else {
                self.current_frame[0] -= 1;
            }
        }
        // If player is moving forwards
        else {
            self.current_frame[0] += 1;
        }

        // Clamp sprite animation
        if self.current_frame[0] >= self.sprite.get_columns() {
            self.current_frame[0] = 1;
        } else if self.current_frame[0] <= 0 {
            self.current_frame[0] = self.sprite.get_columns() - 1;
        }
        self.set_sprite();
    }

    fn update_animation(&mut self, delta: f64) {
        self.counter += delta as f32;
        if self.movement.x != 0.0 {
            if self.counter > 0.2 {
                self.next_frame();
                self.counter = 0.0;
            }
        } else {
            self.current_frame[0] = 0;
            self.set_sprite();
        }
    }

    pub fn update(&mut self, delta: f64) {
        let mut pos = self.rect.get_position();

        // Update velocity
        self.vel.y += skyfall::GRAVITY_RATE;
        if self.on_ground {
            self.vel.y += self.movement.y * 550.0;
        }
        self.vel.x += self.movement.x * 30.0;

        // Decay velocity
        self.vel.x *= 0.9;

        // Update position
        pos.y += self.vel.y * delta;
        pos.x += self.vel.x * delta;
        if pos.y >= 600.0 - 120.0 {
            pos.y = 600.0 - 120.0;
            self.vel.y = 0.0;
            self.on_ground = true;
        } else {
            self.on_ground = false;
        }

        self.update_animation(delta);
        self.rect.set_position(pos);
    }

    pub fn draw(&mut self, window: &mut RenderWindow) {
        window.draw(&mut self.rect);
    }
}
