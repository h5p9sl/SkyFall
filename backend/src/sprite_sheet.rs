use std::path::PathBuf;

use serde_derive::Deserialize;
use shapes::{Rect, Size};

#[derive(Deserialize, Clone)]
pub struct SpriteSheet {
    /// The path leading to the sprite image (.png, .jpg)
    path: String,
    /// The size of one individual sprite on the sprite sheet
    size: (u16, u16),
    /// The number of rows in the sprite sheet
    rows: u16,
    /// The number of rows in the sprite sheet
    columns: u16,
}

impl SpriteSheet {
    pub fn new(path: String) -> SpriteSheet {
        SpriteSheet::from_sprite_file(path)
    }

    fn load_sprite_file(file: &PathBuf) -> String {
        use std::fs::File;
        use std::io::Read;
        let mut buf = String::new();
        let mut file = File::open(&file).expect("Could not find sprite file");
        let _result = file
            .read_to_string(&mut buf)
            .expect("Could not read sprite file");
        buf
    }

    fn from_sprite_file<F: Into<PathBuf>>(file: F) -> SpriteSheet {
        let mut file_path = file.into();

        // Get the last element of file_path, ex. "/tmp/a.txt" => "a.txt"
        let string = file_path.iter()
            .last()
            .expect("Failed to get last element of file_path")
            .to_str()
            .expect("Failed to convert last element of file_path");
        eprintln!("Loading sprite \"{}\" ...", string);

        // Use TOML deserialization to load Sprite information
        let mut sprite_sheet: SpriteSheet = toml::from_str(SpriteSheet::load_sprite_file(&file_path).as_str())
            .expect("Failed to parse TOML information");

        // Append the path found in sprite_sheet onto our working directory
        // ex. "/tmp/my_sprite.sprite" => "/tmp/" => "/tmp/aaa.png"
        file_path.pop();
        let path = file_path.join(sprite_sheet.path);
        sprite_sheet.path = path.to_str()
            .expect("Failed to join sprite.path")
            .to_string();
        
        // Return result
        sprite_sheet
    }

    pub fn get_rows(&self) -> u16 {
        self.rows
    }
    pub fn get_columns(&self) -> u16 {
        self.columns
    }
    pub fn get_size(&self) -> Size {
        Size::from((self.size.0 as f64,
                   self.size.1 as f64))
    }
    pub fn get_sprite_path(&self) -> String {
        self.path.clone()
    }

    pub fn get_sprite_at(&self, point: [u16; 2]) -> Rect {
        assert!(point[0] <= self.columns);
        assert!(point[1] <= self.rows);
        let size = self.get_size();
        Rect::from([
            point[0] as f64 * size.w,
            point[1] as f64 * size.h,
            size.w,
            size.h,
        ])
    }
}
