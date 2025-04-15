#include "Config.hpp"
#include <unordered_map>
#include <stdexcept>
#include <functional>
#include <memory>

class DefaultConfig : public Config
{
private:
    std::unordered_map<std::string, std::string> defaultValues = {
        {"loggerType", "file"},
        {"userType", "local"},
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

__attribute__((constructor)) void initDefaultConfig()
{
    ConfigFactory::registerConfigCreator("default", []() -> std::unique_ptr<Config>
                                         { return std::make_unique<DefaultConfig>(); });
}