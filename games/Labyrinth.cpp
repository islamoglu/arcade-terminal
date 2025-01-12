#include "game.hpp"
#include "screen.hpp"
#include <unistd.h>

class Labyrinth : public Game
{
public:
    Labyrinth();
    void intro() override;
    void run() override;
    void cleanup() override;

private:
    Screen screen;
};

void __attribute__((constructor)) init()
{
    GameRepository::registerGame(new Labyrinth());
}

Labyrinth::Labyrinth() : Game("Labyrinth") {}

void Labyrinth::intro()
{
    screen.Start();
    screen.ClearScreen();
    screen.Print("Labyrinth");
    screen.Flush();
}

void Labyrinth::run()
{
    sleep(10);
}

void Labyrinth::cleanup()
{
    screen.End();
}