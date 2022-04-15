// Libraries
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Definitions
#define BOARD_DIM 17
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 5
#define QUIT_KEY 'x'

// Custom Header File Import
#include "player.h"
#include "mainmenu.h"

int main(int argc, char **argv)
{
    // Initialize NCurses
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // Create Main Box
    WINDOW *mainBox = newwin(BOARD_ROWS, BOARD_COLS, (yMax / 2) - (BOARD_ROWS / 2), (xMax / 2) - (BOARD_COLS / 2));

    PaintBox(mainBox);
    //----------------

    // Paint Main Menu
    MainMenu(mainBox);
    //----------------

    // Create Sub Game Window
    WINDOW *playwin = derwin(mainBox, BOARD_ROWS - 1, BOARD_COLS - 1, 1, 1);

    box(playwin, 0, 0);
    refresh();
    wrefresh(playwin);

    // Instantiate Player
    Player *p = new Player(playwin, 3, 3, '#');

    // Game Loop
    while (p->getInput() != QUIT_KEY)
    {
        p->Display();
        wrefresh(playwin);
        wtimeout(playwin, 50);
    }

    getch();
    endwin();

    return 0;
}