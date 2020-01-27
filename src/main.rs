//! The SkyFall game crate
//!
//! To view the engine documentation, see [backend](../backend/index.html)

use std::time::Instant;

use ::backend::*;
use piston::*;

pub mod gamestate;
pub mod main_menu;
pub mod scenemanager;
pub mod skyfall;

mod local_player;

pub use skyfall::SkyFall;

const SKYFALL_VERSION: &str = "0.2.0";

fn get_delta_time(clock: &mut Instant) -> f64 {
    let delta = clock.elapsed().as_secs_f64();
    *clock = Instant::now();
    delta
}

pub fn start_game() {
    let mut window = RenderWindow::new("SkyFall", [800, 600], false);
    let mut game = SkyFall::new(&mut window);

    let mut clock: Instant = Instant::now();
    while let Some(e) = window.poll_event() {
        // Check event type and run code accordingly
        let input: Option<Input> = e.clone().into();
        if input.is_some() {
            let input = input.unwrap();
            game.on_input(&input);
        }
        if let Some(args) = e.resize_args() {
            game.resize(&args);
        }
        if let Some(args) = e.render_args() {
            window.clear([0., 0., 0., 1.]);
            game.draw(&mut window);
            window.display(&args);
        }
        if let Some(_args) = e.update_args() {
            // Get delta time
            let delta = get_delta_time(&mut clock);

            game.update(delta);
        }
    }
}

fn main() {
    println!("Running SkyFall version {}", SKYFALL_VERSION);
    start_game();
}
