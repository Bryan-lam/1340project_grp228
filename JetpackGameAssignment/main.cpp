#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "player.h"
using namespace std;

#define BOARD_DIM 17
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2.5
#define QUIT_KEY 'x'

int main(int argc, char **argv) {
    initscr();
    noecho();
    cbreak();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW *playwin = newwin(BOARD_ROWS, BOARD_COLS, (yMax/2) - (BOARD_ROWS/2), (xMax/2) - (BOARD_COLS/2));
    box(playwin, 0, 0);
    refresh();
    wrefresh(playwin);

    Player *p = new Player(playwin, 3, 3, '#');

    while (p->getInput() != QUIT_KEY) {
        p->Display();
        wrefresh(playwin);
        wtimeout(playwin, 50);
    }

    getch();
    endwin();
    
    return 0;
}