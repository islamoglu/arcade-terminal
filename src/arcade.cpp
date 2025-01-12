#include "arcade.hpp"
#include "game.hpp"
#include "log.hpp"
#include <unistd.h>

Arcade::Arcade()
{
}

Arcade::~Arcade()
{
}

void Arcade::run()
{
    auto games = GameRepository::getGames();
    games[0]->intro();
    sleep(1);
    games[0]->cleanup();
}
