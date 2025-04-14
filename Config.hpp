#pragma once

#include <string>

class Config
{
public:
    virtual ~Config() {}
    virtual const std::string &getValue(std::string &key) = 0;
    virtual const std::string &getValue(const char *key) = 0;
};

class ConfigManager
{
private:
    static Config *config;

public:
    static Config &buildConfig(int argc, char *argv[]);
    static Config &getConfig();
};
