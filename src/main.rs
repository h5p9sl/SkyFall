//! The SkyFall game crate
//!
//! To view the engine documentation, see [backend](../backend/index.html)

use std::time::Instant;

use ::backend::*;
use piston::*;

const SKYFALL_VERSION: &str = "0.1.0";

fn get_delta_time(clock: &mut Instant) -> f64 {
    let delta = clock.elapsed().as_secs_f64();
    *clock = Instant::now();
    delta
}

pub fn start_game() {
    let mut window = RenderWindow::new("SkyFall", [800, 600], false);
    let mut clock: Instant = Instant::now();
    while let Some(e) = window.poll_event() {
        // Get delta time
        let delta = get_delta_time(&mut clock);

        // Check event type and run code accordingly
        let input: Option<Input> = e.clone().into();
        if input.is_some() {
        }
        if let Some(args) = e.render_args() {
            window.clear([0., 0., 0., 1.]);
            window.display(&args);
        }
        if let Some(_args) = e.update_args() {
        }
    }
}

fn main() {
    println!("Running SkyFall version {}", SKYFALL_VERSION);
    start_game();
}
