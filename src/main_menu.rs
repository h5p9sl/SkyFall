use ::backend::{GuiButton, GuiLabel, RenderWindow};
use piston::Input;

pub struct MainMenu {
    title: GuiLabel<'static>,
    start_button: GuiButton<'static>,
    options_button: GuiButton<'static>,
    exit_button: GuiButton<'static>,
}

impl MainMenu {
    pub fn new() -> MainMenu {
        println!("Initializing MainMenu");
        MainMenu {
            title: GuiLabel::new("SkyFall Rust")
                .font_size(48)
                .color([1.0, 1.0, 1.0, 1.0])
                .origin((0.5, 0.5))
                .position((400., 250.)),

            start_button: GuiButton::new("Start game")
                .size((300., 50.))
                .position((250., 350.)),
            options_button: GuiButton::new("Options")
                .size((300., 50.))
                .position((250., 410.)),
            exit_button: GuiButton::new("Exit game")
                .size((300., 50.))
                .position((250., 470.)),
        }
    }

    pub fn on_input(&mut self, input: &Input) {
        self.start_button.on_input(input);
        self.options_button.on_input(input);
        if self.exit_button.on_input(input) {
            // Lazy exit
            std::process::exit(0);
        }
    }

    pub fn update(&mut self, delta: f64) {}

    pub fn draw(&mut self, window: &mut RenderWindow) {
        window.draw(&mut self.start_button);
        window.draw(&mut self.options_button);
        window.draw(&mut self.exit_button);
        window.draw(&mut self.title);
    }
}
