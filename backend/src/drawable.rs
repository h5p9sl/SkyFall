use crate::rendering_arguments::RenderingArguments;

pub trait Drawable {
    fn draw(&self, args: &mut RenderingArguments);
}
