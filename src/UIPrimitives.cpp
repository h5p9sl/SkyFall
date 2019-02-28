#include "UIPrimitives.hpp"
#include "SkyFall.hpp"

using namespace SkyFall;

UIButton::UIButton(const sf::Texture& texture, const sf::IntRect& dimensions, const std::string& label) :
    sprite(texture),
    text(label, globals->fontPLACEHOLDER)
{
    this->sprite.setTextureRect({ 0, 0, 100, 40 });

    this->sprite.setPosition(static_cast<float>(dimensions.left),
        static_cast<float>(dimensions.top));
    this->text.setString(label);
    this->text.setOutlineColor(sf::Color::Black);
    this->text.setOutlineThickness(2.f);

    sf::Vector2f newScale;
    sf::FloatRect currentSize = this->sprite.getLocalBounds();
    newScale.x = dimensions.width / currentSize.width;
    newScale.y = dimensions.height / currentSize.height;

    this->sprite.setScale(newScale);
}

bool __inline UIButton::isMouseOnButton()
{
    sf::Window& mainWindow = globals->baseGame->mainWindow;
    sf::Vector2i mousePos = sf::Mouse::getPosition(mainWindow);
    sf::FloatRect myRect = this->sprite.getGlobalBounds();
    return myRect.contains(static_cast<float>(mousePos.x),
        static_cast<float>(mousePos.y));
}

bool UIButton::isPressed()
{
    sf::Window& mainWindow = globals->baseGame->mainWindow;

    if (Input::wasButtonReleased(sf::Mouse::Left) &&
        mainWindow.hasFocus())
    {
        return this->isMouseOnButton();
    }

    return false;
}

void UIButton::highlightOnHover()
{
    bool currentState;
    bool mousedown;

    currentState =  this->isMouseOnButton();
    mousedown =     sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (mousedown && currentState) {
        this->sprite.setTextureRect({ 200, 0, 100, 40 });
    }
    else if (currentState) {
        this->sprite.setTextureRect({ 100, 0, 100, 40 });
    }
    else {
        this->sprite.setTextureRect({ 0, 0, 100, 40 });
    }
}

void UIButton::centerText()
{
    sf::FloatRect bounds = this->sprite.getGlobalBounds();
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);

    sf::Vector2f pos;
    pos.x = bounds.left + bounds.width  / 2;
    pos.y = bounds.top  + bounds.height / 2;

    this->text.setPosition(pos);
}

bool UIButton::update()
{
    this->centerText();
    this->highlightOnHover();
    return this->isPressed();
}

void UIButton::draw(sf::RenderTarget & renderTarget)
{
    renderTarget.draw(this->sprite);
    renderTarget.draw(this->text);
}
