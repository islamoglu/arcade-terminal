#include "arcade.hpp"
#include "config.hpp"
#include "log.hpp"
#include <unistd.h>

int main(int argc, char **argv)
{
    try
    {
        Arcade arcade;
        std::string log_file = "log.txt";
        std::string config_file = "../config/config.json";
        int opt;

        while ((opt = getopt(argc, argv, "c:l:")) != -1)
        {
            switch (opt)
            {
            case 'c':
                config_file = optarg;
            case 'l':
                log_file = optarg;
            }
        }

        LogManager::init_logger(log_file);
        ConfigManager::load_config(config_file);

        INFO("Arcade starting...");
        arcade.run();
        INFO("Arcade terminating...");
    }
    catch (const std::exception &e)
    {
        ERROR("Main Exception: {}", e.what());
    }
    return 0;
}