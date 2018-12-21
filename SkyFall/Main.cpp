#include "BaseGame.hpp"
#include "SkyFall.hpp"

int main()
{
    SkyFall::globals = new SkyFall::GlobalVariables();

	BaseGame* baseGame = new BaseGame();

	baseGame->beginGameLoop();

	delete baseGame;
	return 0;
}
