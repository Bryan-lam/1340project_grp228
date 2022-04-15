#ifndef PLAYER_H
#define PLAYER_H

#define BOOST 1
#define GRAVITY 1
#define BOOST_KEY 'w'

class Player {
    public:
        Player(WINDOW * win, int y, int x, char c);

        void mvup();
        void mvdown();
        void mvleft();
        void mvright();
        int getInput();
        void Display();

    private:    
        int xPos, yPos;
        int yMax = 1;
        int xMax = 1;
        int yMin, xMin;
        char icon;
        WINDOW *curwin;

        bool kbhit();
};

Player::Player(WINDOW * win, int y, int x, char c) {
    this->curwin = win;
    yPos = y;
    xPos = x;
    getmaxyx(curwin, yMin, xMin);
    keypad(curwin, true);
    icon = c;
}

int Player::getInput() {
    int c = wgetch(curwin);

    if (c==BOOST_KEY) {
        mvup();
    }
    else {
        mvdown();
    }

    return c;
}

void Player::mvup() {
    mvwaddch(curwin, yPos, xPos, ' ');
    yPos--;
    if (yPos < yMax) yPos = yMax;
}

void Player::mvdown() {
    mvwaddch(curwin, yPos, xPos, ' ');
    yPos++;
    if (yPos > yMin-2) yPos = yMin-2;
}

void Player::mvleft() {
    mvwaddch(curwin, yPos, xPos, ' ');
    xPos--;
    if (xPos < xMax) xPos = xMax;
}

void Player::mvright() {
    mvwaddch(curwin, yPos, xPos, ' ');
    xPos++;
    if (xPos > xMin-2) xPos = xMin-2;
}

void Player::Display() {
    mvwaddch(curwin, yPos, xPos, icon);
}

bool Player::kbhit() {
    int c = getch();

    if (c != ERR) {
        ungetch(c);
        return true;
    }
    else {
        return false;
    }
}

#endif