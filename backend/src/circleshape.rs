use shapes::*;
use graphics::types::Color;

use crate::drawable::Drawable;
use crate::rendering_arguments::RenderingArguments;

pub struct CircleShape {
    radius: f64,
    color: Color,
    position: Point,
}

impl CircleShape {
    pub fn new(radius: f64) -> CircleShape {
        CircleShape {
            radius,
            color: [1., 1., 1., 1.,],
            position: Point {x: 0., y: 0.},
        }
    }

    pub fn set_color(&mut self, r: f32, g: f32, b: f32, a: f32)
    {
        self.color = [r,g,b,a];
    }
}

impl Drawable for CircleShape {
    fn draw(&mut self, args: &mut RenderingArguments) {
        let transform = args.context
            .transform;
        graphics::ellipse(self.color, [self.position.x, self.position.y, self.radius, self.radius], transform, args.graphics_api);
    }
}
