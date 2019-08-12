#include "input.hpp"

#include <string.h>

Input* Input::instance = nullptr;

Input::Input()
{
}

Input * Input::getInstance()
{
    if (Input::instance == nullptr) {
        Input::instance = new Input();
    }
    return Input::instance;
}

Input::~Input()
{
}

void Input::updateStates()
{
    auto instance = getInstance();
    memcpy(instance->lastKeyStates, instance->currentKeyStates, sizeof(currentKeyStates));
    memcpy(instance->lastButtonStates, instance->currentButtonStates, sizeof(currentButtonStates));
}

void Input::onKeyDown(sf::Keyboard::Key t_key)
{
    getInstance()->currentKeyStates[t_key] = true;
}

void Input::onKeyUp(sf::Keyboard::Key t_key)
{
    getInstance()->currentKeyStates[t_key] = false;
}

void Input::onButtonDown(sf::Mouse::Button t_button)
{
    getInstance()->currentButtonStates[t_button] = true;
}

void Input::onButtonUp(sf::Mouse::Button t_button)
{
    getInstance()->currentButtonStates[t_button] = false;
}

bool Input::isKeyPressed(sf::Keyboard::Key t_key)
{
    auto instance = getInstance();
    return instance->currentKeyStates[t_key];
}

bool Input::wasKeyPressed(sf::Keyboard::Key t_key)
{
    auto instance = getInstance();
    return instance->currentKeyStates[t_key] &&
        !instance->lastKeyStates[t_key];
}

bool Input::wasKeyReleased(sf::Keyboard::Key t_key)
{
    auto instance = getInstance();
    return instance->lastKeyStates[t_key] &&
        !instance->currentKeyStates[t_key];
}

bool Input::isButtonPressed(sf::Mouse::Button t_button)
{
    auto instance = getInstance();
    return instance->currentButtonStates[t_button];
}

bool Input::wasButtonPressed(sf::Mouse::Button t_button)
{
    auto instance = getInstance();
    return instance->currentButtonStates[t_button] &&
        !instance->lastButtonStates[t_button];
}

bool Input::wasButtonReleased(sf::Mouse::Button t_button)
{
    auto instance = getInstance();
    return instance->lastButtonStates[t_button] &&
        !instance->currentButtonStates[t_button];
}
