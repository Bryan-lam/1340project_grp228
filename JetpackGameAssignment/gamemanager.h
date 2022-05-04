#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#define SBWIDTH 20
#define SBHEIGHT 3

#include "player.h"
#include "pipe.h"
#include "mainmenu.h"

bool isTop(int gamescore) {
    ifstream fin;
    fin.open("Leaderboard.txt", ios::in);

    vector<int> leaderboard;
    int score = 0;
    int count = 0;
    while (fin >> score) {
        leaderboard.push_back(score);
        count++;
    }

    fin.close();

    sort(leaderboard.begin(), leaderboard.end(), greater<int>());
    printw("%d", leaderboard[0]);

    if (gamescore >= leaderboard[0]) {
        return true;
    }
    else {
        return false;
    }
}

void ShowEndScreen(WINDOW *mainBox, int gamescore, bool ishighscore) {
    WINDOW *endwin = derwin(mainBox, BOARD_ROWS - 1, BOARD_COLS - 1, 1, 1);

    string end_str1, end_str2;
    if (ishighscore) {
        end_str1 = "New high score! Your score was " + to_string(gamescore);
    }
    else {
        end_str1 = "You died! Your score was " + to_string(gamescore);
    }
    end_str2 = "Press \"X\" to return to menu.";

    int y, x;
    GetScreenCenter(mainBox, y, x);
    PrintCenter(endwin, end_str1, y-2);
    PrintCenter(endwin, end_str2, y);
    PaintBox(endwin);

    GetExitCommand(endwin);
    DeleteBox(endwin);
    return;
}

void EndGame(WINDOW *mainBox, WINDOW *playwin, WINDOW *scorewin, Player *player, Pipe *pipe, int gamescore) {
    delete player;
    delete pipe;

    DeleteBox(playwin);
    DeleteBox(scorewin);
    // endwin();

    ofstream fout;
    fout.open("Leaderboard.txt", ios::app);
    fout << to_string(gamescore) + "\n";
    fout.close();

    ShowEndScreen(mainBox, gamescore, isTop(gamescore));

    return;
}

void UpdateScore(WINDOW *scorewin, int gamescore) {
    string score_str = "Score: " + to_string(gamescore);
    ClearBox(scorewin);
    PrintCenter(scorewin, score_str, 1);
    PaintBox(scorewin);
    return;
}

void Game(WINDOW *mainBox, int &gs, int yLim, int xLim) {
    // Instantiate Sub Game Window
    WINDOW *playwin = derwin(mainBox, BOARD_ROWS - 1, BOARD_COLS - 1, 1, 1);
    box(playwin, 0, 0);    

    // Instantiate Player
    int gamescore = 0;
    Player *player = new Player(playwin, PLAYER_SPAWN_Y + 10, PLAYER_SPAWN_X, '#');
    Pipe *pipeOne = new Pipe(yLim, xLim, 5, 70, 1, playwin, BOARD_COLS, BOARD_ROWS);

    // Instantiate score board
    int yLoc, xLoc;
    GetScreenCenter(stdscr, yLoc, xLoc);
    yLoc = yLoc - (BOARD_ROWS / 2) - 2;
    xLoc = xLoc - (SBWIDTH / 2);
    WINDOW *scorewin = newwin(SBHEIGHT, SBWIDTH, yLoc, xLoc);
    // box(scorewin, 0, 0);

    string score_str = "Score: " + to_string(gamescore);
    PrintCenter(scorewin, score_str, 1);

    // Refresh play window and score window
    PaintBox(playwin);
    PaintBox(scorewin);

    // Game Loop
    bool game_over = false;
    while (!game_over) {
        if (player->collisionCheck()) game_over = true;
        if (player->getInput() == QUIT_KEY) game_over = true;
        gamescore += pipeOne->UpdatePipes();

        // Do a collision detection between player and pipe
        refresh();
        wrefresh(playwin);
        usleep((unsigned int)(1000000 / 60));

        // Update score window
        UpdateScore(scorewin, gamescore);
    }

    // End game
    EndGame(mainBox, playwin, scorewin, player, pipeOne, gamescore);
    gs = 0;

    return;
}

#endif