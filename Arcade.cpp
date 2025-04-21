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
#include <string.h>

class Arcade : public Configurable, Loggable<LogModules::main>
{
private:
    std::unique_ptr<Screen> screen;
    std::unique_ptr<User> user;

    void playMainIntro()
    {
        screen->clean();

        const char *arcade[] = {
            "            _____     _____              _____    ______ ",
            "    /\\     |  __ \\   / ____|     /\\     |  __ \\  |  ____|",
            "   /  \\    | |__) | | |         /  \\    | |  | | | |__   ",
            "  / /\\ \\   |  _  /  | |        / /\\ \\   | |  | | |  __|  ",
            " / ____ \\  | | \\ \\  | |____   / ____ \\  | |__| | | |____ ",
            "/_/    \\_\\ |_|  \\_\\  \\_____| /_/    \\_\\ |_____/  |______|"};

        const int arcade_y = sizeof(arcade) / sizeof(arcade[0]);
        const int arcade_x = strlen(arcade[0]);

        for (int i = 99; i > 49; i--)
        {
            screen->printObjectCenterAligned(25, i, arcade, arcade_y, arcade_x);
            screen->render();
            usleep(25000);
            if (i != 50)
            {
                screen->clearAreaCenterAligned(25, i, arcade_y, arcade_x);
            }
        }

        const char *terminal[] = {
            " _______   ______   _____    __  __   _____   _   _              _      ",
            "|__   __| |  ____| |  __ \\  |  \\/  | |_   _| | \\ | |     /\\     | |     ",
            "   | |    | |__    | |__) | | \\  / |   | |   |  \\| |    /  \\    | |     ",
            "   | |    |  __|   |  _  /  | |\\/| |   | |   | . ` |   / /\\ \\   | |     ",
            "   | |    | |____  | | \\ \\  | |  | |  _| |_  | |\\  |  / ____ \\  | |____ ",
            "   |_|    |______| |_|  \\_\\ |_|  |_| |_____| |_| \\_| /_/    \\_\\ |______|"};

        const int terminal_y = sizeof(terminal) / sizeof(terminal[0]);
        const int terminal_x = strlen(terminal[0]);

        for (int i = 0; i < 51; i++)
        {
            screen->printObjectCenterAligned(50, i, terminal, terminal_y, terminal_x);
            screen->render();
            usleep(25000);
            if (i != 50)
            {
                screen->clearAreaCenterAligned(50, i, terminal_y, terminal_x);
            }
        }
        screen->printStringCenterAligned(0, 50, "!!! Welcome !!!");
        screen->printStringCenterAligned(80, 50, "Press enter to continue");
        screen->printStringCenterAligned(95, 50, "Copyright 2025 Selahaddin Islamoglu, All rights reserved.");
        screen->printStringCenterAligned(99, 50, "https://islamoglu.github.io/");
        screen->render();
        sleep(20);
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
