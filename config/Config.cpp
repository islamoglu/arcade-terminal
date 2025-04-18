#include "Config.hpp"
#include <unordered_map>
#include <stdexcept>
#include <functional>
#include <memory>

std::unique_ptr<Config> Configurable::config = nullptr;

std::unordered_map<std::string, std::function<std::unique_ptr<Config>()>> *ConfigFactory::configCreators = nullptr;

void ConfigFactory::registerConfigCreator(std::string type, std::function<std::unique_ptr<Config>()> creator)
{
    if (configCreators == nullptr)
    {
        configCreators = new std::unordered_map<std::string, std::function<std::unique_ptr<Config>()>>();
    }
    configCreators->insert({type, creator});
}

std::unique_ptr<Config> ConfigFactory::createConfig(int argc, char *argv[])
{
    std::string configType = "default";
    if (argv[1] != nullptr)
    {
        configType = argv[1];
    }

    std::function<std::unique_ptr<Config>()> creator = configCreators->at(configType);
    return creator();
}
