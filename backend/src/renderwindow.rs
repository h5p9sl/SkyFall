use piston::*;
use piston_window::*;
use graphics::clear;
use opengl_graphics::GlGraphics;

use crate::drawable::Drawable;
use crate::rendering_arguments::RenderingArguments;

pub struct RenderWindow<'a> {
    gl: GlGraphics,
    window: PistonWindow,
    objects: Vec<&'a mut dyn Drawable>
}

impl RenderWindow<'_> {
    pub fn new<N, S>(name: N, size: S, resizable: bool) -> RenderWindow<'static> 
        where N: Into<String>,
              S: Into<Size>,
    {
        const VERSION: OpenGL = OpenGL::V3_2;
        RenderWindow {
            window: WindowSettings::new(name, size)
                .resizable(resizable)
                .graphics_api(VERSION)
                .build()
                .expect("Failed to create window!"),
            gl: GlGraphics::new(VERSION),
            objects: Vec::new(),
        }
    }

    pub fn poll_event(&mut self) -> Option<Event> {
        self.window.next()
    }

    pub fn clear(&mut self, color: [f32;4]) {
        self.objects.clear();
        clear(color, &mut self.gl);
    }

    pub fn display(&mut self) {
        let mut args = RenderingArguments {
        };
        for obj in &mut self.objects {
            obj.draw(&mut args);
        }
    }
}
