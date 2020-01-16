use crate::gamestate::GameState;
use crate::main_menu::MainMenu;
use ::backend::RenderWindow;
use piston::Input;

use ::backend::shapes;

pub struct SkyFall {
    window: *mut RenderWindow,
    next_state: GameState,
    last_state: GameState,
    state: GameState,
    // Use std::vec here so we can dynamically allocate and free the main menu
    main_menu: Vec<MainMenu>,
}

impl SkyFall {
    pub fn new(window: *mut RenderWindow) -> SkyFall {
        SkyFall {
            window,
            last_state: GameState::Invalid,
            next_state: GameState::MainMenu,
            state: GameState::MainMenu,
            main_menu: Vec::new(),
        }
    }

    fn initialize_main_menu(&mut self) {
        unsafe {
            let size = (*self.window).size();
            self.main_menu.push(MainMenu::new(size));
        }
    }

    fn initialize_game(&mut self) {
    }

    /// Ensures that the current game state is not initialized:
    ///
    /// An "uninitialized game state" in the context of MainMenu would mean that the
    /// main menu is currently uninitialized and it is not safe to draw or pass input
    /// to the main menu while it is uninitialized.
    fn ensure_valid_state(&self) -> bool {
        self.last_state != GameState::Invalid
    }

    /// Called once per frame, updates game-state
    ///
    /// In summary, this function sets `self.last_state` = `self.state`
    fn update_state(&mut self) {
        if self.next_state != self.state {
            self.last_state = GameState::Invalid;
        } else {
            self.last_state = self.state;
        }
        self.state = self.next_state;
    }

    fn initialize_state_if_needed(&mut self) {
        if !self.ensure_valid_state() {
            match self.state {
                GameState::MainMenu => self.initialize_main_menu(),
                GameState::InGame => self.initialize_game(),
                _ => {},
            }
        }
    }

    /// Called whenever there is an input event in the main window
    ///
    /// This function passes the input event down to the entities
    /// so that they can respond to the input event
    pub fn on_input(&mut self, input: &Input) {
        if self.ensure_valid_state() {
            match self.state {
                GameState::MainMenu => {
                    let main_menu = self.main_menu.first_mut().expect("MainMenu not found?");
                    self.next_state = main_menu.on_input(input);
                }
                GameState::InGame => {}
                _ => panic!("Invalid GameState in SkyFall::on_input"),
            }
        }
    }

    /// Called whenever the main window is resized
    ///
    /// This function will reset all elements to the correct position
    pub fn resize(&mut self, args: &piston::ResizeArgs) {
        // Ensure that our state is initialized
        if self.ensure_valid_state() {
            match self.state {
                GameState::MainMenu => {
                    let main_menu = self.main_menu.first_mut().expect("MainMenu not found?");
                    let size = shapes::Size::from(
                        [
                        args.draw_size[0] as f64,
                        args.draw_size[1] as f64,
                        ]);

                    main_menu.resize(size);
                }
                GameState::InGame => {}
                _ => panic!("Invalid GameState in SkyFall::draw"),
            }
        }
    }

    /// Called once per frame, updates game based on current GameState.
    ///
    /// For example, if the current game-state is MainMenu, the main menu will be **updated**.
    pub fn update(&mut self, delta: f64) {
        match self.state {
            GameState::MainMenu => {
                self.initialize_state_if_needed();
                let main_menu = self.main_menu.first_mut().expect("MainMenu not found?");
                main_menu.update(delta);
            }
            GameState::InGame => {
                self.initialize_state_if_needed();
            }
            _ => panic!("Invalid GameState in SkyFall::update"),
        }
        self.update_state();
    }

    /// Called once per frame, draws game objects based on current GameState
    ///
    /// For example, if the game-state is MainMenu, the main menu will be **drawn**.
    pub fn draw(&mut self, window: &mut RenderWindow) {
        // Ensure that our state is initialized
        if self.ensure_valid_state() {
            match self.state {
                GameState::MainMenu => {
                    let main_menu = self.main_menu.first_mut().expect("MainMenu not found?");
                    main_menu.draw(window);
                }
                GameState::InGame => {}
                _ => panic!("Invalid GameState in SkyFall::draw"),
            }
        }
    }
}
