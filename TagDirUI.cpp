// UI application for tagdir

#include <ncurses.h>

void display_ui() {
    initscr();
    printw("UI Application for tagdir");
    refresh();
    getch();
    endwin();
}
