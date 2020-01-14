use crate::drawable::Drawable;
use crate::rendering_arguments::RenderingArguments;
use opengl_graphics::GlyphCache;

pub struct GuiLabel<'a> {
    color: [f32; 4],
    font_size: u32,
    text: String,
    glyph: GlyphCache<'a>,
}

impl GuiLabel<'_> {
    pub fn new<S>(label: S, glyphs: GlyphCache<'static>) -> GuiLabel<'static>
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

impl Drawable for GuiLabel<'_> {
    fn draw(&mut self, args: &mut RenderingArguments) {
        graphics::text(
            self.color,
            self.font_size,
            self.text.as_str(),
            &mut self.glyph,
            args.context.transform,
            args.graphics_api
        ).expect("Failed to draw text!");
    }
}
