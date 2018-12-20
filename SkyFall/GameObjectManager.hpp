#pragma once
#include <vector>

// Forward declarations
namespace sf {
	class RenderTarget;
	class Drawable;
}

class GameObjectManager
{
private:
	std::vector<sf::Drawable*> entityList;
public:
	GameObjectManager();
public:
	void drawObjects(sf::RenderTarget& renderTarget);
};
