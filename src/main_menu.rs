use ::backend::{GuiButton, RenderWindow};
use piston::Input;

pub struct MainMenu {
    start_button: GuiButton<'static>,
}

impl MainMenu {
    pub fn new() -> MainMenu {
        println!("Initializing MainMenu");
        MainMenu {
            start_button: GuiButton::new("Start game")
                .size((300., 50.))
                .position((250., 350.)),
        }
    }

    pub fn on_input(&mut self, input: &Input) {
        self.start_button.on_input(input);
    }

    pub fn update(&mut self, delta: f64) {}

    pub fn draw(&mut self, window: &mut RenderWindow) {
        window.draw(&mut self.start_button);
    }
}
