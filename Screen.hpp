#pragma once

#include <string>
#include <memory>

class Screen
{
public:
    virtual void render() = 0;
    virtual void clean() = 0;
    virtual std::string readInput(const char *title) = 0;
    virtual ~Screen() {}
};

class ScreenManager
{
private:
    static std::unique_ptr<Screen> screen;

public:
    static Screen &buildScreen();
    static Screen &getScreen();
};