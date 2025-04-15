#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

class Config
{
public:
    virtual ~Config() {}
    virtual const std::string &getValue(std::string &key) = 0;
    virtual const std::string &getValue(const char *key) = 0;
};

class Configurable
{
public:
    static void setConfig(std::unique_ptr<Config> value) { config = std::move(value); };
    static std::unique_ptr<Config> &getConfig() { return config; };

private:
    static std::unique_ptr<Config> config;
};

class ConfigFactory
{
private:
    static std::unordered_map<std::string, std::function<std::unique_ptr<Config>()>> *configCreators;

public:
    static void registerConfigCreator(std::string type, std::function<std::unique_ptr<Config>()> creator);
    static std::unique_ptr<Config> createConfig(int argc, char *argv[]);
};
