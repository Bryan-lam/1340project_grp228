#ifndef MAINMENU_H
#define MAINMENU_H

#define CHOICES 3
#define UP_KEY 'w'
#define DOWN_KEY 's'

void DeleteBox(WINDOW *win) {
    werase(win);
    wrefresh(win);
    delwin(win);
    return;
}

void ClearBox(WINDOW *mainBox) {
    wclear(mainBox);
    return;
}

void PaintBox(WINDOW *mainBox)
{
    // refresh();
    wrefresh(mainBox);
    return;
}

void GetScreenLimit(WINDOW *win, int &yMax, int &xMax) {
    getmaxyx(win, yMax, xMax);
    return;
}

void GetScreenCenter(WINDOW *win, int &y, int &x) {
    int yMax, xMax;
    GetScreenLimit(win, yMax, xMax);
    y = yMax / 2;
    x = xMax / 2;
    return;
}

void PrintCenter(WINDOW *win, string s, int cy) {
    int h, w;
    GetScreenLimit(win, h, w);
    int cx = (w / 2) - (s.length() / 2);
    mvwprintw(win, cy, cx, s.c_str());
    return;
}

void GetExitCommand(WINDOW *win) {
    int c;
    while (c!=QUIT_KEY) {
        c = wgetch(win);
    }
    return;
}

void MainMenu(WINDOW *mainBox, int &gs)
{
    ClearBox(mainBox);

    //Initilize main menu options
    string title = "Jetpack Joyride";
    string instr1 = "Navigate with \"W\" & \"S\"";
    string instr2 = "Press ENTER to confirm choice";
    string choices[CHOICES] = {"Play", "Leaderboard", "Quit"};

    int cy, cx;
    GetScreenCenter(mainBox, cy, cx);
    // int cx = ((BOARD_COLS) / 2) - (title.length() / 2);
    // int cx_instructions = ((BOARD_COLS) / 2) - (instructions.length() / 2);

    PrintCenter(mainBox, title, cy-2);
    PrintCenter(mainBox, instr1, cy+CHOICES+4);
    PrintCenter(mainBox, instr2, cy+CHOICES+5);
    // PrintCenter( mainBox, instructions, cy + 2, BOARD_COLS);

    wrefresh(mainBox);

    int choice;
    int highlight = 1;

    while (1) {
        for (int i=1; i<=CHOICES; i++) {
            if (i == highlight) wattron(mainBox, A_REVERSE);
            PrintCenter(mainBox, choices[i-1], cy-1+i);
            wattroff(mainBox, A_REVERSE);
        }

        choice = wgetch(mainBox);

        switch(choice) {
            case UP__KEY:
                highlight--;
                break;
            case DOWN__KEY:
                highlight++;
                break;
            default:
                break;
        }

        if (highlight > CHOICES) highlight = CHOICES;
        else if (highlight < 1) highlight = 1;

        if (choice == 10) {
            gs = highlight;
            break;
        }
    }

    ClearBox(mainBox);
    // PaintBox(mainBox);

    return;
}

void LeaderBoard(WINDOW *mainBox, int &gs) {
    ClearBox(mainBox);

    // Initialize leaderboard
    string subtitle = "**Top 10 players**";
    string instruction = "Press \"X\" to return to main menu!";
    int cy = BOARD_ROWS/2 - 7;
    PrintCenter(mainBox, subtitle, cy);

    // Read and print input from Leaderboard.txt
    ifstream fin("Leaderboard.txt", ios::in);
    vector<int> leaderboard;
    int score = 0;
    int count = 0;

    while (fin >> score) {
        leaderboard.push_back(score);
        count++;
    }

    fin.close();

    sort(leaderboard.begin(), leaderboard.end(), greater<int>());

    if (count != 0) {
        int disp = (count < 10)? count : 10;
        for (int i=0; i<disp; i++) {
            string space = "      ";
            if (i==10) space.pop_back();
            if (leaderboard[i] > 9) space.pop_back();
            string line = "#" + to_string(i+1) + space + to_string(leaderboard[i]);
            PrintCenter(mainBox, line, cy+2+i);
        }
    }

    PrintCenter(mainBox, instruction, cy+13);

    PaintBox(mainBox);

    GetExitCommand(mainBox);

    gs = 0;

    return;
}

#endif