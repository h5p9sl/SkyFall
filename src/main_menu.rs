use ::backend::{GuiButton, RenderWindow};
use piston::Input;

pub struct MainMenu {
    start_button: GuiButton<'static>,
    exit_button: GuiButton<'static>
}

impl MainMenu {
    pub fn new() -> MainMenu {
        println!("Initializing MainMenu");
        MainMenu {
            start_button: GuiButton::new("Start game")
                .size((300., 50.))
                .position((250., 350.)),
            exit_button: GuiButton::new("Exit game")
                .size((300., 50.))
                .position((250., 405.)),
        }
    }

    pub fn on_input(&mut self, input: &Input) {
        self.start_button.on_input(input);
        if self.exit_button.on_input(input) {
            // Lazy exit
            std::process::exit(0);
        }
    }

    pub fn update(&mut self, delta: f64) {}

    pub fn draw(&mut self, window: &mut RenderWindow) {
        window.draw(&mut self.start_button);
        window.draw(&mut self.exit_button);
    }
}
