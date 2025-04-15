#pragma once

#include <string>
#include <memory>
#include "Config.hpp"

class Screen
{
public:
    virtual void render() = 0;
    virtual void clean() = 0;
    virtual std::string readInput(const char *title) = 0;
    virtual void displayIntro() = 0;
    virtual ~Screen() {}
};

class ScreenFactory
{
private:
    static std::unordered_map<std::string, std::function<std::unique_ptr<Screen>()>> *screenCreators;

public:
    static void registerScreenCreator(std::string type, std::function<std::unique_ptr<Screen>()> creator);
    static std::unique_ptr<Screen> createScreen(std::unique_ptr<Config> &config);
};