#include <string>
#include <vector>

class Game
{
public:
    Game(std::string name);
    std::string getName();
    virtual ~Game() = default;
    virtual void intro() = 0;
    virtual void run() = 0;
    virtual void cleanup() = 0;

private:
    std::string name;
};

class GameRepository
{
public:
    static void registerGame(Game *game);
    static std::vector<Game *> getGames();

private:
    static std::vector<Game *> games;
};