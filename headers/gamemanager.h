#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#define SBWIDTH 20
#define SBHEIGHT 3

#include "player.h"
#include "pipe.h"
#include "format.h"

class Game
{
public:
    Game(WINDOW *mainBox, int yLim, int xLim);
    void ShowEndScreen(bool ishighscore);
    void EndGame();
    void UpdateScore();
    void MainMenu();
    void LeaderBoard();
    void PlayGame();
    int GetGameState();

private:
    WINDOW *mainBox;
    WINDOW *scorewin;
    WINDOW *playwin;
    WINDOW *endwin;

    Player *player;
    Pipe *pipeOne;

    int yLim, xLim;
    int yC, xC;
    int gamescore = 0;
    int gamestate = 0;

    bool isTop(int gamescore);
};

Game::Game(WINDOW *mainBox, int yLim, int xLim)
{
    // Initialize variables
    this->mainBox = mainBox;
    this->yLim = yLim;
    this->xLim = xLim;

    GetScreenCenter(mainBox, yC, xC);

    PaintBox(mainBox);
}

void Game::ShowEndScreen(bool ishighscore)
{
    // Create subwindow for death screen
    endwin = derwin(mainBox, BOARD_ROWS - 1, BOARD_COLS - 1, 1, 1);

    // Print death message
    string end_str1, end_str2;
    if (ishighscore)
    {
        end_str1 = "New high score! Your score was " + to_string(gamescore);
    }
    else
    {
        end_str1 = "You died! Your score was " + to_string(gamescore);
    }
    end_str2 = "Press \"X\" to return to menu.";

    PrintCenter(endwin, end_str1, yC - 2);
    PrintCenter(endwin, end_str2, yC);
    PaintBox(endwin);

    // Wait for exit command to close and delete subwindow
    GetExitCommand(endwin);
    DeleteBox(endwin);

    return;
}

void Game::EndGame()
{
    // Free memory from pointers
    delete player;
    delete pipeOne;

    // Close and delete subwindows
    DeleteBox(playwin);
    DeleteBox(scorewin);

    // Record game score
    ofstream fout;
    fout.open("Leaderboard.txt", ios::app);
    fout << to_string(gamescore) + "\n";
    fout.close();

    // Display death screen
    ShowEndScreen(isTop(gamescore));

    return;
}

void Game::UpdateScore()
{
    string score_str = "Score: " + to_string(gamescore);

    ClearBox(scorewin);

    PrintCenter(scorewin, score_str, 1);

    PaintBox(scorewin);

    return;
}

void Game::MainMenu()
{
    ClearBox(mainBox);

    // Initilize main menu options
    string title = "Jetpack Joyride";
    string instr1 = "Navigate with \"W\" & \"S\"";
    string instr2 = "Press ENTER to confirm choice";
    string choices[CHOICES] = {"Play", "Leaderboard", "Quit"};

    PrintCenter(mainBox, title, yC - 2);
    PrintCenter(mainBox, instr1, yC + CHOICES + 4);
    PrintCenter(mainBox, instr2, yC + CHOICES + 5);

    wrefresh(mainBox);

    int choice;
    int highlight = 1;

    // Loop to navigate main menu bar
    while (1)
    {
        for (int i = 1; i <= CHOICES; i++)
        {
            if (i == highlight)
                wattron(mainBox, A_REVERSE);
            PrintCenter(mainBox, choices[i - 1], yC - 1 + i);
            wattroff(mainBox, A_REVERSE);
        }

        choice = wgetch(mainBox);

        switch (choice)
        {
        case UP__KEY:
            highlight--;
            break;
        case DOWN__KEY:
            highlight++;
            break;
        default:
            break;
        }

        if (highlight > CHOICES)
            highlight = CHOICES;
        else if (highlight < 1)
            highlight = 1;

        if (choice == 10)
        {
            gamestate = highlight;
            break;
        }
    }

    // Refresh game screen after quitting menu
    ClearBox(mainBox);

    return;
}

void Game::LeaderBoard()
{
    // Initialize leaderboard
    string subtitle = "**Top 10 players**";
    string instruction = "Press \"X\" to return to main menu!";
    int cy = BOARD_ROWS / 2 - 7;
    PrintCenter(mainBox, subtitle, cy);

    // Read and print input from Leaderboard.txt
    ifstream fin("Leaderboard.txt", ios::in);
    vector<int> leaderboard;
    int score = 0;
    int count = 0;

    while (fin >> score)
    {
        leaderboard.push_back(score);
        count++;
    }

    fin.close();

    // Sort leaderboard in descending order of points
    sort(leaderboard.begin(), leaderboard.end(), greater<int>());

    if (count != 0)
    {
        int disp = (count < 10) ? count : 10;
        for (int i = 0; i < disp; i++)
        {
            string space = "      ";
            if (i == 10)
                space.pop_back();
            if (leaderboard[i] > 9)
                space.pop_back();
            string line = "#" + to_string(i + 1) + space + to_string(leaderboard[i]);
            PrintCenter(mainBox, line, cy + 2 + i);
        }
    }

    // Print leader board
    PrintCenter(mainBox, instruction, cy + 13);
    PaintBox(mainBox);

    // Wait for exit command
    GetExitCommand(mainBox);

    // Return game state
    gamestate = 0;

    return;
}

void Game::PlayGame()
{
    // Instantiate Sub Game Window
    playwin = derwin(mainBox, BOARD_ROWS - 1, BOARD_COLS - 1, 1, 1);
    box(playwin, 0, 0);

    // Instantiate Player
    gamescore = 0;
    player = new Player(playwin, PLAYER_SPAWN_Y + 10, PLAYER_SPAWN_X, '#');
    pipeOne = new Pipe(yLim, xLim, 5, 70, 1, playwin, BOARD_COLS, BOARD_ROWS);

    // Instantiate score board
    scorewin = newwin(SBHEIGHT, SBWIDTH, 0, 0);

    string score_str = "Score: " + to_string(gamescore);
    PrintCenter(scorewin, score_str, 1);

    // Refresh play window and score window
    PaintBox(playwin);
    PaintBox(scorewin);

    // Game Loop
    bool game_over = false;
    while (!game_over)
    {
        if (player->collisionCheck())
            game_over = true;
        if (player->getInput() == QUIT_KEY)
            game_over = true;
        gamescore += pipeOne->UpdatePipes();

        // Do a collision detection between player and pipe
        wrefresh(playwin);
        usleep((unsigned int)(1000000 / 60));

        // Update score window
        UpdateScore();
    }

    // End game
    EndGame();
    gamestate = 0;

    return;
}

int Game::GetGameState()
{
    return gamestate;
}

bool Game::isTop(int gamescore)
{
    // Determine if game score broke record
    ifstream fin;
    fin.open("./game_storage/Leaderboard.txt", ios::in);

    vector<int> leaderboard;
    int score = 0;
    int count = 0;
    while (fin >> score)
    {
        leaderboard.push_back(score);
        count++;
    }

    fin.close();

    sort(leaderboard.begin(), leaderboard.end(), greater<int>());

    if (gamescore >= leaderboard[0])
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif