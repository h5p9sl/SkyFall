use ::backend::{Asset, RectangleShape, SpriteSheet, RenderWindow};
use ::input::InputManager;

pub struct Arm {
    arm_sprite: SpriteSheet,
    arm_rect: RectangleShape,
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
                .flip_offset_h(false)
                .debug_outline(true),
        }
    }

    pub fn update(&mut self, input: &InputManager, parent: &RectangleShape, flipped: bool) {
        self.arm_rect.parent(parent);
        self.arm_rect.set_position([0.0, -74.0]);
        self.arm_rect.set_flip_h(flipped);

        // Update arm rotation
        {
            let mouse_pos = input.get_cursor_pos();
            let arm_pos = self.arm_rect.get_position();
            let diffs = [mouse_pos[0] - arm_pos.x, mouse_pos[1] - arm_pos.y];
            let angle = f64::atan(diffs[1] / diffs[0]);
            let angle = angle * 180.0 / std::f64::consts::PI;
            self.arm_rect.rotate(angle);
        }
    }

    pub fn draw(&mut self, window: &mut RenderWindow) {
        window.draw(&mut self.arm_rect);
    }
}