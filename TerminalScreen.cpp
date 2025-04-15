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
        int x = COLS / 3;
        int y = LINES / 2 - 1;
        mvprintw(y, x, "%s :", title);
        mvprintw(y + 4, x, "Press enter to save ...");
        mvprintw(y + 2, x, ">> ");
        refresh();
        getstr(input);
        noecho();
        clear();
        return std::string(input);
    }

    void displayIntro() override
    {
        const char *frames[] = {
            "  _______    _______  _______  _______  _______  ",
            " |       |  |       ||       ||       ||       | ",
            " |  __   |  |   _   ||   _   ||   _   ||   _   | ",
            " | /  \\  |  |  | |  ||  | |  ||  | |  ||  | |  | ",
            " | |  | |  |  | |  ||  |_|  ||  |_|  ||  |_|  | ",
            " | |__| |  |  |_|  ||       ||       ||       | ",
            " |_______|  |_______||_______||_______||_______| ",
            "                                        ",
            "                                        ",
            "                                        ",
            "                                        ",
            "                                        ",
            "                                        ",
            "                                        ",
            "                                        ",
            "                                        ",
        };
        const int num_frames = sizeof(frames) / sizeof(frames[0]);
        int frame = 0;
        int y = LINES / 2 - 1;
        while (true)
        {
            if (frame == 0)
                clear();
            int x = COLS - strlen(frames[frame]);
            mvprintw(y, x, frames[frame]);
            refresh();
            frame = (frame + 1) % num_frames;
            napms(100);
        }
    }
};

__attribute__((constructor)) void initTerminalScreen()
{
    ScreenFactory::registerScreenCreator("terminal", []() -> std::unique_ptr<Screen>
                                         { return std::make_unique<TerminalScreen>(); });
}