#pragma once

#include <string>
#include <nlohmann/json.hpp>

class Config
{
public:
    Config(const std::string &filename);
    std::string get_config(const std::string &key, const std::string &defaultValue = "");

private:
    nlohmann::json config_json;
};

class ConfigManager
{
public:
    static void load_config(const std::string &filename);
    static std::string get_config(const std::string &key, const std::string &defaultValue = "");

private:
    static std::shared_ptr<Config> config_instance;
};
