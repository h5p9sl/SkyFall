pub use crate::rendering_arguments::RenderingArguments;

pub trait Drawable {
    fn draw(&mut self, args: &mut RenderingArguments);
}
