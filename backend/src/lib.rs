//! The core engine for SkyFall
//!
//! Contains everything SkyFall needs in order to run, including Window abstractions, User
//! Interfaces, Assets, etc.

// General structs
pub use crate::renderwindow::RenderWindow;
pub use crate::circleshape::CircleShape;
pub use crate::rendering_arguments::RenderingArguments;

// GUI
pub use crate::gui_button::GuiButton;

mod rendering_arguments;

pub mod renderwindow;
pub mod drawable;
pub mod circleshape;

pub mod gui_label;
pub mod gui_button;
