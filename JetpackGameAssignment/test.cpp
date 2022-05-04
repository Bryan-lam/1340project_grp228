#include <curses.h>

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int main(void)
{
    initscr();

    cbreak();
    noecho();
    nodelay(stdscr, true);

    scrollok(stdscr, true);
    while (1) {
        if (kbhit()) {
            printw("Key pressed! It was: %d\n", getch());
        } else {
            napms(20);
        }
    }
}