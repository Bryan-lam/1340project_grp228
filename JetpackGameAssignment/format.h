#ifndef FORMAT_H
#define FORMAT_H

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

#endif