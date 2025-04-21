#include "Game.hpp"

class Snake : public Game
{
public:
    void displayIntro(std::unique_ptr<Screen> &screen) override
    {
        screen->clean();
        screen->printStringCenterAligned(20, 50, "Snake");
    }
    void play() override
    {
    }
    const char *getName() override
    {
        return "Snake";
    }
};

__attribute__((constructor)) void registerSnake()
{
    GameRepository::registerGame(std::make_unique<Snake>());
}