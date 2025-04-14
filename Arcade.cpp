#include "Config.hpp"
#include "Log.hpp"
#include "User.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    try
    {
        ConfigManager::buildConfig(argc, argv);
        Logger &logger = LogManager::buildLogger();
        logger.log("Starting program");

        // Get user info
        User *user = UserManager::getUser();

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
