use piston::*;
use glutin_window::*;

pub struct Window {
    glutin_window: GlutinWindow,
}

impl Window {
    pub fn new<N, S>(name: N, size: S, resizable: bool) -> Window 
        where N: Into<String>,
              S: Into<Size>,
    {
        Window {
            glutin_window: GlutinWindow::new(&WindowSettings::new(name, size)
                .resizable(resizable)
                ).expect("Failed to create window!")
        }
    }
}
