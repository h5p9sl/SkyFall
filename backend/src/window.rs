use piston::*;
use glutin_window::*;
use graphics::{clear, types::Color};
use opengl_graphics::GlGraphics;

pub struct Window {
    gl: GlGraphics,
    glutin_window: GlutinWindow,
}

impl Window {
    pub fn new<N, S>(name: N, size: S, resizable: bool) -> Window 
        where N: Into<String>,
              S: Into<Size>,
    {
        const VERSION: OpenGL = OpenGL::V3_2;
        Window {
            glutin_window: WindowSettings::new(name, size)
                .resizable(resizable)
                .graphics_api(VERSION)
                .build()
                .expect("Failed to create window!"),
            gl: GlGraphics::new(VERSION),
        }
    }

    pub fn clear(&mut self, color: [f32;4]) {
        clear(color, &mut self.gl);
    }

    pub fn display(&mut self) {
    }
}
