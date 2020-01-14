use crate::drawable::Drawable;
use crate::rendering_arguments::RenderingArguments;

use piston_window::Glyphs;

pub struct GuiLabel {
    color: [f32; 4],
    font_size: u32,
    text: String,
    glyph: Glyphs,
}

impl GuiLabel {
    pub fn new<S>(label: S, glyphs: Glyphs) -> GuiLabel
    where
        S: Into<String>,
    {
        GuiLabel {
            color: [0., 0., 0., 1.],
            font_size: 12,
            text: label.into(),
            glyph: glyphs,
        }
    }
}

impl Drawable for GuiLabel {
    fn draw(&self, args: &mut RenderingArguments) {
        graphics::text(
            self.color,
            self.font_size,
            self.text.as_str(),
            &mut self.glyph,
            args.context.transform,
            args.graphics_api
            );
    }
}
