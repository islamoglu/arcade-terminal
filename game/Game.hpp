#include "Screen.hpp"
#include <memory>

class Game
{
public:
    virtual void play() = 0;
};

class GameRepository
{
private:
    static std::unordered_map<std::string, std::unique_ptr<Game>> *games;

public:
    static void registerGame(std::string type, std::unique_ptr<Game> game);
    static std::unique_ptr<Game> chooseGame(std::unique_ptr<Screen> &screen);
};