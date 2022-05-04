#ifndef PIPE_H
#define PIPE_H

#define PIPE_X_GAP 2
// #define PIPE_Y_GAP 10
#define PIPE_WIDTH 2

#define PIPE_Y_GAP_MAX 8
#define PIPE_Y_GAP_MIN 4

#include <random>

int PIPE_Y_GAP = 5;





class Pipe
{
public:
    Pipe(int y_lowlim, int x_lowlim, int y, int x, int speed, WINDOW *curwin, int mw_width, int mw_height);

    void SetSpeed(int speed);
    void mvfwd();
    void InitPipes();
    void DrawPipes();
    void ClearPipes();
    void UpdatePipes();

private:
    int yPos, xPos;
    int y_upplim, x_lflim, y_lowlim, x_rtlim;
    int speed;
    bool passed = false;

    WINDOW *curwin;
    int mw_width;
    int mw_height;
    int x = 0;

    int v_shift = 0;

    bool OutOfBounds();
};

Pipe::Pipe(int y_upplim, int x_lflim, int y, int x, int speed, WINDOW *curwin, int mw_width, int mw_height)
{
    this->curwin = curwin;

    this->y_upplim = y_upplim + 1;
    this->x_lflim = x_lflim + 1;

    y_lowlim = y_upplim + 20 - 1; // make this global later!
    x_rtlim = x_lflim + 100 - 1;  // make this global later!

    this->yPos = y;
    this->xPos = x;

    this->mw_width = mw_width;
    this->mw_height = mw_height;

    this->speed = speed;

    InitPipes();
    DrawPipes();
}

void Pipe::SetSpeed(int speed)
{
    this->speed = speed;
    return;
}

void Pipe::mvfwd()
{
    xPos -= speed;

    if (xPos <= x_lflim)
    {
        passed = true;
    }

    return;
}

void Pipe::InitPipes()
{

    // upperwin = newwin(yPos - PIPE_Y_GAP / 2, PIPE_WIDTH, y_upplim, xPos - PIPE_WIDTH / 2);
    // lowerwin = newwin(y_lowlim - yPos - PIPE_Y_GAP / 2, PIPE_WIDTH, yPos + PIPE_Y_GAP / 2, xPos - PIPE_WIDTH / 2);
    return;
}

void Pipe::DrawPipes()
{

    // box(upperwin, '*', '*');
    // box(lowerwin, '*', '*');

    // wborder(upperwin, '*', '*', '*', '*', 0, 0, 0, 0);
    wborder(curwin, '|', '|', '-', '-', 0, 0, 0, 0);

    // int col = xPos - PIPE_WIDTH / 2;

    // int UPPER_HEIGHT = yPos - PIPE_Y_GAP / 2;
    // int LOWER_HEIGHT = y_lowlim - yPos - PIPE_Y_GAP / 2;

    // int UPPER_Y_START = y_upplim;
    // int BOTTOM_Y_START = yPos + PIPE_Y_GAP / 2;

    mvwvline(curwin, 1, mw_width - 3 - x + speed, ' ', mw_height - 2);

    int x_pos = mw_width - 3 - x;
    x += speed;

    if (x > mw_width)
    {
        x = 0;
    }

    int upper_start = 1;
    int upper_end = (mw_height - PIPE_Y_GAP) / 2;

    int lower_start = upper_end + PIPE_Y_GAP - 1;
    int lower_end = mw_height - 2;

       // mvwvline(curwin, upper_start, x_pos, '*', 10);
    mvwvline(curwin, upper_start, xPos, '*', upper_end - v_shift);
    mvwvline(curwin, lower_start - v_shift, xPos, '*', mw_height - lower_start + v_shift - 1);

    // mvwvline(curwin, lower_start, x_pos, '*', lower_end);
    // mvwvline(curwin, ((mw_height + (PIPE_Y_GAP / 2)) / 2) - 2, x_pos, '*', ((mw_height - 2) / 2));

    // mvwvline(curwin, col, 0, '*', 6);

    // mvwvline(lowerwin, 0, 0, '*', 6);

    return;
}

void Pipe::ClearPipes()
{
    // werase(curwin);
    // werase(lowerwin);
    // wrefresh(curwin);
    // wrefresh(lowerwin);
    // delwin(curwin);
    // delwin(lowerwin);

    return;
}

void Pipe::UpdatePipes()
{
    ClearPipes();

    mvfwd();

    InitPipes();

    if (OutOfBounds())
    {
        // Reposition the pipe at the end of the board
        xPos = x_rtlim - PIPE_WIDTH / 2;

        // Change pipe gap
        // Generate random number between PIPE_Y_GAP_MAX and PIPE_Y_GAP_MIN
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(PIPE_Y_GAP_MIN, PIPE_Y_GAP_MAX);
        PIPE_Y_GAP = dis(gen);

        std::random_device s_rd;
        std::mt19937 s_gen(rd());
        std::uniform_int_distribution<> s_dis(-5, 5);
        v_shift = s_dis(s_gen);
    }
    else
    {
        DrawPipes();
    }

    return;
}

bool Pipe::OutOfBounds()
{
    if (xPos <= 0 || xPos >= x_rtlim - PIPE_WIDTH / 2)
    {

        return true;
    }
    else
    {

        return false;
    }
}

#endif