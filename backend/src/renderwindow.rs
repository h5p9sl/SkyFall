use piston::*;
use glutin_window::*;
use graphics::clear;
use opengl_graphics::GlGraphics;

use crate::drawable::Drawable;
use crate::rendering_arguments::RenderingArguments;

pub struct RenderWindow {
    gl: GlGraphics,
    window: GlutinWindow,
    events: Events,
    objects: Vec<*mut dyn Drawable>
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
            events: Events::new(EventSettings::new()),
            objects: Vec::new(),
        }
    }
    
    pub fn should_close(&self) -> bool {
        self.window.should_close()
    }

    pub fn poll_event(&mut self) -> Option<Event> {
        self.events.next(&mut self.window)
    }

    pub fn clear(&mut self, color: [f32;4]) {
        self.objects.clear();
        clear(color, &mut self.gl);
    }

    pub fn draw(&mut self, obj: *mut dyn Drawable) {
        self.objects.push(obj);
    }

    pub fn display(&mut self, args: &RenderArgs) {
        let mut context = self.gl.draw_begin(args.viewport());
        let mut args = RenderingArguments {
            graphics_api: &mut self.gl,
            context: &mut context,
        };
        for pobj in &mut self.objects {
            unsafe {
                (**pobj).draw(&mut args);
            }
        }
        self.gl.draw_end();
    }
}
