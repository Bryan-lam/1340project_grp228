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
#include "format.h"

void ExitGame(WINDOW *mainBox, Game *game) {
    delete game;
    DeleteBox(mainBox);
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

    // Create Main Box
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int yLim = (yMax / 2) - (BOARD_ROWS / 2);
    int xLim = (xMax / 2) - (BOARD_COLS / 2);
    WINDOW *mainBox = newwin(BOARD_ROWS, BOARD_COLS, yLim, xLim);

    // Initiallize game manager, assign main box to manager
    Game *game = new Game(mainBox, yLim, xLim);

    bool quit = false;
    while (!quit) {
        switch (game->GetGameState()) {
            // 0: main menu
            case 0: {
                game->MainMenu();
                break;
            }

            // 1: game
            case 1: {
                game->PlayGame();
                break;
            }

            // 2: leaderboard
            case 2: {
                game->LeaderBoard();
                break;
            }

            // 3: quit game
            case 3: {
                quit = true;
                break;
            }

            // crash
            default:
                ExitGame(mainBox, game);
                break;
        }
    }

    ExitGame(mainBox, game);

    return 0;
}