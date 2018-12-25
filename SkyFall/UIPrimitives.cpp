#include "UIPrimitives.hpp"
#include "SkyFall.hpp"

using namespace SkyFall;

UIButton::UIButton(const sf::Texture& texture, const sf::IntRect& rect, const std::string& label) :
    sprite(texture),
    text(label, globals->fontPLACEHOLDER)
{
    this->sprite.setColor(sf::Color(
        0xff - this->highlightAmount,
        0xff - this->highlightAmount,
        0xff - this->highlightAmount,
        0xff));

    this->sprite.setPosition(static_cast<float>(rect.left),
        static_cast<float>(rect.top));
    this->text.setString(label);
    this->text.setOutlineColor(sf::Color::Black);
    this->text.setOutlineThickness(2.f);

    sf::Vector2f newScale;
    sf::FloatRect currentSize = this->sprite.getLocalBounds();
    newScale.x = rect.width / currentSize.width;
    newScale.y = rect.height / currentSize.height;

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
    // TODO: Make this return true when mouse1 is *RELEASED*
    sf::Window& mainWindow = globals->baseGame->mainWindow;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
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

    if (currentState && !this->lastHighlightState) {
        sf::Color currentColor = this->sprite.getColor();
        this->lastHighlightColor = currentColor;
        
        uint8_t t_highlightAmount = (mousedown) ? this->highlightAmount : this->highlightAmount / 2;

        currentColor.r += t_highlightAmount;
        currentColor.g += t_highlightAmount;
        currentColor.b += t_highlightAmount;

        this->sprite.setColor(currentColor);
    }
    else if (!currentState && this->lastHighlightState) {
        this->sprite.setColor(this->lastHighlightColor);
    }

    lastHighlightState = currentState;
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
