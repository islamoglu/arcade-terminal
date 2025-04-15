#include "Logger.hpp"
#include "Config.hpp"

std::unique_ptr<Logger> Loggable::logger = nullptr;

std::unordered_map<std::string, std::function<std::unique_ptr<Logger>()>> *LoggerFactory::loggerCreators = nullptr;

void LoggerFactory::registerLoggerCreator(std::string type, std::function<std::unique_ptr<Logger>()> creator)
{
    if (loggerCreators == nullptr)
    {
        loggerCreators = new std::unordered_map<std::string, std::function<std::unique_ptr<Logger>()>>();
    }
    loggerCreators->insert({type, creator});
}

std::unique_ptr<Logger> LoggerFactory::createLogger()
{
    std::string loggerType = getConfig()->getValue("loggerType");
    std::function<std::unique_ptr<Logger>()> creator = loggerCreators->at(loggerType);
    return creator();
}
