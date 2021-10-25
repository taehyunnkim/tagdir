// UI application for tagdir
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <string>
#include "TagDir.hpp"

using namespace std;

void display_ui() {
    WINDOW *menu_win;
    int width, height, startx, starty, side_padding;

    // initialize
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    
    side_padding = 2;
    width = COLS/1.5;
    height = 10;
    startx = (COLS - width) / 2;
    starty = (LINES - height) / 2;
    menu_win = newwin(height, width, starty, startx); // rows, cols, y, x
    box(menu_win, 0, 0);
    

    wattron(menu_win, A_BOLD);
    wattron(menu_win, COLOR_PAIR(1));
    mvwprintw(menu_win, 0, side_padding, "TAGDIR");
    wattroff(menu_win, A_BOLD);
    wattroff(menu_win, COLOR_PAIR(1));
    
    string instruction = "Press ENTER to navigate";
    mvwprintw(menu_win, 0, width - instruction.length() - side_padding, instruction.c_str());
    
    int selected_row = 0;
    int ch;
    string selected_tag = "";
    while (ch != KEY_EXIT) {
        print_items(menu_win, side_padding, selected_row, selected_tag);
        ch = getch();
        
        switch (ch) {
            case KEY_DOWN:
                if (selected_row < tagdirPairs.size()-1) selected_row++;
                continue;
            case KEY_UP:
                if (selected_row > 0) selected_row--; 
                continue;
            default:
                break;
        }
        
        break;

    }

    endwin();
    
    if (!selected_tag.empty()) write_command(selected_tag.c_str());
}

void print_items(WINDOW *win, int padding, int selected_item, string &selected_tag) {
    int start_row = padding;
    for(auto itr = tagdirPairs.begin(); itr != tagdirPairs.end(); itr++) {
        string item = itr->first + " -> " + itr->second;
        if (distance(tagdirPairs.begin(), itr) == selected_item) {
            wattron(win, A_REVERSE); 
            mvwprintw(win, start_row, padding, item.c_str());
            wattroff(win, A_REVERSE);
            selected_tag = itr->first;
        } else {
            mvwprintw(win, start_row, padding, item.c_str());
        }

        start_row++;
    }
    
    refresh();
    wrefresh(win);
}

void print_centered_text(WINDOW *win, int start_row, string text) {
    int win_center = win->_maxx / 2;
    int text_half_length = text.length() / 2;
    int adjusted = win_center - text_half_length;

    mvwprintw(win, start_row, 2, text.c_str());
}
