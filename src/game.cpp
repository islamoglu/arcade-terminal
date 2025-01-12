#include "game.hpp"

Game::Game(std::string name)
{
    this->name = name;
}

std::string Game::getName()
{
    return name;
}

std::vector<Game *> GameRepository::games;

void GameRepository::registerGame(Game *game)
{
    games.push_back(game);
}

std::vector<Game *> GameRepository::getGames()
{
    return games;
}
