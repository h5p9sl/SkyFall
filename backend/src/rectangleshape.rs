use opengl_graphics::{Texture, TextureSettings, Filter};
use graphics::*;
use shapes::*;

use graphics::types::Color;

use crate::drawable::Drawable;
use crate::rendering_arguments::RenderingArguments;
use crate::sprite_sheet::SpriteSheet;

pub struct RectangleShape {
    color: Color,
    bounds: Rect,
    image: Image,
    texture: Texture,
    texture_loaded: bool,
    flip_v: bool,
}

impl RectangleShape {
    pub fn new() -> RectangleShape {
        let texture_settings = RectangleShape::get_texture_settings();
        RectangleShape {
            color: [1., 1., 1., 1.],
            bounds: Rect::from([0., 0., 0., 0.,]),
            image: Image::new(),
            texture: Texture::empty(&texture_settings).unwrap(),
            texture_loaded: false,
            flip_v: false,
        }
    }

    // ****************************************
    // ****************************************
    //
    //          Get/Set functions
    //
    //      These functions are mostly
    //      self explanatory, needing
    //      no documentation.
    //
    // ****************************************
    // ****************************************

    pub fn set_flip_v(&mut self, should: bool) {
        self.flip_v = should;
    }

    pub fn flip_v(mut self, should: bool) -> Self {
        self.set_flip_v(should);
        self
    }

    fn get_texture_settings() -> TextureSettings {
        TextureSettings::new().mag(Filter::Nearest)
    }

    pub fn set_texture<S: Into<String>>(&mut self, path: S) {
        // Disables rectangle drawing and draws image instead
        self.texture_loaded = true;

        let settings = RectangleShape::get_texture_settings();
        self.texture = Texture::from_path(path.into(), &settings).unwrap();
    }

    pub fn texture<S: Into<String>>(mut self, path: S) -> Self {
        self.set_texture(path);
        self
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

    pub fn set_texture_rect<R: Into<Rect>>(&mut self, rect: R) {
        self.image = self.image.src_rect(rect.into().into());
    }

    pub fn texture_rect<R: Into<Rect>>(mut self, rect: R) -> Self {
        self.set_texture_rect(rect);
        self
    }

    fn update_image(&mut self) {
        self.image = self.image.rect(self.bounds);
    }

    pub fn sprite(mut self, sprite_sheet: &SpriteSheet) -> Self {
        self.set_texture(sprite_sheet.get_sprite_path());
        self.set_texture_rect(sprite_sheet.get_sprite_at([0, 0]));
        self
    }
}

impl Drawable for RectangleShape {
    fn draw(&mut self, args: &mut RenderingArguments) {
        let mut transform = args.context.transform;

        if self.flip_v {
            transform = transform.flip_v();
        }

        if self.texture_loaded {
            self.update_image();
            self.image.draw(&self.texture, &DrawState::default(), transform, args.graphics_api);
        } else {
            graphics::rectangle(self.color, self.bounds, transform, args.graphics_api);
        }
    }
}
