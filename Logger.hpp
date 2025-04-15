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

class LoggerFactory
{
private:
    static std::unordered_map<std::string, std::function<std::unique_ptr<Logger>()>> *loggerCreators;

public:
    static void registerLoggerCreator(std::string type, std::function<std::unique_ptr<Logger>()> creator);
    static std::unique_ptr<Logger> createLogger(std::unique_ptr<Config> &config);
};