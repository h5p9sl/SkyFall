#include "BaseGame.hpp"
#include "SkyFall.hpp"

using namespace SkyFall;

int main()
{
    globals = new SkyFall::GlobalVariables();
    globals->initializeGlobals();

    globals->baseGame->beginGameLoop();

    delete globals->baseGame;

    return 0;
}
