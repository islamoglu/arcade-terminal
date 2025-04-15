#include "Screen.hpp"
#include "Config.hpp"
#include "Logger.hpp"
#include <string>
#include <string.h>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <curses.h>

class TerminalScreen : public Screen, Loggable
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
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        // welcome

        // name
        const char *arcade[]{

            "    _     ____    ____     _     ____   _____ ",
            "   / \\   |  _ \\  / ___|   / \\   |  _ \\ | ____|",
            "  / _ \\  | |_) || |      / _ \\  | | | ||  _|  ",
            " / ___ \\ |  _ < | |___  / ___ \\ | |_| || |___ ",
            "/_/   \\_\\|_| \\_\\ \\____|/_/   \\_\\|____/ |_____|"

        };

        const char *terminal[]{
            " _____  _____  ____   __  __  ___  _   _     _     _     ",
            "|_   _|| ____||  _ \\ |  \\/  ||_ _|| \\ | |   / \\   | |    ",
            "  | |  |  _|  | |_) || |\\/| | | | |  \\| |  / _ \\  | |    ",
            "  | |  | |___ |  _ < | |  | | | | | |\\  | / ___ \\ | |___ ",
            "  |_|  |_____||_| \\_\\|_|  |_||___||_| \\_|/_/   \\_\\|_____|"

        };

        getLogger()->log(std::to_string(sizeof(arcade)));
        getLogger()->log(std::to_string(sizeof(arcade[0])));

        const int arcade_frame = sizeof(arcade) / sizeof(arcade[0]);
        const int arcade_char = sizeof(arcade[0]);
        const int terminal_frame = sizeof(terminal) / sizeof(terminal[0]);
        const int terminal_char = sizeof(terminal[0]);

        int frame = 0;
        int y = LINES / 2 - arcade_frame / 2;
        int x = COLS;
        while (true)
        {
            mvprintw(y, x, arcade[frame]);
            refresh();
            frame++;
            y++;
            if (frame == arcade_frame)
            {
                frame = 0;
                y = LINES / 2 - arcade_frame / 2;
                x--;
                if (x == (COLS - 46) / 2)
                {
                    break;
                }
                napms(25);
                clear();
            }
        }
        // press enter
        getch();

        attroff(COLOR_PAIR(1));
        clear();
    }
};

__attribute__((constructor)) void initTerminalScreen()
{
    ScreenFactory::registerScreenCreator("terminal", []() -> std::unique_ptr<Screen>
                                         { return std::make_unique<TerminalScreen>(); });
}