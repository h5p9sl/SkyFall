use crate::drawable::Drawable;
use crate::rendering_arguments::RenderingArguments;
use piston_window::*;

pub struct GuiButton {
    is_touching_mouse: bool,
    is_pressed: bool,
    bounds: shapes::Rect,
}

impl Drawable for GuiButton {
    fn draw(&self, args: &mut RenderingArguments) {
        let color: [f32; 4] = [1., 1., 1., 1.];
        let rect = self.bounds;
        let transform = args.context.transform;
        graphics::rectangle(color, rect, transform, args.graphics_api);
    }
}

impl GuiButton {
    pub fn new(_lbl: &str) -> GuiButton {
        GuiButton {
            bounds: shapes::Rect::from([0., 0., 0., 0.,]),
            is_touching_mouse: false,
            is_pressed: false,
        }
    }

    pub fn set_position<T: Into<shapes::Point>>(&mut self, pos: T) {
        self.bounds.pos = pos.into();
    }

    pub fn set_size<T: Into<shapes::Size>>(&mut self, size: T) {
        self.bounds.size = size.into();
    }

    pub fn size<T: Into<shapes::Size>>(mut self, size: T) -> Self {
        self.set_size(size);
        self
    }

    pub fn position<T: Into<shapes::Point>>(mut self, pos: T) -> Self {
        self.set_position(pos);
        self
    }

    fn on_button(&mut self, args: &ButtonArgs) -> bool {
        self.is_pressed = false;
        if let Button::Mouse(button) = args.button {
            match button {
                MouseButton::Left => {
                    if self.is_touching_mouse && args.state == ButtonState::Press {
                        self.is_pressed = true;
                    }
                },
                _ => {},
            }
        }
        return self.is_pressed;
    }

    fn on_move(&mut self, args: &Motion) {
        if let Motion::MouseCursor(args) = args {
            if self.bounds.contains((args[0], args[1])) {
                self.is_touching_mouse = true;
            } else {
                self.is_touching_mouse = false;
            }
        }
    }

    pub fn on_input(&mut self, input_event: Input) -> bool {
        match input_event {
            Input::Button(args) => return self.on_button(&args),
            Input::Move(args) => self.on_move(&args),
            _ => {}
        }
        return false;
    }
}
