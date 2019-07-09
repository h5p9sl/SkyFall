#include "base/game.hpp"
#include "skyfall.hpp"

#include <iostream>
#include <string>
#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif
#include <errno.h>

using namespace SkyFall;

/* 
    Changes current working directory to the binary location so the
    program can successfully find the resources needed to run the game.
*/
void changeDirectory(char const* binLocation)
{
    std::string bin(binLocation);

    std::size_t lastSlash = bin.find_last_of('/');
    if (lastSlash == bin.npos) {
        throw std::runtime_error("invalid executable path???");
    }

    bin.erase(++lastSlash, bin.length() - lastSlash);

#ifdef _WIN32
    int r = _chdir(bin.c_str());
#else
    int r = chdir(bin.c_str());
#endif
    if (r == -1) {
        std::cerr << "errno = " << errno << '\n';
        throw std::runtime_error("chdir returned -1.");
    }
}

int main(int argc, char *argv[])
{
    std::cout << "Initializing game..." << std::endl;

    changeDirectory(argv[0]);

    globals = new SkyFall::GlobalVariables();
    globals->initializeGlobals();

    std::cout << "Starting game loop..." << std::endl;

    globals->baseGame->beginGameLoop();

    delete globals->baseGame;

    return 0;
}
