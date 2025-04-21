#include "Game.hpp"
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include <curses.h> //TODO need to be removed

std::vector<std::unique_ptr<Game>> *GameRepository::games = nullptr;

void GameRepository::registerGame(std::unique_ptr<Game> game)
{
    if (games == nullptr)
    {
        games = new std::vector<std::unique_ptr<Game>>();
    }
    games->push_back(std::move(game));
}

std::unique_ptr<Game> &GameRepository::chooseGame(std::unique_ptr<Screen> &screen)
{
    if (games == nullptr)
    {
        throw std::runtime_error("No games registered");
    }

    int i = 0;
    while (true)
    {
        std::unique_ptr<Game> &game = (*games)[i];
        game->displayIntro(screen);
        int read = screen->readInputChar();
        if (read == KEY_LEFT)
        {
            i--;
            if (i == -1)
            {
                i = games->size() - 1;
            }
        }
        else if (read == KEY_RIGHT)
        {
            i++;
            if (i == games->size())
            {
                i = 0;
            }
        }
        else if (read == KEY_ENTER)
        {
            return game;
        }
    }
}
