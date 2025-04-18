#include "Game.hpp"

std::unordered_map<std::string, std::unique_ptr<Game>> *GameRepository::games = nullptr;

void GameRepository::registerGame(std::string type, std::unique_ptr<Game> game)
{
    if (games == nullptr)
    {
        games = new std::unordered_map<std::string, std::unique_ptr<Game>>();
    }
    games->insert({type, std::move(game)});
}

std::unique_ptr<Game> GameRepository::chooseGame(std::unique_ptr<Screen> &screen)
{
    return nullptr;
}
