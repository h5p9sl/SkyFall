use ::backend::{Camera, Asset, RectangleShape, RenderWindow, SpriteSheet};
use ::input::InputManager;

use piston::*;

pub struct Arm {
    arm_sprite: SpriteSheet,
    arm_rect: RectangleShape,
    current_frame: [i16; 2],
    counter: f32,
    shooting: bool,
    debug: bool,
}

impl Arm {
    pub fn new() -> Arm {
        let arm_sprite = SpriteSheet::new(Asset::graphic("weapon/pistol.sprite"));
        Arm {
            arm_sprite: arm_sprite.clone(),
            arm_rect: RectangleShape::new()
                .size(arm_sprite.get_size() * 4.0)
                .sprite(&arm_sprite)
                .origin_px([1.5 * 4.0, 7.5 * 4.0])
                .flip_offset_h(false),
            current_frame: [0, 0],
            counter: std::f32::MAX,
            shooting: false,
            debug: false,
        }
    }

    pub fn toggle_debug(&mut self) {
        self.debug = !self.debug;
        self.arm_rect.set_debug_outline(self.debug);
    }

    fn set_sprite(&mut self) {
        let frame = [self.current_frame[0] as u16, self.current_frame[1] as u16];
        self.arm_rect
            .set_texture_rect(self.arm_sprite.get_sprite_at(frame));
    }

    fn next_frame(&mut self) {
        self.current_frame[0] += 1;

        // Clamp sprite animation
        if self.current_frame[0] >= self.arm_sprite.get_columns() as i16 {
            self.current_frame[0] = 0;
            self.shooting = false;
        }
        self.set_sprite();
    }

    fn update_animation(&mut self, delta: f64) {
        if self.shooting {
            self.counter += delta as f32;
            if self.counter > 0.1 {
                self.next_frame();
                self.counter = 0.0;
            }
        }
    }

    pub fn update(
        &mut self,
        input: &InputManager,
        camera: &Camera,
        parent: &RectangleShape,
        flipped: bool,
        delta: f64,
    ) {
        let mouse_pos = camera.get_cursor_pos(input.get_cursor_pos());
        self.arm_rect.parent(parent);
        self.arm_rect.set_position([0.0, -74.0]);
        self.arm_rect.set_flip_h(flipped);

        // Update arm rotation
        {
            let arm_pos = self.arm_rect.get_position();
            let diffs = [mouse_pos[0] - arm_pos.x, mouse_pos[1] - arm_pos.y];
            let angle = f64::atan(diffs[1] / diffs[0]);
            let angle = angle * 180.0 / std::f64::consts::PI;
            self.arm_rect.rotate(angle);
        }

        if !self.shooting && input.is_button_down(MouseButton::Left) {
            self.shooting = true;
        }
        self.update_animation(delta);
    }

    pub fn draw(&mut self, window: &mut RenderWindow) {
        window.draw(&mut self.arm_rect);
    }
}
