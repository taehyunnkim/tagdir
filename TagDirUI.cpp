// UI application for tagdir

#include <fstream>
#include <ncurses.h>
#include <string>
#include "TagDir.hpp"

using namespace std;

void display_ui() {
    initscr();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);


    ifstream ifstr;
    ifstr.open(data_path);
    char *line;

    int start_row = 10;
    while(ifstr >> line) {
        attron(A_BOLD);
        attron(COLOR_PAIR(1));
        print_centered(stdscr, start_row, line);
        attroff(A_BOLD);
        attroff(COLOR_PAIR(1));

        start_row++;
    }

    ifstr.close();

    refresh();
    getch();
    endwin();
}

void print_centered(WINDOW *win, int start_row, string text) {
    int win_center = win->_maxx / 2;
    int text_half_length = text.length() / 2;
    int adjusted = win_center - text_half_length;

    mvwprintw(win, start_row, adjusted, text.c_str());
}
