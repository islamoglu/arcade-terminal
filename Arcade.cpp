#include "Config.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Screen.hpp"
#include "Game.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <unistd.h>

class Arcade : public Configurable, Loggable<LogModules::main>
{
private:
    std::unique_ptr<Screen> screen;
    std::unique_ptr<User> user;

    void playMainIntro()
    {
        screen->clean();
        screen->printStringCenterAligned(1, 50, "!!! Welcome !!!");
        screen->printStringCenterAligned(80, 50, "Press enter to continue");
        screen->printStringCenterAligned(95, 50, "Copyright 2025 Selahaddin Islamoglu, All rights reserved.");
        screen->printStringCenterAligned(99, 50, "https://islamoglu.github.io/");
        screen->render();
        sleep(2);
    }
    void getUserInfo()
    {
        // user->getUserInfo(screen);
    }

public:
    Arcade()
    {
        screen = ScreenFactory::createScreen();
        user = UserFactory::createUser();
    }
    void run()
    {
        playMainIntro();
        getUserInfo();

        // Select game

        // Start game

        // Exit
    }
};

int main(int argc, char *argv[])
{
    try
    {
        std::unique_ptr<Config> config = ConfigFactory::createConfig(argc, argv);
        Configurable::setConfig(std::move(config));

        Arcade arcade;
        arcade.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
