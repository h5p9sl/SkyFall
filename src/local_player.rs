use piston::keyboard::Key;

use crate::skyfall;

use ::input::InputManager;
use ::backend::shapes::Point;
use ::backend::{Asset, RectangleShape, RenderWindow, SpriteSheet};

pub struct LocalPlayer {
    sprite: SpriteSheet,
    rect: RectangleShape,
    vel: Point,
    movement: Point,
    on_ground: bool,

    // Whether or not the sprite is flipped
    flipped: bool,

    counter: f32,
    current_frame: [i16; 2],
}

impl LocalPlayer {
    pub fn new() -> LocalPlayer {
        let sprite = SpriteSheet::new(Asset::graphic("player/original_light.sprite"));
        LocalPlayer {
            sprite: sprite.clone(),
            rect: RectangleShape::new()
                .size([80., 120.])
                .sprite(&sprite)
                .origin([0.5, 0.0]),
            vel: Point::from([0., 0.]),
            movement: Point::from([0., 0.]),
            on_ground: false,

            flipped: false,

            counter: 999.0,
            current_frame: [0, 0],
        }
    }

    fn update_head(&mut self, input: &InputManager) {
        let cursor_pos = input.get_cursor_pos();
        let rect_pos = self.rect.get_position();

        // Get angle between cursor and player head
        let head_pos = [rect_pos.x, rect_pos.y + 16.0];
        let mut pos = [cursor_pos[0] - head_pos[0], cursor_pos[1] - head_pos[1]];
        let hyp = pos[0].hypot(pos[1]);
        pos[0] /= hyp;
        pos[1] /= hyp;

        if pos[1] <= -0.5 {
            self.current_frame[1] = 1; // Looking up
        }
        else if pos[1] >= 0.5 {
            self.current_frame[1] = 2; // Looking down
        }
        else {
            self.current_frame[1] = 0; // Looking straight
        }
    }

    fn update_movement(&mut self, input: &InputManager) {
        // Update flip state
        let cursor_pos = input.get_cursor_pos();
        let rect_pos = self.rect.get_position();
        self.flipped = cursor_pos[0] < rect_pos.x;

        // Get key states
        let move_x = (input.is_key_down(Key::A), input.is_key_down(Key::D));
        let move_y = input.is_key_down(Key::W);

        // Reset movement variable
        self.movement = Point::from([0., 0.]);

        if move_x.0 {
            self.movement.x -= 1.0;
        }
        if move_x.1 {
            self.movement.x += 1.0;
        }
        if move_y {
            self.movement.y -= 1.0;
        }
    }

    fn set_sprite(&mut self) {
        let frame = [self.current_frame[0] as u16, self.current_frame[1] as u16];
        self.rect
            .set_texture_rect(self.sprite.get_sprite_at(frame));
    }

    /// Sets the current sprite animation to the next frame
    fn next_frame(&mut self) {
        // Reverse animation if we're flipped
        let mut frame_change = 1;
        if self.flipped {
            frame_change = -frame_change;
        }

        // Animate sprite "forwards" if we're moving forwards
        if self.movement.x < 0.0 {
            self.current_frame[0] -= frame_change;
        }
        // Vise versa
        else {
            self.current_frame[0] += frame_change;
        }

        // Clamp sprite animation
        if self.current_frame[0] >= self.sprite.get_columns() as i16 {
            self.current_frame[0] = 1;
        } else if self.current_frame[0] <= 0 {
            self.current_frame[0] = self.sprite.get_columns() as i16 - 1;
        }
        self.set_sprite();
    }

    /// Called once per update, updates the player sprite
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
        self.rect.set_flip_h(self.flipped);
    }

    /// Called once per frame, updates velocity, position, animation, etc.
    pub fn update(&mut self, delta: f64, input: &InputManager) {
        let mut pos = self.rect.get_position();

        // Update movement
        self.update_movement(input);

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

        self.update_head(input);
        self.update_animation(delta);
        self.rect.set_position(pos);
    }

    pub fn draw(&mut self, window: &mut RenderWindow) {
        window.draw(&mut self.rect);
    }
}
