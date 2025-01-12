#include "screen.hpp"
#include "log.hpp"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

// TODO refactor to not use string objects

Screen::Screen()
{
}

Screen::~Screen()
{
}

void Screen::Start()
{
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
    {
        ERROR("Failed to get terminal size");
        y = 50;
        x = 100;
    }
    else
    {
        INFO("Terminal size: {}x{}", w.ws_col, w.ws_row);
        y = (w.ws_row / 50) * 50;
        x = y * 2;
    }

    INFO("x={}, y={}", x, y);

    if (x == 0 || y == 0)
    {
        printf("Not enough screen space, Zoom out terminal!\n");
        exit(1);
    }

    HideCursorNow();
    ClearScreenNow();
}

void Screen::End()
{
    ClearScreenNow();
    ShowCursorNow();
}

void Screen::ClearScreen()
{
    Print("\033[2J\033[H");
}

void Screen::ClearBuffer()
{
    buffer.clear();
}

void Screen::Flush()
{
    printf("%s", buffer.c_str());
    fflush(stdout);
    buffer.clear();
}

void Screen::ClearScreenNow()
{
    printf("\033[2J\033[H"); // Clear screen and move cursor to home position
    fflush(stdout);
}

void Screen::HideCursorNow()
{
    printf("\033[?25l");
    fflush(stdout);
}

void Screen::ShowCursorNow()
{
    printf("\033[?25h");
    fflush(stdout);
}

void Screen::MoveCursor(int x, int y)
{
    buffer += ("\033[" + std::to_string(y) + ";" + std::to_string(x) + "H");
}

void Screen::SetColor(int color)
{
    color = color % 8;
    buffer += "\033[0;" + std::to_string(color) + "m";
}

void Screen::SetBackgroundColor(int bg_color)
{
    bg_color = bg_color % 8;
    buffer += "\033[4;" + std::to_string(bg_color) + "m";
}

void Screen::Print(const char *str)
{
    buffer += str;
}

void Screen::Print(int x, int y, const char *str)
{
    buffer += ("\033[" + std::to_string(y) + ";" + std::to_string(x) + "H");
    buffer += str;
}

void Screen::Print(int x, int y, const char *str, int color)
{
    buffer += ("\033[" + std::to_string(y) + ";" + std::to_string(x) + "H");
    buffer += "\033[0;" + std::to_string(color) + "m";
    buffer += str;
    buffer += "\033[0;" + std::to_string(this->color) + "m";
}

void Screen::Print(int x, int y, const char *str, int color, int bg_color)
{
    buffer += ("\033[" + std::to_string(y) + ";" + std::to_string(x) + "H");
    buffer += "\033[0;" + std::to_string(color) + "m";
    buffer += "\033[4;" + std::to_string(bg_color) + "m";
    buffer += str;
    buffer += "\033[0;" + std::to_string(this->color) + "m";
    buffer += "\033[4;" + std::to_string(this->bg_color) + "m";
}
