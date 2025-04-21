#pragma once

#include <string>
#include <memory>
#include "Config.hpp"

class Screen
{
public:
    virtual void printString(int y, int x, std::string text) = 0;
    virtual void printStringCenterAligned(int y, int x, std::string text) = 0;
    virtual void printObject(int y, int x, const char **object, int object_y, int object_x) = 0;
    virtual void printObjectCenterAligned(int y, int x, const char **object, int object_y, int object_x) = 0;
    virtual void clearArea(int y, int x, int object_y, int object_x) = 0;
    virtual void clearAreaCenterAligned(int y, int x, int object_y, int object_x) = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
    virtual std::string readInput(const char *title) = 0;
    virtual ~Screen() {};
};

class ScreenFactory : public Configurable
{
private:
    static std::unordered_map<std::string, std::function<std::unique_ptr<Screen>()>> *screenCreators;

public:
    static void registerScreenCreator(std::string type, std::function<std::unique_ptr<Screen>()> creator);
    static std::unique_ptr<Screen> createScreen();
};