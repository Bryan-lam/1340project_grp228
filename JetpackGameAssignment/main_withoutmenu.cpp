#include <ncurses.h>
// #include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "player.h"
#include "pipe.h"
#include "collision.h"

using namespace std;

#define BOARD_DIM 20
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 5
#define PLAYER_SPAWN_Y 5
#define PLAYER_SPAWN_X 5
#define QUIT_KEY 'x'

int GAME_SCORE = 0;

int main(int argc, char **argv)
{
    bool game_over = false;

    setlocale(LC_ALL, "");

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

    Player *player = new Player(playwin, PLAYER_SPAWN_Y + 10, PLAYER_SPAWN_X, '#', GAME_SCORE);
    Pipe *pipeOne = new Pipe(ylim, xlim, 5, 70, 1, playwin, BOARD_COLS, BOARD_ROWS);

    while (!game_over)
    {
        if (player->collisionCheck())
        {

            game_over = true;
            endwin();
        }   

        if (player->getInput() == QUIT_KEY)
            game_over = true;
        pipeOne->UpdatePipes();
        // wrefresh(playwin);
        // wtimeout(playwin, 30);
        // FPS Delay

        // Do a collision detection between player and pipe

        refresh();

        wrefresh(playwin);
        // werase(playwin);

        usleep((unsigned int)(1000000 / 60));
    }

    endwin();

    return 0;
}