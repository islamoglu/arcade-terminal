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

    void printStringRaw(int y, int x, const char *text, bool center)
    {
        int col = COLS * x / 100 - (center ? strlen(text) / 2 : 0);
        int row = LINES * y / 100;
        mvprintw(row, col, "%s", text);
    }

    void printString(int y, int x, const char *text) override
    {
        printStringRaw(y, x, text, false);
    }

    void printStringCenterAligned(int y, int x, const char *text) override
    {
        printStringRaw(y, x, text, true);
    }

    void printObjectRaw(int y, int x, const char **object, int object_y, int object_x, bool center)
    {
        double start_x = 0;
        double start_y = 0;
        double finish_x = object_x;
        double finish_y = object_y;
        double start_col = (double)COLS * x / 100 - (center ? (double)object_x / 2 : 0);
        double start_row = (double)LINES * y / 100 - (center ? (double)object_y / 2 : 0);

        if (start_col >= (double)COLS || start_row >= (double)LINES)
            return;
        if (start_col + (double)object_x < 0 || start_row + (double)object_y < 0)
            return;

        if (start_col < 0)
        {
            start_x = -start_col;
            start_col = 0;
        }
        if (start_row < 0)
        {
            start_y = -start_row;
            start_row = 0;
        }

        if (start_col + (double)object_x >= (double)COLS)
        {
            finish_x = (double)COLS - start_col;
        }
        if (start_row + object_y >= (double)LINES)
        {
            finish_y = (double)LINES - start_row;
        }

        for (int i = (int)start_y; i < (int)finish_y; i++)
        {
            mvprintw((int)start_row + i, (int)start_col, "%.*s", (int)finish_x + 1 - (int)start_x, object[i] + (int)start_x);
        }
    }

    void printObject(int y, int x, const char **object, int object_y, int object_x) override
    {
        printObjectRaw(y, x, object, object_y, object_x, false);
    }

    void printObjectCenterAligned(int y, int x, const char **object, int object_y, int object_x) override
    {
        printObjectRaw(y, x, object, object_y, object_x, true);
    }

    void clearArea(int y, int x, int object_y, int object_x) override
    {
        int col = COLS * x / 100;
        int row = LINES * y / 100;
        for (int i = 0; i < object_y; i++)
        {
            mvprintw(row + i, col, "%s", std::string(object_x, ' ').c_str());
        }
    }

    void clearAreaCenterAligned(int y, int x, int object_y, int object_x) override
    {
        double col = (double)COLS * (double)x / 100 - (double)object_x / 2;
        double row = (double)LINES * (double)y / 100 - (double)object_y / 2;
        for (int i = 0; i < object_y; i++)
        {
            mvprintw((int)row + i, (int)col, "%s", std::string(object_x, ' ').c_str());
        }
    }

    std::string readInput(const char *title) override
    {
        clear();
        echo();
        char input[256];
        printStringCenterAligned(40, 50, title);
        printStringCenterAligned(60, 50, "Press enter to save ...");
        printStringCenterAligned(50, 50, ">> ");
        refresh();
        getstr(input);
        noecho();
        clear();
        return std::string(input);
    }

    int readInputChar() override
    {
        return getch();
    }
};

__attribute__((constructor)) void initTerminalScreen()
{
    ScreenFactory::registerScreenCreator("terminal", []() -> std::unique_ptr<Screen>
                                         { return std::make_unique<TerminalScreen>(); });
}