//! The core engine for SkyFall
//!
//! Contains everything SkyFall needs in order to run, including Window abstractions, User
//! Interfaces, Assets, etc.

pub use crate::renderwindow::RenderWindow;

mod rendering_arguments;

pub mod renderwindow;
pub mod drawable;

