#ifndef PLAYER_H
#define PLAYER_H

#define BOOST 1
#define UP__KEY 'w'
#define DOWN__KEY 's'

const float GRAVITY = 0.05;
const float init_velocity = -0.5;

void chtostr(char ch, char *str)
{
    str[0] = ch;
    str[1] = '\0';
}

class Player
{
public:
    Player(WINDOW *win, int y, int x, char c);

    void mvup();
    void mvdown();
    void mvleft();
    void mvright();
    int getInput();
    void Display();
    int getPos();
    int collisionCheck();
    // int getScore();

private:
    int xPos, yPos;
    int yMax = 1;
    int xMax = 1;
    int yMin, xMin;
    char icon;
    WINDOW *curwin;
    int time_since_last_boost = 0;
    int ground_height;
    // int score = 0;
};

Player::Player(WINDOW *win, int y, int x, char c)
{
    this->curwin = win;
    yPos = y;
    xPos = x;
    getmaxyx(curwin, yMin, xMin);
    // keypad(curwin, true);
    icon = c;

    Display();
}

int Player::getInput()
{
    nodelay(curwin, true);

    // wrefresh(curwin);
    int c = wgetch(curwin);

    if (c == UP__KEY)
    {
        mvup();
    }
    else if (c == DOWN__KEY)
    {
        mvdown();
    }

    Display();

    return c;
}

int Player::collisionCheck()
{
    int playerch = mvwinch(curwin, yPos - 1, xPos + 3);

        // std::cout << playerch << std::endl;
    // if (playerch == '#') {
    //     std::cout << "Collided" << std::endl;
    // }
    return playerch == '*';

    // return false;
}

int Player::getPos()
{
    return yPos;
}

void Player::mvup()
{
    // mvwaddch(curwin, yPos, xPos, ' ');


    WINDOW *window = curwin;
    int height = yPos;
    int JETPACK_COL = 10;
    char c[2];

    if (GRAVITY * time_since_last_boost + init_velocity > 0)
    {

        chtostr(' ', c);
        mvwprintw(window, height - 1, JETPACK_COL - 1, "%s", c);

        chtostr(' ', c);
        // mvwprintw(window, height - 1, JETPACK_COL - 1, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL + 1, "%s", c);

        chtostr(' ', c);
        mvwprintw(window, height - 1, JETPACK_COL + 2, "%s", c);

        chtostr(' ', c);
        mvwprintw(window, height - 1, JETPACK_COL + 3, "%s", c);
    }

    // If going up, flap!
    else
    {

        chtostr(' ', c);
        mvwprintw(window, height - 1, JETPACK_COL - 1, "%s", c);

        chtostr(' ', c);
        // mvwprintw(window, height - 1, JETPACK_COL - 1, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL + 1, "%s", c);
        chtostr(' ', c);
        mvwprintw(window, height - 1, JETPACK_COL + 2, "%s", c);

        chtostr(' ', c);
        mvwprintw(window, height - 1, JETPACK_COL + 3, "%s", c);
    }



    yPos -= 1;
    if (yPos < yMax)
        yPos = yMax;

    time_since_last_boost = 0;
    ground_height = yPos;

    Display();

    return;
}

void Player::mvdown()
{
    // mvwaddch(curwin, yPos, xPos, ' ');
    WINDOW *window = curwin;
    int height = yPos;
    int JETPACK_COL = 10;
    char c[2];

    if (GRAVITY * time_since_last_boost + init_velocity > 0)
    {

        chtostr(' ', c);
        mvwprintw(window, height - 1, JETPACK_COL - 1, "%s", c);

        chtostr(' ', c);
        // mvwprintw(window, height - 1, JETPACK_COL - 1, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL + 1, "%s", c);

        chtostr(' ', c);
        mvwprintw(window, height - 1, JETPACK_COL + 2, "%s", c);

        chtostr(' ', c);
        mvwprintw(window, height - 1, JETPACK_COL + 3, "%s", c);
    }

    // If going up, flap!
    else
    {

        chtostr(' ', c);
        mvwprintw(window, height - 1, JETPACK_COL - 1, "%s", c);

        chtostr(' ', c);
        // mvwprintw(window, height - 1, JETPACK_COL - 1, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL + 1, "%s", c);
        chtostr(' ', c);
        mvwprintw(window, height - 1, JETPACK_COL + 2, "%s", c);

        chtostr(' ', c);
        mvwprintw(window, height - 1, JETPACK_COL + 3, "%s", c);
    }


    yPos++;

    // usleep(500);
    if (yPos > yMin - 2)
        yPos = yMin - 2;
    Display();

    return;
}

void Player::Display()
{
    // mvwaddch(curwin, yPos, xPos, icon);
    WINDOW *window = curwin;
    int height = yPos;
    int JETPACK_COL = 10;
    char c[2];

    if (GRAVITY * time_since_last_boost + init_velocity > 0)
    {

        chtostr('(', c);
        mvwprintw(window, height - 1, JETPACK_COL - 1, "%s", c);

        chtostr('-', c);
        // mvwprintw(window, height - 1, JETPACK_COL - 1, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL + 1, "%s", c);

        chtostr(')', c);
        mvwprintw(window, height - 1, JETPACK_COL + 2, "%s", c);

        chtostr(')', c);
        mvwprintw(window, height - 1, JETPACK_COL + 3, "%s", c);
    }

    // If going up, flap!
    else
    {

        chtostr('(', c);
        mvwprintw(window, height - 1, JETPACK_COL - 1, "%s", c);

        chtostr('-', c);
        // mvwprintw(window, height - 1, JETPACK_COL - 1, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL + 1, "%s", c);
        chtostr(')', c);
        mvwprintw(window, height - 1, JETPACK_COL + 2, "%s", c);

        chtostr(')', c);
        mvwprintw(window, height - 1, JETPACK_COL + 3, "%s", c);
    }

    int above_chr = mvwinch(curwin, yPos - 5, xPos + 3);

    // if (mvwinch(curwin, yPos + 10, xPos + 3) == '*' || mvwinch(curwin, yPos - 10, xPos + 3) == '*') {
    //     score++;
    // }

    // std::cout << score << std::endl;
    return;
}

// int Player::getScore() {
//     return this->score;
// }

#endif