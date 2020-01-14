use piston_window::*;
use std::time::Instant;

use ::backend::*;

fn main() {
    println!("Hello, world!");
    let mut window = RenderWindow::new("SkyFall", [800, 600], false);

    let mut should_rainbow = true;
    let mut circle = CircleShape::new(256.);
    let mut button = ::backend::GuiButton::new("Click me!")
        .size((200., 100.))
        .position((500., 300.));

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
                println!("Toggled rainbow");
                should_rainbow = !should_rainbow;
            }
        }
        if let Some(args) = e.render_args() {
            window.clear([0., 0., 0., 1.]);
            window.draw(&mut circle);
            window.draw(&mut button);
            window.display(&args);
        }
        if let Some(_args) = e.update_args() {
            let delta = clock.elapsed().as_secs_f64();
            clock = Instant::now();

            //println!("Delta: {}", delta);
            t += delta;

            let (r, g, b);
            if should_rainbow {
                r = f32::sin(t as f32 * 2.5 + 2.0) * 0.5 + 0.5;
                g = f32::sin(t as f32 * 2.5 + 0.0) * 0.5 + 0.5;
                b = f32::sin(t as f32 * 2.5 + 4.0) * 0.5 + 0.5;
            } else {
                r = 0.5;
                g = 0.5;
                b = 0.5;
            }

            circle.set_color(r, g, b, 1.0);
        }
    }
}
