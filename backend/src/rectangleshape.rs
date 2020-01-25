use graphics::*;
use opengl_graphics::{Filter, Texture, TextureSettings};
use shapes::*;

use graphics::types::Color;

use crate::drawable::Drawable;
use crate::rendering_arguments::RenderingArguments;
use crate::sprite_sheet::SpriteSheet;

pub struct RectangleShape {
    color: Color,
    bounds: Rect,
    /// The parent rectangle's (if any) position
    parent: Point,
    /// The position of the rectangle
    pos: Point,
    /// Whether or not the origin is measured in pixels
    origin_pixels: bool,
    origin: Point,
    image: Image,
    texture: Texture,
    texture_loaded: bool,

    rotation: f64,

    /// Whether or not to offset the flipped sprite with it's width
    flip_offset_h: bool,
    flip_h: bool,
}

impl RectangleShape {
    pub fn new() -> RectangleShape {
        let texture_settings = RectangleShape::get_texture_settings();
        RectangleShape {
            color: [1., 1., 1., 1.],
            bounds: Rect::from([0., 0., 0., 0.]),
            parent: Point::from([0., 0.]),
            pos: Point::from([0., 0.]),
            origin: Point::from([0., 0.]),
            origin_pixels: false,
            image: Image::new(),
            texture: Texture::empty(&texture_settings).unwrap(),
            texture_loaded: false,
            rotation: 0.0,
            flip_offset_h: true,
            flip_h: false,
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

    pub fn rotate(&mut self, degrees: f64) {
        self.rotation = degrees;
    }

    pub fn flip_offset_h(mut self, should: bool) -> Self {
        self.flip_offset_h = should;
        self
    }

    pub fn set_flip_h(&mut self, should: bool) {
        self.flip_h = should;
    }

    pub fn flip_h(mut self, should: bool) -> Self {
        self.set_flip_h(should);
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

    pub fn set_origin<P: Into<Point>>(&mut self, pos: P) {
        self.origin = pos.into();
    }

    pub fn origin_px<P: Into<Point>>(mut self, pos: P) -> Self {
        self.origin_pixels = true;
        self.set_origin(pos);
        self
    }

    pub fn origin<P: Into<Point>>(mut self, pos: P) -> Self {
        self.set_origin(pos);
        self
    }

    pub fn move_<P: Into<Point>>(&mut self, pos: P) {
        self.pos = self.pos +  pos.into();
    }

    /// Sets position based on parent rectangle
    pub fn parent(&mut self, other: &RectangleShape) {
        self.parent = other.get_position();
    }

    pub fn set_position<P: Into<Point>>(&mut self, pos: P) {
        self.pos = pos.into();
    }

    pub fn position<P: Into<Point>>(mut self, pos: P) -> Self {
        self.set_position(pos);
        self
    }

    pub fn get_position(&self) -> Point {
        self.pos + self.parent
    }

    pub fn set_color(&mut self, r: f32, g: f32, b: f32, a: f32) {
        self.color = [r, g, b, a];
    }

    pub fn set_texture_rect<R: Into<Rect>>(&mut self, rect: R) {
        let rect = rect.into();
        self.image = self.image.src_rect(rect.into());
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

    /// Return calculated offset
    fn get_origin_offset(&self) -> Point {
        let size = self.bounds.size;
        let mut origin = self.origin;
        if !self.origin_pixels {
            origin.x *= size.w;
            origin.y *= size.h;
        }

        // Negate origin
        origin.x = -origin.x;
        origin.y = -origin.y;

        origin
    }
}

impl Drawable for RectangleShape {
    fn draw(&mut self, args: &mut RenderingArguments) {
        let pos = self.pos + self.parent;
        let size = self.bounds.size;
        let origin = self.get_origin_offset();
        let mut transform = args
            .context
            .transform
            .trans(pos.x, pos.y)
            .rot_deg(self.rotation)
            .trans(origin.x, origin.y);

        if self.flip_h {
            transform = transform.flip_h();
            if self.flip_offset_h {
                transform = transform.trans(-size.w, 0.0);
            }
        }

        if self.texture_loaded {
            self.update_image();
            self.image.draw(
                &self.texture,
                &DrawState::default(),
                transform,
                args.graphics_api,
            );
        } else {
            let bounds: Rect = Rect::from([pos.x, pos.y, size.w, size.h]);
            graphics::rectangle(self.color, bounds, transform, args.graphics_api);
        }
    }
}
