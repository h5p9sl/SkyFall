use crate::gamestate::GameState;
use crate::main_menu::MainMenu;
use ::backend::RenderWindow;
use piston::Input;

pub struct SkyFall {
    last_state: GameState,
    state: GameState,
    // Use std::vec here so we can dynamically allocate and free the main menu
    main_menu: Vec<MainMenu>,
}

impl SkyFall {
    pub fn new() -> SkyFall {
        SkyFall {
            last_state: GameState::Invalid,
            state: GameState::MainMenu,
            main_menu: Vec::new(),
        }
    }

    fn initialize_main_menu(&mut self) {
        self.main_menu.push(MainMenu::new());
    }

    /// Ensures that the current game state is not initialized:
    ///
    /// An "uninitialized game state" in the context of MainMenu would mean that the
    /// main menu is currently uninitialized and it is not safe to draw or pass input
    /// to the main menu while it is uninitialized.
    fn ensure_valid_state(&self) -> bool {
        self.last_state != GameState::Invalid
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
                    main_menu.on_input(input);
                }
                _ => panic!("Invalid GameState in SkyFall::on_input"),
            }
        }
    }

    /// Called once per frame, updates game-state
    ///
    /// In summary, this function sets `self.last_state` = `self.state`
    fn update_state(&mut self) {
        self.last_state = self.state;
    }

    /// Called once per frame, updates game based on current GameState.
    ///
    /// For example, if the current game-state is MainMenu, the main menu will be **updated**.
    pub fn update(&mut self, delta: f64) {
        match self.state {
            GameState::MainMenu => {
                if self.last_state != GameState::MainMenu {
                    self.initialize_main_menu();
                }
                let main_menu = self.main_menu.first_mut().expect("MainMenu not found?");
                main_menu.update(delta);
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
                _ => panic!("Invalid GameState in SkyFall::draw"),
            }
        }
    }
}
