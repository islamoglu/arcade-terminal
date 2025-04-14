#pragma once

#include <string>
#include "Config.hpp"

class Logger
{
public:
    virtual ~Logger() {}

    virtual void log(const std::string &message) = 0;
};

class LogManager
{
private:
    static Logger *logger;

public:
    static Logger &buildLogger();
    static Logger &getLogger();
};