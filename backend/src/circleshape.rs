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
            radius: radius,
            color: [1., 1., 1., 1.,],
            position: Point {x: 0., y: 0.},
        }
    }
}

impl Drawable for CircleShape {
    fn draw(&self, args: &mut RenderingArguments) {
        let transform = args.context
            .transform;
        graphics::ellipse(self.color, [self.position.x, self.position.y, self.radius, self.radius], transform, args.graphics_api);
    }
}
