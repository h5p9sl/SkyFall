use piston::*;
use piston_window::*;
use graphics::clear;
use opengl_graphics::GlGraphics;
//
pub struct RenderWindow {
    gl: GlGraphics,
    window: PistonWindow,
    //objects: Vec<&mut dyn Drawable>
}

impl RenderWindow {
    pub fn new<N, S>(name: N, size: S, resizable: bool) -> RenderWindow 
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
        }
    }

    pub fn poll_event(&mut self) -> Option<Event> {
        self.window.next()
    }

    pub fn clear(&mut self, color: [f32;4]) {
        clear(color, &mut self.gl);
    }

    pub fn display(&mut self) {
        /*
        for obj in self.objects {
            obj.draw(&mut self.gl);
        }
        */
    }
}
