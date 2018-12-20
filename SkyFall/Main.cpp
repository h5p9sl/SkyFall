#include "BaseGame.hpp"

int main()
{
	BaseGame* baseGame = new BaseGame();

	baseGame->beginGameLoop();

	delete baseGame;
	return 0;
}