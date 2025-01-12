#include <string>

class Screen
{
public:
    Screen();
    ~Screen();

    void Start();
    void End();
    void ClearScreen();
    void ClearBuffer();
    void Flush();

    void ClearScreenNow();
    void HideCursorNow();
    void ShowCursorNow();

    void MoveCursor(int x, int y);
    void SetColor(int color);
    void SetBackgroundColor(int bg_color);

    void Print(const char *str);
    void Print(int x, int y, const char *str);
    void Print(int x, int y, const char *str, int color);
    void Print(int x, int y, const char *str, int color, int bg_color);

    /*
        void DrawLine(int x2, int y2);
        void DrawLine(int x1, int y1, int x2, int y2);
        void DrawLine(int x1, int y1, int x2, int y2, int color);
        void DrawLine(int x1, int y1, int x2, int y2, int color, int bg_color);

        void DrawRect(int x1, int y1, int x2, int y2);
        void DrawRect(int x1, int y1, int x2, int y2, int color);
        void DrawRect(int x1, int y1, int x2, int y2, int color, int bg_color);

        void DrawCircle(int x, int y, int radius);
        void DrawCircle(int x, int y, int radius, int color);
        void DrawCircle(int x, int y, int radius, int color, int bg_color);

        void DrawPixel();
        void DrawPixel(int x, int y);
        void DrawPixel(int x, int y, int color);
        void DrawPixel(int x, int y, int color, int bg_color);

        void DrawText(const char *str);
        void DrawText(int x, int y, const char *str);
        void DrawText(int x, int y, const char *str, int color);
        void DrawText(int x, int y, const char *str, int color, int bg_color);

        void DrawImage(const char *filename);
        void DrawImage(int x, int y, const char *filename);
        void DrawImage(int x, int y, const char *filename, int color);
        void DrawImage(int x, int y, const char *filename, int color, int bg_color);
    */
private:
    int x;
    int y;
    int color;
    int bg_color;

    std::string buffer;
};