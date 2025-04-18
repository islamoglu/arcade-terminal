#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include <typeindex>
#include <cxxabi.h>
#include "Config.hpp"

#define LOG(message) getLogger()->log(getModuleName() + ":" + getClassName() + ": " + message)

#define GENERATE_ENUM(X) X,
#define GENERATE_STRING(X) #X,

#define ALL_LOGGER_IDS(FUNCTION) \
    FUNCTION(main)               \
    FUNCTION(config)             \
    FUNCTION(game)               \
    FUNCTION(logging)            \
    FUNCTION(screen)             \
    FUNCTION(user)

enum class LogModules
{
    ALL_LOGGER_IDS(GENERATE_ENUM)
};

static std::string LogModuleStrings[] = {
    ALL_LOGGER_IDS(GENERATE_STRING)};

class Logger
{
public:
    virtual void log(const std::string &message) = 0;
};

class LoggerFactory : public Configurable
{
private:
    static std::unordered_map<std::string, std::function<std::unique_ptr<Logger>()>> *loggerCreators;

public:
    static void registerLoggerCreator(std::string type, std::function<std::unique_ptr<Logger>()> creator);
    static std::unique_ptr<Logger> createLogger(LogModules module);
};

template <LogModules module>
class Loggable
{
private:
    std::string demangle(const char *name)
    {
        int status = 0;
        char *realname = abi::__cxa_demangle(name, 0, 0, &status);
        std::string result = (status == 0 && realname) ? realname : name;
        free(realname);
        return result;
    };

protected:
    std::unique_ptr<Logger> &getLogger()
    {
        static std::unique_ptr<Logger> logger = LoggerFactory::createLogger(module);
        return logger;
    };
    std::string &getModuleName()
    {
        static std::string &moduleName = LogModuleStrings[static_cast<int>(module)];
        return moduleName;
    }
    std::string &getClassName()
    {
        static std::string className = demangle(typeid(*this).name());
        return className;
    };
    virtual ~Loggable() {};
};