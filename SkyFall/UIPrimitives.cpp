#include "UIPrimitives.hpp"
#include "SkyFall.hpp"

using namespace SkyFall;

UIButton::UIButton(const sf::Texture& texture, const sf::Vector2u& pos, const std::string& label) :
	sprite(texture),
	text(label, globals->fontPLACEHOLDER)
{
}

bool UIButton::update()
{
	auto pos = this->sprite.getPosition();
	this->text.setPosition(pos);
	
	// TODO: return true if clicked by user

	return false;
}

void UIButton::draw(sf::RenderTarget & renderTarget)
{
	renderTarget.draw(this->sprite);
	renderTarget.draw(this->text);
}
