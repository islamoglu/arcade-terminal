#include "Game.hpp"

class Pacman : public Game
{
public:
    void displayIntro(std::unique_ptr<Screen> &screen) override
    {
        screen->clean();
        screen->printStringCenterAligned(20, 50, "Pacman");
    }
    void play() override
    {
    }
    const char *getName() override
    {
        return "Pacman";
    }
};

__attribute__((constructor)) void registerPacman()
{
    GameRepository::registerGame(std::make_unique<Pacman>());
}