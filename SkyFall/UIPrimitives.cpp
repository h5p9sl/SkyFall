#include "UIPrimitives.hpp"
#include "SkyFall.hpp"

using namespace SkyFall;

UIButton::UIButton(const sf::Texture& texture, const sf::Vector2f& pos, const std::string& label) :
    sprite(texture),
    text(label, globals->fontPLACEHOLDER)
{
    this->sprite.setPosition(pos);
    this->text.setString(label);

    sf::Vector2f newScale;
    sf::FloatRect currentSize = this->sprite.getLocalBounds();
    newScale.x = 400.f / currentSize.width;
    newScale.y = 200.f / currentSize.height;

    this->sprite.setScale(newScale);
}

bool UIButton::isPressed()
{
    sf::Window& mainWindow = globals->baseGame->mainWindow;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        mainWindow.hasFocus()) {
        auto mousePos = sf::Mouse::getPosition(mainWindow);
        auto myPos = this->sprite.getGlobalBounds();

        return (
            mousePos.x >= myPos.left &&
            mousePos.x <= myPos.left + myPos.width &&
            mousePos.y >= myPos.top &&
            mousePos.y <= myPos.top + myPos.height
            );
    }

    return false;
}

bool UIButton::update()
{
    sf::Vector2f pos = this->sprite.getPosition();
    this->text.setPosition(pos);

    return this->isPressed();
}

void UIButton::draw(sf::RenderTarget & renderTarget)
{
    renderTarget.draw(this->sprite);
    renderTarget.draw(this->text);
}
