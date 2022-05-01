#ifndef PIPE_H
#define PIPE_H

#define PIPE_X_GAP 17
// #define PIPE_Y_GAP 10
#define PIPE_WIDTH 2

#define PIPE_Y_GAP_MAX 15
#define PIPE_Y_GAP_MIN 12

#include <random>

int PIPE_Y_GAP = 10;

class Pipe
{
public:
    Pipe(int y_lowlim, int x_lowlim, int y, int x, int speed);

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
    WINDOW *upperwin;
    WINDOW *lowerwin;

    bool OutOfBounds();
};

Pipe::Pipe(int y_upplim, int x_lflim, int y, int x, int speed)
{
    this->y_upplim = y_upplim + 1;
    this->x_lflim = x_lflim + 1;
    y_lowlim = y_upplim + 20 - 1; // make this global later!
    x_rtlim = x_lflim + 100 - 1;  // make this global later!

    this->yPos = y;
    this->xPos = x;

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

    upperwin = newwin(yPos - PIPE_Y_GAP / 2, PIPE_WIDTH, y_upplim, xPos - PIPE_WIDTH / 2);
    lowerwin = newwin(y_lowlim - yPos - PIPE_Y_GAP / 2, PIPE_WIDTH, yPos + PIPE_Y_GAP / 2, xPos - PIPE_WIDTH / 2);
    return;
}

void Pipe::DrawPipes()
{
    box(upperwin, 0, 0);
    box(lowerwin, 0, 0);

    wrefresh(upperwin);
    wrefresh(lowerwin);

    return;
}

void Pipe::ClearPipes()
{
    werase(upperwin);
    werase(lowerwin);
    wrefresh(upperwin);
    wrefresh(lowerwin);
    delwin(upperwin);
    delwin(lowerwin);
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

    }
    else
    {
        DrawPipes();
    }

    return;
}

bool Pipe::OutOfBounds()
{
    if (xPos <= x_lflim  + PIPE_WIDTH / 2 || xPos >= x_rtlim - PIPE_WIDTH / 2)
    {

        return true;
    }
    else
    {

        return false;
    }
}

#endif