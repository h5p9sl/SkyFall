use shapes::{Size, Rect};

#[derive(Clone)]
pub struct SpriteSheet {
    rows: u32,
    columns: u32,
    /// The size of an individual sprite
    size: Size,
    /// The file path to the spritesheet image
    path: String,
}

impl SpriteSheet {
    pub fn new(path: String) -> SpriteSheet {
        SpriteSheet {
            rows: 0,
            columns: 0,
            size: Size::from([0., 0.,]),
            path,
        }
    }

    /// Temporary function until TOML parsing is implemented
    pub fn rows(mut self, rows: u32) -> Self {
        self.rows = rows;
        self
    }
    /// Temporary function until TOML parsing is implemented
    pub fn columns(mut self, columns: u32) -> Self {
        self.columns = columns;
        self
    }
    /// Temporary function until TOML parsing is implemented
    pub fn size<S: Into<Size>>(mut self, size: S) -> Self {
        self.size = size.into();
        self
    }

    pub fn get_sprite_path(&self) -> String {
        self.path.clone()
    }

    pub fn get_sprite_at(&self, point: [u32; 2]) -> Rect {
        assert!(point[0] <= self.columns);
        assert!(point[1] <= self.rows);
        Rect::from([
                   point[0] as f64 * self.size.w,
                   point[1] as f64 * self.size.h,
                   self.size.w,
                   self.size.h,
        ])
    }
}
