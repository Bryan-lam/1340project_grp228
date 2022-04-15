#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "player.h"
using namespace std;

#define BOARD_DIM 17
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 5
#define QUIT_KEY 'x'

void PaintBox(WINDOW *mainBox)
{
    refresh();

    // box(mainBox, 0, 0);

    wrefresh(mainBox);
}

void MainMenu(WINDOW *mainBox)
{
    string title = "Jetpack Joyride";
    string instructions = "Press any key to start";

    int cy = ((BOARD_ROWS) / 2) - 1;
    int cx = ((BOARD_COLS) / 2) - (title.length() / 2);
    int cx_instructions = ((BOARD_COLS) / 2) - (instructions.length() / 2);

    mvwprintw(mainBox, cy, cx, "Jetpack Joyride");
    mvwprintw(mainBox, cy + 2, cx_instructions, "Press any key to start");

    wrefresh(mainBox);

    getch();

    wclear(mainBox);

    PaintBox(mainBox);
    wrefresh(mainBox);
}





void SetupNC()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    // timeout(0);
}


int main(int argc, char **argv)
{
    SetupNC();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // Create Game Box
    WINDOW *mainBox = newwin(BOARD_ROWS, BOARD_COLS, (yMax / 2) - (BOARD_ROWS / 2), (xMax / 2) - (BOARD_COLS / 2));

    PaintBox(mainBox);
    //----------------

    // Paint a Main Menu
    MainMenu(mainBox);
    //----------------

    // Create sub window
    WINDOW *playwin = derwin(mainBox, BOARD_ROWS - 1, BOARD_COLS - 1, 1, 1);

    box(playwin, 0, 0);
    refresh();
    wrefresh(playwin);

    Player *p = new Player(playwin, 3, 3, '#');

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