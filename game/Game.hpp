#include "Screen.hpp"
#include "Logger.hpp"
#include <memory>

class Game
{
public:
    virtual void displayIntro(std::unique_ptr<Screen> &screen) = 0;
    virtual void play() = 0;
    virtual const char *getName() = 0;
};

class GameRepository
{
private:
    static std::vector<std::unique_ptr<Game>> *games;

public:
    static void registerGame(std::unique_ptr<Game> game);
    static std::unique_ptr<Game> &chooseGame(std::unique_ptr<Screen> &screen);
};