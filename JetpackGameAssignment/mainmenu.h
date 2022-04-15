void PaintBox(WINDOW *mainBox)
{
    refresh();

    wrefresh(mainBox);
}

void MainMenu(WINDOW *mainBox)
{
    string title = "Jetpack Joyride";
    string instructions = "Press any key to start";

    int cy = ((BOARD_ROWS) / 2) - 1;
    int cx = ((BOARD_COLS) / 2) - (title.length() / 2);
    int cx_instructions = ((BOARD_COLS) / 2) - (instructions.length() / 2);

    mvwprintw(mainBox, cy, cx, "Jetpack Joyride");
    mvwprintw(mainBox, cy + 2, cx_instructions, "Press any key to start");

    wrefresh(mainBox);

    getch();

    wclear(mainBox);

    PaintBox(mainBox);
    wrefresh(mainBox);
}




