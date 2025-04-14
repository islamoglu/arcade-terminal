#include "Log.hpp"
#include <iostream>
#include <fstream>

class FileLogger : public Logger
{
private:
    std::ofstream file;
    std::string filename;

public:
    FileLogger(const std::string &filename) : filename(filename)
    {
        file.open(filename, std::ios::out | std::ios::app);
    }

    ~FileLogger()
    {
        file.close();
    }

    void log(const std::string &message) override
    {
        file << message << std::endl;
    }
};

Logger *LogManager::logger = nullptr;

Logger &LogManager::buildLogger()
{
    if (logger != nullptr)
    {
        delete logger;
        logger = nullptr;
    }

    std::string loggerType = ConfigManager::getConfig().getValue("loggerType");
    if (loggerType == "file")
    {
        logger = new FileLogger("log.txt");
    }
    else
    {
        throw std::runtime_error("Unknown logger type: " + loggerType);
    }

    if (logger == nullptr)
    {
        throw std::runtime_error("Failed to create logger");
    }

    return *logger;
}

Logger &LogManager::getLogger()
{
    if (logger == nullptr)
    {
        buildLogger();
    }
    return *logger;
}
