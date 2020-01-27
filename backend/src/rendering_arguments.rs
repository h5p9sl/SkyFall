use graphics::*;
use opengl_graphics::GlGraphics;

/// Structure containing all the information an object needs to draw
/// on an OpenGL context.
pub struct RenderingArguments<'a> {
    pub graphics_api: &'a mut GlGraphics,
    pub context: &'a mut Context,
}
