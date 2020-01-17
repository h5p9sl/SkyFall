//! The core engine for SkyFall
//!
//! Contains everything SkyFall needs in order to run, including Window abstractions, User
//! Interfaces, Assets, etc.
//!
//! To see SkyFall's documentation, see [SkyFall](../skyfall_rs/index.html)

// External exports
pub use shapes;

// General structs
pub use crate::sprite_sheet::SpriteSheet;

pub use crate::asset::Asset;
pub use crate::drawable::Drawable;
pub use crate::circleshape::CircleShape;
pub use crate::rectangleshape::RectangleShape;
pub use crate::rendering_arguments::RenderingArguments;
pub use crate::renderwindow::RenderWindow;

// GUI
pub use crate::gui_button::GuiButton;
pub use crate::gui_label::GuiLabel;

pub mod asset;
pub mod sprite_sheet;

mod rendering_arguments;
pub mod drawable;
pub mod renderwindow;

pub mod rectangleshape;
pub mod circleshape;
pub mod gui_button;
pub mod gui_label;
