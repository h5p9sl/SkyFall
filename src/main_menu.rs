use ::backend::{Asset, GuiButton, GuiLabel, RenderWindow};
use piston::Input;

use crate::gamestate::GameState;
use crate::shapes::Size;
use ears::*;

pub struct MainMenu {
    title: GuiLabel<'static>,
    start_button: GuiButton<'static>,
    options_button: GuiButton<'static>,
    exit_button: GuiButton<'static>,
    music: Music,
    pause_music: Music,
    bg_color: [f32; 4],
    paused: bool,
}

impl MainMenu {
    pub fn new(window_size: Size) -> MainMenu {
        println!("Initializing MainMenu");
        let mut menu = MainMenu {
            title: GuiLabel::new("SkyFall Rust")
                .font_size(48)
                .color([1.0, 1.0, 1.0, 1.0])
                .origin((0.5, 0.5)),
            start_button: GuiButton::new("Start game")
                .size((300., 50.))
                .origin((0.5, 0.5)),
            options_button: GuiButton::new("Options")
                .size((300., 50.))
                .origin((0.5, 0.5)),
            exit_button: GuiButton::new("Exit game")
                .size((300., 50.))
                .origin((0.5, 0.5)),
            music: Music::new(Asset::music("skullcrusher.ogg").as_str()).unwrap(),
            pause_music: Music::new(Asset::music("drips_01.ogg").as_str()).unwrap(),
            bg_color: [0.14, 0.58, 0.68, 1.0],
            paused: false,
        };
        menu.music.play();
        menu.resize(window_size);
        menu
    }

    /// Called whenever the window resizes; resets the button & label positions to the center of
    /// the screen or wherever needed.
    pub fn resize(&mut self, window_size: Size) {
        let cntr = Size::from([window_size.w / 2.0, window_size.h / 2.0]);
        // Reposition title
        self.title.set_position((cntr.w, cntr.h));
        // Reposition buttons
        self.start_button.set_position((cntr.w, cntr.h + 20. + 60.));
        self.options_button
            .set_position((cntr.w, cntr.h + 20. + 60. * 2.));
        self.exit_button
            .set_position((cntr.w, cntr.h + 20. + 60. * 3.));
    }

    /// Stops all playing music
    fn stop_all_music(&mut self) {
        self.music.stop();
        self.pause_music.stop();
    }

    /// Called whenever the main window recieves input from the user. This input is then passed
    /// down to the buttons in the main menu
    ///
    /// Returns the next GameState
    pub fn on_input(&mut self, input: &Input) -> GameState {
        if self.start_button.on_input(input) {
            self.stop_all_music();
            self.paused = false;
            return GameState::InGame;
        }
        if self.options_button.on_input(input) {
            if self.music.get_state() != State::Playing {
                self.music.play();
            }
        }
        if self.exit_button.on_input(input) {
            // Lazy exit
            std::process::exit(0);
        }
        if self.paused {
            return GameState::Paused;
        }
        GameState::MainMenu
    }

    pub fn update(&mut self, _delta: f64, state: GameState) {
        self.paused = state == GameState::Paused;
        if self.paused {
            self.bg_color = [0.44, 0.58, 0.68, 1.0];
            self.start_button.set_label("Unpause");
            if !self.pause_music.is_playing() {
                self.pause_music.play();
            }
        }
    }

    pub fn draw(&mut self, window: &mut RenderWindow) {
        window.clear(self.bg_color);
        window.draw(&mut self.start_button);
        window.draw(&mut self.options_button);
        window.draw(&mut self.exit_button);
        window.draw(&mut self.title);
    }
}
