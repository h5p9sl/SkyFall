use glutin_window::*;
use graphics::clear;
use opengl_graphics::GlGraphics;
use piston::*;

use crate::drawable::Drawable;
use crate::rendering_arguments::RenderingArguments;

use shapes::Point;

pub struct RenderWindow {
    gl: GlGraphics,
    window: GlutinWindow,
    events: Events,
    objects: Vec<*mut dyn Drawable>,
    view: Point,
}

impl RenderWindow {
    pub fn new<N, S>(name: N, size: S, resizable: bool) -> RenderWindow
    where
        N: Into<String>,
        S: Into<Size>,
    {
        let size = size.into();
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
            view: Point::from([0., 0.]),
        }
    }

    pub fn set_view(&mut self, view: Point) {
        self.view = view;
    }

    pub fn size(&self) -> shapes::Size {
        let size = self.window.size();
        shapes::Size::from([size.width, size.height])
    }

    pub fn should_close(&self) -> bool {
        self.window.should_close()
    }

    pub fn poll_event(&mut self) -> Option<Event> {
        self.events.next(&mut self.window)
    }

    pub fn clear(&mut self, color: [f32; 4]) {
        self.objects.clear();
        clear(color, &mut self.gl);
    }

    pub fn draw(&mut self, obj: *mut dyn Drawable) {
        self.objects.push(obj);
    }

    pub fn display(&mut self, args: &RenderArgs) {
        use graphics::Transformed;
        let mut context = self.gl.draw_begin(args.viewport());
        context.transform = context.transform.trans(self.view.x, self.view.y);
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
