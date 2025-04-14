#include "Config.hpp"
#include <unordered_map>
#include <stdexcept>

class DefaultConfig : public Config
{
private:
    std::unordered_map<std::string, std::string> defaultValues = {
        {"loggerType", "file"},
        {"userType", "terminal"},
        {"screenType", "terminal"}};

public:
    const std::string &getValue(std::string &key) override
    {
        return defaultValues.at(key);
    }
    const std::string &getValue(const char *key) override
    {
        return defaultValues.at(key);
    }
};

Config *ConfigManager::config = nullptr;

Config &ConfigManager::buildConfig(int argc, char *argv[])
{
    if (config != nullptr)
    {
        delete config;
        config = nullptr;
    }

    config = new DefaultConfig();

    if (config == nullptr)
    {
        throw std::runtime_error("Failed to create config");
    }

    return *config;
}

Config &ConfigManager::getConfig()
{
    if (config == nullptr)
    {
        config = new DefaultConfig();

        if (config == nullptr)
        {
            throw std::runtime_error("Failed to create config");
        }
    }

    return *config;
}
