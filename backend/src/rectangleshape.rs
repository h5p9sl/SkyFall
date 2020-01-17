use graphics::types::Color;
use shapes::*;

use crate::drawable::Drawable;
use crate::rendering_arguments::RenderingArguments;

pub struct RectangleShape {
    color: Color,
    bounds: Rect,
}

impl RectangleShape {
    pub fn new() -> RectangleShape {
        RectangleShape {
            color: [1., 1., 1., 1.],
            bounds: Rect::from([0., 0., 0., 0.,]),
        }
    }

    pub fn set_size<S: Into<Size>>(&mut self, size: S) {
        self.bounds.size = size.into();
    }

    pub fn size<S: Into<Size>>(mut self, size: S) -> Self {
        self.set_size(size);
        self
    }

    pub fn get_size(&self) -> Size {
        self.bounds.size
    }

    pub fn set_position<P: Into<Point>>(&mut self, pos: P) {
        self.bounds.pos = pos.into();
    }

    pub fn position<P: Into<Point>>(mut self, pos: P) -> Self {
        self.set_position(pos);
        self
    }

    pub fn get_position(&self) -> Point {
        self.bounds.pos
    }

    pub fn set_color(&mut self, r: f32, g: f32, b: f32, a: f32) {
        self.color = [r, g, b, a];
    }
}

impl Drawable for RectangleShape {
    fn draw(&mut self, args: &mut RenderingArguments) {
        let transform = args.context.transform;
        graphics::rectangle(self.color, self.bounds, transform, args.graphics_api);
    }
}
