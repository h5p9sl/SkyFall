#include "BaseGame.hpp"
#include "SkyFall.hpp"

#include <iostream>

using namespace SkyFall;

int main()
{

    std::cout << "Initializing game..." << std::endl;

    globals = new SkyFall::GlobalVariables();
    globals->initializeGlobals();

    std::cout << "Starting game loop..." << std::endl;

    globals->baseGame->beginGameLoop();

    delete globals->baseGame;

    return 0;
}
