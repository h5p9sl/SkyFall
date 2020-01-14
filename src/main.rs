use piston_window::*;
use std::time::Instant;

use ::backend::*;

fn main() {
    println!("Hello, world!");
    let mut window = RenderWindow::new("SkyFall", [800, 600], false);

    let mut circle = CircleShape::new(256.);
    let mut button = ::backend::GuiButton::new("Click me!");
    button.set_position((500., 300.));
    button.set_size((200., 100.));

    let mut t: f64 = 0.0;
    let mut clock: Instant = Instant::now();
    while let Some(e) = window.poll_event() {
        let input: Option<Input> = e.clone().into();
        if let Some(_args) = e.close_args() {
            return;
        }
        if input.is_some() {
            let input = input.unwrap();
            if button.on_input(input) {
                println!("Button pressed.");
            }
        }
        if let Some(args) = e.render_args() {
            window.clear([0., 0., 0., 1.]);
            window.draw(&circle);
            window.draw(&button);
            window.display(&args);
        }
        if let Some(_args) = e.update_args() {
            let delta = clock.elapsed().as_secs_f64();
            clock = Instant::now();

            //println!("Delta: {}", delta);
            t += delta;

            let r = f32::sin(t as f32 * 2.5 + 2.0) * 0.5 + 0.5;
            let g = f32::sin(t as f32 * 2.5 + 0.0) * 0.5 + 0.5;
            let b = f32::sin(t as f32 * 2.5 + 4.0) * 0.5 + 0.5;

            circle.set_color(r, g, b, 1.0);
        }
    }
}
