use piston::keyboard::Key;
use piston::*;

pub struct InputManager {
    keys: [bool; 256],
    buttons: [bool; 16],
    cursor_pos: [f64; 2],
}

impl InputManager {
    pub fn new() -> InputManager {
        InputManager {
            keys: [false; 256],
            buttons: [false; 16],
            cursor_pos: [0., 0.],
        }
    }

    fn on_button_event(&mut self, button: &ButtonArgs) {
        use piston::Button::*;
        let state = button.state == ButtonState::Press;

        match button.button {
            Keyboard(key) => {
                if let Some(x) = self.keys.get_mut(key.code() as usize) {
                    *x = state;
                } else {
                    println!("key.code() was {}", key.code());
                }
            }
            Mouse(key) => {
                if let Some(x) = self.buttons.get_mut(key as usize) {
                    *x = state;
                } else {
                    println!("button.code() was {}", key as usize);
                }
            }
            _ => {}
        }
    }

    fn on_motion_event(&mut self, motion: &Motion) {
        use piston::Motion::*;
        match motion {
            MouseCursor(pos) => self.cursor_pos = *pos,
            _ => {}
        }
    }

    /// Called whenever there is an input event from the parent window
    pub fn on_input(&mut self, input: &Input) {
        use piston::Input::*;
        match input {
            Button(args) => self.on_button_event(args),
            Move(args) => self.on_motion_event(args),
            _ => {}
        }
    }

    pub fn is_key_down(&self, key: Key) -> bool {
        *self.keys.get(key.code() as usize).unwrap_or(&false)
    }

    pub fn was_key_down(&self, _key: Key) -> bool {
        unimplemented!();
    }

    pub fn is_button_down(&self, button: MouseButton) -> bool {
        *self.buttons.get(button as usize).unwrap_or(&false)
    }

    pub fn was_button_down(&self, _button: MouseButton) -> bool {
        unimplemented!();
    }

    pub fn get_cursor_pos(&self) -> [f64; 2] {
        self.cursor_pos
    }
}
