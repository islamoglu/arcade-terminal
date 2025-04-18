#include "Logger.hpp"
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
        file.open(filename, std::ios::out);
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

__attribute__((constructor)) void initFileLogger()
{
    LoggerFactory::registerLoggerCreator("file", []() -> std::unique_ptr<Logger>
                                         { return std::make_unique<FileLogger>("log.txt"); });
}