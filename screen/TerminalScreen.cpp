#include "Screen.hpp"
#include "Config.hpp"
#include "Logger.hpp"
#include <string>
#include <string.h>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <curses.h>

class TerminalScreen : public Screen, Loggable<LogModules::screen>
{
public:
    TerminalScreen()
    {
        initscr(); // Start ncurses mode
        cbreak();  // Disable line buffering
        noecho();  // Don't echo() while we do getch
        // nodelay(stdscr, TRUE); // Make getch() non-blocking
        keypad(stdscr, TRUE); // Enable F1, arrow keys, etc.
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        attron(COLOR_PAIR(1));

        LOG("lines: " + std::to_string(LINES));
        LOG("columns: " + std::to_string(COLS));
    }

    ~TerminalScreen()
    {
        attroff(COLOR_PAIR(1));
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

    void printStringRaw(int y, int x, std::string text, bool center)
    {
        int col = COLS * x / 100 - (center ? text.length() / 2 : 0);
        int row = LINES * y / 100;
        mvprintw(row, col, "%s", text.c_str());
    }

    void printString(int y, int x, std::string text) override
    {
        printStringRaw(y, x, text, false);
    }

    void printStringCenterAligned(int y, int x, std::string text) override
    {
        printStringRaw(y, x, text, true);
    }

    std::string readInput(const char *title) override
    {
        echo();
        char input[256];
        int x = (COLS - strlen(title)) / 2;
        int y = LINES / 2 - 2;
        mvprintw(y, x, "%s :", title);
        mvprintw(y + 4, x, "Press enter to save ...");
        mvprintw(y + 2, x, ">> ");
        refresh();
        getstr(input);
        noecho();
        clear();
        return std::string(input);
    }
};

__attribute__((constructor)) void initTerminalScreen()
{
    ScreenFactory::registerScreenCreator("terminal", []() -> std::unique_ptr<Screen>
                                         { return std::make_unique<TerminalScreen>(); });
}