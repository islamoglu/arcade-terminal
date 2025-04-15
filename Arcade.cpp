#include "Config.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Screen.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

int main(int argc, char *argv[])
{
    try
    {
        std::unique_ptr<Config> config = ConfigFactory::createConfig(argc, argv);
        Configurable::setConfig(std::move(config));

        std::unique_ptr<Logger> logger = LoggerFactory::createLogger();
        Loggable::setLogger(std::move(logger));

        Loggable::getLogger()->log("Starting program");

        // Display intro
        std::unique_ptr<Screen> screen = ScreenFactory::createScreen();
        screen->displayIntro();

        // Get user info
        std::unique_ptr<User> user = UserFactory::createUser();
        user->getUserInfo(screen);
        Loggable::getLogger()->log("User: " + user->getName());

        // Select game

        // Start game

        // Save results

        // Exit
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
