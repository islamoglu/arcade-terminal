#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include "Config.hpp"

class Logger
{
public:
    virtual void log(const std::string &message) = 0;
};

class Loggable
{
public:
    static void setLogger(std::unique_ptr<Logger> value) { logger = std::move(value); };
    static std::unique_ptr<Logger> &getLogger() { return logger; };

private:
    static std::unique_ptr<Logger> logger;
};

class LoggerFactory : public Configurable
{
private:
    static std::unordered_map<std::string, std::function<std::unique_ptr<Logger>()>> *loggerCreators;

public:
    static void registerLoggerCreator(std::string type, std::function<std::unique_ptr<Logger>()> creator);
    static std::unique_ptr<Logger> createLogger();
};