#pragma once

#include <SFML/Graphics.hpp>

class Input
{
private:
    static Input* instance;
    // Keyboard
    bool currentKeyStates[128] = { false };
    bool lastKeyStates[128] = { false };
    // Mouse
    bool currentButtonStates[5] = { false };
    bool lastButtonStates[5] = { false };
private:
    Input();
    static Input* getInstance();
public:
    ~Input();
public:
    // Called every frame
    // Sets currentKeyStates to lastKeyStates
    static void updateStates();

    // Key change events
    static void onKeyDown(sf::Keyboard::Key t_key);
    static void onKeyUp(sf::Keyboard::Key t_key);
    static void onButtonDown(sf::Mouse::Button t_button);
    static void onButtonUp(sf::Mouse::Button t_button);
    // Key state checking
    static bool isKeyPressed(sf::Keyboard::Key t_key);
    static bool wasKeyPressed(sf::Keyboard::Key t_key);
    static bool wasKeyReleased(sf::Keyboard::Key t_key);
    // Button state checking
    static bool isButtonPressed(sf::Mouse::Button t_button);
    static bool wasButtonPressed(sf::Mouse::Button t_button);
    static bool wasButtonReleased(sf::Mouse::Button t_button);
};
