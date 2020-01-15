use crate::drawable::Drawable;
use crate::rendering_arguments::RenderingArguments;
use opengl_graphics::{GlyphCache, TextureSettings};
use graphics::*;
use shapes::*;

pub struct GuiLabel<'a> {
    pos: Point,
    origin: Point,
    color: [f32; 4],
    font_size: u32,
    text: String,
    glyphs: GlyphCache<'a>,
}

impl GuiLabel<'_> {
    pub fn new<S>(label: S) -> GuiLabel<'static>
    where
        S: Into<String>,
    {
        GuiLabel {
            pos: Point::from([0.0, 0.0]),
            origin: Point::from([0.0, 0.0]),
            color: [0., 0., 0., 1.],
            font_size: 12,
            text: label.into(),
            glyphs: GlyphCache::new("res/LiberationMono-Regular.ttf", (), TextureSettings::new()).expect("GlyphCache creation failed!")
        }
    }
    pub fn set_color(&mut self, new_color: [f32; 4]) {
        self.color = new_color;
    }
    pub fn color(mut self, new_color: [f32; 4]) -> Self {
        self.set_color(new_color);
        self
    }
    pub fn set_font_size(&mut self, new_font_size: u32) {
        self.font_size = new_font_size;
    }
    pub fn font_size(mut self, new_font_size: u32) -> Self {
        self.set_font_size(new_font_size);
        self
    }
    pub fn set_origin<P: Into<Point>>(&mut self, new_origin: P) {
        self.origin = new_origin.into();
    }
    pub fn origin<P: Into<Point>>(mut self, new_origin: P) -> Self {
        self.set_origin(new_origin);
        self
    }
    pub fn set_position<P: Into<Point>>(&mut self, new_pos: P)
    {
        self.pos = new_pos.into();
    }
    pub fn position<P: Into<Point>>(mut self, new_pos: P) -> Self
    {
        self.set_position(new_pos);
        self
    }
}

impl Drawable for GuiLabel<'_> {
    fn draw(&mut self, args: &mut RenderingArguments) {
        let transform = args.context.transform
            .trans(self.origin.x, self.origin.y)
            .trans(0.0, self.font_size as f64)
            .trans(self.pos.x, self.pos.y);

        graphics::text(
            self.color,
            self.font_size,
            self.text.as_str(),
            &mut self.glyphs,
            transform,
            args.graphics_api
        ).expect("Failed to draw text!");
    }
}
