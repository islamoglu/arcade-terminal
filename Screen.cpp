#include "Screen.hpp"
#include "Config.hpp"
#include <functional>

std::unordered_map<std::string, std::function<std::unique_ptr<Screen>()>> *ScreenFactory::screenCreators = nullptr;

void ScreenFactory::registerScreenCreator(std::string type, std::function<std::unique_ptr<Screen>()> creator)
{
    if (screenCreators == nullptr)
    {
        screenCreators = new std::unordered_map<std::string, std::function<std::unique_ptr<Screen>()>>();
    }
    screenCreators->insert({type, creator});
}

std::unique_ptr<Screen> ScreenFactory::createScreen(std::unique_ptr<Config> &config)
{
    std::string screenType = config->getValue("screenType");
    std::function<std::unique_ptr<Screen>()> creator = screenCreators->at(screenType);
    return creator();
}
