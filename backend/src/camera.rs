use crate::shapes::Point;
use crate::RenderWindow;

pub struct Camera {
    pos: Point,
}

impl Camera {
    pub fn new() -> Camera {
        Camera {
            pos: Point::from([0., 0.]),
        }
    }

    pub fn set_position<P: Into<Point>>(&mut self, pos: P) {
        self.pos = pos.into();
    }

    pub fn set_window_view(&self, window: &mut RenderWindow) {
        window.set_view(self.pos);
    }

    pub fn get_cursor_pos(&self, cursor: [f64; 2]) -> [f64; 2] {
        let mut pos = [self.pos.x, self.pos.y];
        pos[0] = -(pos[0] - cursor[0]);
        pos[1] = -(pos[1] - cursor[1]);
        pos
    }
}
