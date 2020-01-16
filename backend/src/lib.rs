//! The core engine for SkyFall
//!
//! Contains everything SkyFall needs in order to run, including Window abstractions, User
//! Interfaces, Assets, etc.
//!
//! To see SkyFall's documentation, see [SkyFall](../skyfall_rs/index.html)

// External exports
pub use shapes;

// General structs
pub use crate::asset::Asset;
pub use crate::circleshape::CircleShape;
pub use crate::rendering_arguments::RenderingArguments;
pub use crate::renderwindow::RenderWindow;

// GUI
pub use crate::gui_button::GuiButton;
pub use crate::gui_label::GuiLabel;

pub mod asset;

mod rendering_arguments;

pub mod circleshape;
pub mod drawable;
pub mod renderwindow;

pub mod gui_button;
pub mod gui_label;
