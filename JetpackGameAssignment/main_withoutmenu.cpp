#include <ncurses.h>
// #include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "player.h"
#include "pipe.h"

using namespace std;

#define BOARD_DIM 20
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 5
#define PLAYER_SPAWN_Y 5
#define PLAYER_SPAWN_X 5
#define QUIT_KEY 'x'

int main(int argc, char **argv)
{
    bool game_over = false;


    

    initscr();
    noecho();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    
    cbreak();
    nodelay(stdscr, true);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int ylim = (yMax / 2) - (BOARD_ROWS / 2);
    int xlim = (xMax / 2) - (BOARD_COLS / 2);
    WINDOW *playwin = newwin(BOARD_ROWS, BOARD_COLS, ylim, xlim);
    box(playwin, 0, 0);

    refresh();
    wrefresh(playwin);

    Player *player = new Player(playwin, PLAYER_SPAWN_Y, PLAYER_SPAWN_X, '#');
    Pipe *pipe = new Pipe(ylim, xlim, 15, 70, 1);

    while (!game_over)
    {
        if (player->getInput() == QUIT_KEY)
            game_over = true;
        pipe->UpdatePipes();
        wrefresh(playwin);
        // wtimeout(playwin, 30);
        // FPS Delay
        usleep((unsigned int)(1000000 / 60));
    }

    endwin();

    return 0;
}