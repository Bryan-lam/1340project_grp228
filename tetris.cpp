#include <iostream>
#include <curses.h>

using namespace std;

// Game Objects
wstring jetPack[7];

// Background Grid
int Height = 20;
int Width = 100;
unsigned char *grid = nullptr;

// Terminal Size
int sHeight = 40;
int sWidth = 120;

int Rotate(int x, int y, int r)
{
    switch (r % 4)
    {
    case 0:
        return y * 4 + x;
    case 1:
        return 12 + y - (x * 4);
    case 2:
        return 15 - (y - 4) - x;
    case 3:
        return 3 - y + (x * 4);
    default:
        return 50;
    }
}

int main()
{
    // Create asset
    jetPack[0].append(L"```...");
    jetPack[0].append(L"XXXXXX");

    // Initialize the grid
    grid = new unsigned char[Height * Width]; // Stored as a string
    for (int x = 0; x < Width; x++)
    {
        for (int y = 0; y < Height; y++)
        {
            // Set top boundary to -
            if (y == 0 || y == Height - 1)
            {
                grid[y * Width + x] = '-';
            }
            // Set left and right boundaries to |
            else if (x == 0 || x == Width - 1)
            {
                grid[y * Width + x] = '|';
            }
            else
            {
                grid[y * Width + x] = '0';
            }
        }
    }

    // Create a screen buffer
    wchar_t *screen = new wchar_t[Height * Width];
    for (int i = 0; i < Height * Width; i++)
    {
        screen[i] = L' ';
    }


    // Set up the memory and clear the screen
    initscr();

    getch();

    // deallocate memory and end ncurses
    endwin();

    return 0;
}