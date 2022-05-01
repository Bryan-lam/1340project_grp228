#include <iostream>
#include <curses.h>
#include <time.h>

using namespace std;

// Globals
int HEIGHT = 20;
int WIDTH = 100;
int BOX_ORIGIN_X = 5;
int BOX_ORIGIN_Y = 5;

bool GAME_ON = true;
bool RESTART = true;

int FPS = 25;
int CURRENT_FRAME = 0;
int JETPACK_COL = 10;

// Constants
const float init_velocity = -0.5;
const float GRAVITY = 0.05;

typedef struct JETPACK_CONSTRUCTOR
{
    int ground_height;      // Height from the ground
    int wall_distance;      // Distance from the wall on left
    int time_since_last_up; // Time since last up arrow press
} JETPACK_CONSTRUCTOR;

void SetupNC()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    // timeout(0);
}

void chtostr(char ch, char *str)
{
    str[0] = ch;
    str[1] = '\0';
}

int get_jetpack_position(JETPACK_CONSTRUCTOR j)
{
    return j.ground_height + init_velocity * j.time_since_last_up + 0.5 * GRAVITY * j.time_since_last_up * j.time_since_last_up;
}

void PaintBox(WINDOW *mainBox)
{
    refresh();

    box(mainBox, 0, 0);

    wrefresh(mainBox);
}

void MainMenu(WINDOW *mainBox)
{
    string title = "Jetpack Joyride";
    string instructions = "Press any key to start";

    int cy = ((HEIGHT) / 2) - 1;
    int cx = ((WIDTH) / 2) - (title.length() / 2);
    int cx_instructions = ((WIDTH) / 2) - (instructions.length() / 2);

    mvwprintw(mainBox, cy, cx, "Jetpack Joyride");
    mvwprintw(mainBox, cy + 2, cx_instructions, "Press any key to start");

    wrefresh(mainBox);

    getch();

    wclear(mainBox);

    PaintBox(mainBox);
    wrefresh(mainBox);
}

int PaintJetpack(WINDOW *window, JETPACK_CONSTRUCTOR jetpack)
{
    char c[2];
    int height = get_jetpack_position(jetpack);

    // Upon hitting ceiling
    if (height <= 0)
    {
        // do something
    }
    // Upon hitting floor
    else if (height >= HEIGHT - 1)
    {
        // do something
    }

    // Logic for hitting pipes

    // mvwprintw(subBox, 10, 10, "Jetpack position: %d", height);

    // If going down, don't flap
    if (GRAVITY * jetpack.time_since_last_up + init_velocity > 0)
    {

        chtostr('(', c);
        mvwprintw(window, height - 2, JETPACK_COL - 1, "%s", c);

        chtostr(')', c);
        mvwprintw(window, height - 2, JETPACK_COL + 1, "%s", c);

        chtostr('o', c);
        mvwprintw(window, height - 2, JETPACK_COL, "%s", c);

        chtostr('/', c);
        mvwprintw(window, height - 1, JETPACK_COL - 3, "%s", c);

        chtostr('-', c);
        mvwprintw(window, height - 1, JETPACK_COL - 2, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL - 1, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL + 1, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL + 2, "%s", c);

        chtostr('\\', c);
        mvwprintw(window, height - 1, JETPACK_COL + 3, "%s", c);

        chtostr('/', c);
        mvwprintw(window, height, JETPACK_COL + 3, "%s", c);

        chtostr('-', c);
        mvwprintw(window, height, JETPACK_COL - 2, "%s", c);
        mvwprintw(window, height, JETPACK_COL - 1, "%s", c);
        mvwprintw(window, height, JETPACK_COL, "%s", c);
        mvwprintw(window, height, JETPACK_COL + 1, "%s", c);
        mvwprintw(window, height, JETPACK_COL + 2, "%s", c);

        chtostr('\\', c);
        mvwprintw(window, height, JETPACK_COL - 3, "%s", c);
    }

    // If going up, flap!
    else
    {
        chtostr('(', c);
        mvwprintw(window, height - 2, JETPACK_COL - 1, "%s", c);

        chtostr(')', c);
        mvwprintw(window, height - 2, JETPACK_COL + 1, "%s", c);

        chtostr('o', c);
        mvwprintw(window, height - 2, JETPACK_COL, "%s", c);

        chtostr('/', c);
        mvwprintw(window, height - 1, JETPACK_COL - 3, "%s", c);

        chtostr('-', c);
        mvwprintw(window, height - 1, JETPACK_COL - 2, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL - 1, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL + 1, "%s", c);
        mvwprintw(window, height - 1, JETPACK_COL + 2, "%s", c);

        chtostr('\\', c);
        mvwprintw(window, height - 1, JETPACK_COL + 3, "%s", c);

        chtostr('/', c);
        mvwprintw(window, height, JETPACK_COL + 3, "%s", c);

        chtostr('-', c);
        mvwprintw(window, height, JETPACK_COL - 2, "%s", c);
        mvwprintw(window, height, JETPACK_COL - 1, "%s", c);
        mvwprintw(window, height, JETPACK_COL, "%s", c);
        mvwprintw(window, height, JETPACK_COL + 1, "%s", c);
        mvwprintw(window, height, JETPACK_COL + 2, "%s", c);

        chtostr('\\', c);
        mvwprintw(window, height, JETPACK_COL - 3, "%s", c);

        chtostr('|', c);
        mvwprintw(window, height + 1, JETPACK_COL - 1, "%s", c);
        mvwprintw(window, height + 1, JETPACK_COL - 0, "%s", c);
        mvwprintw(window, height + 1, JETPACK_COL + 1, "%s", c);
    }

    return 0;
}

int main()
{
    int key_pressed = -1;

    // Initialize Game Objects
    JETPACK_CONSTRUCTOR jetpack;

    // Setup Ncurses
    SetupNC();

    // Create Game Box
    WINDOW *mainBox = newwin(HEIGHT, WIDTH, BOX_ORIGIN_Y, BOX_ORIGIN_X);

    PaintBox(mainBox);
    //----------------

    // Paint a Main Menu
    MainMenu(mainBox);
    //----------------

    // Create sub window
    WINDOW *subBox = derwin(mainBox, HEIGHT - 2, WIDTH - 2, 1, 1);

    // Game Loop
    while (GAME_ON)
    {
        // In ase game restarts, clear the screen
        if (RESTART)
        {
            timeout(0);

            // cout << "Restarted" << endl;
            // Paint a Main Menu
            // MainMenu(mainBox);
            //----------------

            // Initlialize the jetpack
            jetpack.ground_height = HEIGHT / 2;
            jetpack.wall_distance = WIDTH / 6;
            jetpack.time_since_last_up = 0;

            RESTART = false;
        }

        // FPS Delay
        usleep((unsigned int)(1000000 / FPS));

        // Clear the screen
        werase(subBox);

        // Get key input
        key_pressed = -1;
        key_pressed = getch();

        mvwprintw(subBox, 17, 0, "(%d, %d)", jetpack.ground_height, jetpack.wall_distance);
        // mvwprintw(subBox, jetpack.ground_height, jetpack.wall_distance, "X");

        switch (key_pressed)
        {

        case 'q':
            endwin();
            exit(0);
            break;
        case KEY_UP:
            // mvwprintw(subBox, 0, 0, "Key Up");
            // jetpack.ground_height = jetpack.ground_height - 1;
            cbreak();

            jetpack.ground_height = get_jetpack_position(jetpack);
            jetpack.time_since_last_up = 0;
            break;

        case KEY_DOWN:
            // mvwprintw(subBox, 0, 0, "Key Down");
            jetpack.ground_height = jetpack.ground_height + 1;
            break;

        case KEY_LEFT:
            // mvwprintw(subBox, 0, 0, "Key Left");
            jetpack.wall_distance = jetpack.wall_distance - 1;
            JETPACK_COL -= 1;

            break;

        case KEY_RIGHT:
            // mvwprintw(subBox, 0, 0, "Key Right");
            jetpack.wall_distance = jetpack.wall_distance + 1;
            JETPACK_COL += 1;
            break;

        default:
            jetpack.time_since_last_up++;
        }

        // Draw the jetpack
        // mvwprintw(subBox, HEIGHT - 1, 0, jetpac);
        // Print the jetpack location on bottom left of sub box
        // mvwprintw(subBox, jetpack.ground_height, jetpack.wall_distance, "X");

        if (PaintJetpack(subBox, jetpack))
        {
            RESTART = true;
            continue; // ...then restart the game.
        }
        // MvWAddStr(subBox, 0, 3, "Sub-window 1");
        wrefresh(subBox);
        CURRENT_FRAME++;
        // PaintBox(mainBox);
    }

    // Wait for input
    getch();

    endwin();

    return 0;
}