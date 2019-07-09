#pragma once
#include <vector>

#include "GameSave.hpp"

class GameSaveManager
{
private:
    std::vector<GameSave*> gameSaves;
public:
    // TODO: Create definitions for these functions
    void loadGameSaves();
    void createGameSave(GameSave& newSave);
};