#include "config.hpp"
#include "log.hpp"
#include <fstream>

Config::Config(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        INFO("Unable to open config file {}", filename);
    }
    else
    {
        file >> config_json;
        INFO("Config content: \n{}", config_json.dump(4));
        file.close();
    }
}

std::string Config::get_config(const std::string &key, const std::string &defaultValue)
{
    return config_json[key].get<std::string>();
}

std::shared_ptr<Config> ConfigManager::config_instance = nullptr;

void ConfigManager::load_config(const std::string &filename)
{
    config_instance = std::make_shared<Config>(filename);
}

std::string ConfigManager::get_config(const std::string &key, const std::string &defaultValue)
{
    return config_instance->get_config(key, defaultValue);
}
