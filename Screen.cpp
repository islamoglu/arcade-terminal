#include "Screen.hpp"
#include "Config.hpp"
#include <string>
#include <string.h>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <curses.h>

class TerminalScreen : public Screen
{
public:
    TerminalScreen()
    {
        initscr();            // Start ncurses mode
        cbreak();             // Disable line buffering
        noecho();             // Don't echo() while we do getch
        keypad(stdscr, TRUE); // Enable F1, arrow keys, etc.
    }

    ~TerminalScreen() override
    {
        endwin();
    }

    void render() override
    {
        refresh();
    }

    void clean() override
    {
        clear();
    }

    std::string readInput(const char *title) override
    {
        echo();
        char input[256];
        int x = (COLS - strlen(title)) / 2;
        int y = LINES / 2 - 1;
        mvprintw(y, x, "%s :", title);
        mvprintw(y + 2, x, "Press enter to save ...");
        mvprintw(y + 1, x, ">> ");
        refresh();
        getstr(input);
        noecho();
        clear();
        return std::string(input);
    }
};

std::unique_ptr<Screen> ScreenManager::screen = nullptr;

Screen &ScreenManager::buildScreen()
{
    if (screen.get() != nullptr)
    {
        delete screen.get();
    }

    std::string screenType = ConfigManager::getConfig().getValue("screenType");
    if (screenType == "terminal")
    {
        screen = std::make_unique<TerminalScreen>();
    }
    else
    {
        throw std::runtime_error("Unknown screen type: " + screenType);
    }

    if (screen == nullptr)
    {
        throw std::runtime_error("Failed to create screen");
    }

    return *screen.get();
}

Screen &ScreenManager::getScreen()
{
    if (screen == nullptr)
    {
        buildScreen();
    }

    return *screen;
}