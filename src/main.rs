use backend::*;
use piston_window::*;

fn main() {
    println!("Hello, world!");
    let mut window = RenderWindow::new("SkyFall", [800, 600], false);

    let circle = CircleShape::new(128.);

    loop {
        while let Some(e) = window.poll_event() {
            if let Some(args) = e.close_args() {
                return;
            }
            if let Some(args) = e.render_args() {
                window.clear([0., 0., 0., 1.]);
                window.draw(&circle);
                window.display(&args);
            }
            if let Some(args) = e.update_args() {
                println!("Delta: {}", args.dt);
            }
        }
    }
}
