#pragma once
#include <vector>

#include "GameSave.hpp"

class GameSaveManager
{
private:
    std::vector<GameSave*> gameSaves;
public:
    void loadGameSaves();
    void createGameSave(GameSave& newSave);
};