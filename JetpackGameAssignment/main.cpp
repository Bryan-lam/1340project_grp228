// Libraries
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Definitions
#define BOARD_DIM 17
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 5
#define PLAYER_SPAWN_Y 5
#define PLAYER_SPAWN_X 5
#define QUIT_KEY 'x'

// Custom Header File Import
#include "pipe.h"
#include "player.h"
#include "gamemanager.h"
#include "mainmenu.h"

void ExitGame() {
    echo();
    endwin();
    return;
}

void StartGame() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    cbreak();
    nodelay(stdscr, true);
    return;
}


int main(int argc, char **argv)
{
    // Initialize NCurses
    StartGame();

    // Initialize game state
    /*
        0: main menu
        1: game
        2: leader board
        3: quit game
    */
    int gamestate = 0;

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int yLim = (yMax / 2) - (BOARD_ROWS / 2);
    int xLim = (xMax / 2) - (BOARD_COLS / 2);

    // Create Main Box
    WINDOW *mainBox = newwin(BOARD_ROWS, BOARD_COLS, yLim, xLim);

    PaintBox(mainBox);
    //----------------

    // // Paint Main Menu
    // MainMenu(mainBox, gamestate);
    // //----------------
    bool quit = false;
    while (!quit) {
        switch (gamestate) {
            // 0: main menu
            case 0: {
                MainMenu(mainBox, gamestate);
                break;
            }

            // 1: game
            case 1: {
                Game(mainBox, gamestate, yLim, xLim);
                break;
            }

            // 2: leaderboard
            case 2: {
                LeaderBoard(mainBox, gamestate);
                break;
            }

            // 3: quit game
            case 3: {
                quit = true;
                break;
            }

            // crash
            default:
                ExitGame();
                break;
        }
    }

    ExitGame();

    return 0;
}