use crate::drawable::Drawable;
use crate::rendering_arguments::RenderingArguments;
use crate::gui_label::GuiLabel;

use piston_window::*;
use opengl_graphics::GlyphCache;

pub struct GuiButton<'a> {
    // Colors that the button can be
    base_color:     [f32; 4],
    hovered_color:  [f32; 4],
    pressed_color:  [f32; 4],

    // Other fields
    is_touching_mouse: bool,
    is_pressed: bool,
    bounds: shapes::Rect,
    label: GuiLabel<'a>,
}

impl Drawable for GuiButton<'_> {
    fn draw(&mut self, args: &mut RenderingArguments) {
        let color: [f32; 4] = self.get_color();
        graphics::rectangle(color, self.bounds, args.context.transform, args.graphics_api);
    }
}

impl GuiButton<'_> {
    pub fn new(lbl: &str) -> GuiButton<'static> {
        GuiButton {
            label: GuiLabel::new(lbl.to_string()),
            bounds: shapes::Rect::from([0., 0., 0., 0.,]),
            is_touching_mouse: false,
            is_pressed: false,
            base_color:     [0.5, 0.5, 0.5, 1.],
            hovered_color:  [0.8, 0.8, 0.8, 1.],
            pressed_color:  [1.0, 0.6, 0.6, 1.],
        }
    }

    /// Gets color based on whether or not the user is hovering or pressing the button
    fn get_color(&self) -> [f32; 4] {
        if !self.is_touching_mouse{
            self.base_color
        } else if self.is_pressed {
            self.pressed_color
        } else {
            self.hovered_color
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

    /// The color that the button will default to when NOT hovered or pressed by the user
    pub fn base_color(mut self, color: [f32; 4]) -> Self {
        self.base_color = color;
        self
    }

    /// The color that the button will change to when hovered on by the user
    pub fn hovered_color(mut self, color: [f32; 4]) -> Self {
        self.hovered_color = color;
        self
    }

    /// The color that the button will change to when pressed by the user
    pub fn pressed_color(mut self, color: [f32; 4]) -> Self {
        self.pressed_color = color;
        self
    }

    fn on_button(&mut self, args: &ButtonArgs) -> bool {
        let mut last_state = self.is_pressed;
        self.is_pressed = false;
        if let Button::Mouse(button) = args.button {
            if button == MouseButton::Left && self.is_touching_mouse {
                self.is_pressed = args.state == ButtonState::Press;
            } else {
                // Ensure we don't send out any events
                last_state = false;
            }
        }
        last_state && !self.is_pressed
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

    /// Called whenever there is an input event on the window
    pub fn on_input(&mut self, input_event: &Input) -> bool {
        match input_event {
            Input::Button(args) => return self.on_button(&args),
            Input::Move(args) => self.on_move(&args),
            _ => {}
        }
        false
    }
}
