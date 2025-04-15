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
        std::unique_ptr<Logger> logger = LoggerFactory::createLogger(config);
        logger->log("Starting program");

        // Display intro
        std::unique_ptr<Screen> screen = ScreenFactory::createScreen(config);
        screen->displayIntro();

        // Get user info
        std::unique_ptr<User> user = UserFactory::createUser(config);
        user->getUserInfo(screen);
        logger->log("User: " + user->getName());

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
