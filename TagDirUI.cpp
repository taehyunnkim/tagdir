// UI application for tagdir
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <string>
#include "TagDir.hpp"

using namespace std;

void display_ui() {
    WINDOW *menu_win, *menu_content;
    int width, height, startx, starty, padding;
    
    // initialize
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    refresh();

    padding = 2;
    width = COLS/2;
    height = LINES/3; 
    startx = (COLS - width) / 2;
    starty = (LINES - height) / 2;
   
    menu_win = newwin(height, width, starty, startx);
    box(menu_win, 0, 0);

    // TITLE
    wattron(menu_win, A_BOLD | COLOR_PAIR(1));
    mvwaddstr(menu_win, 0, padding, "TAGDIR");
    wattroff(menu_win, A_BOLD | COLOR_PAIR(1));
    
    // MENU INSTRUCTIONS
    string instruction = "Press ENTER to navigate";
    mvwaddstr(menu_win, 0, width-instruction.length()-padding, instruction.c_str());
    instruction = "Press SPACE to exit";
    mvwaddstr(menu_win, height-1, width-instruction.length()-padding, instruction.c_str()); 
    
    wrefresh(menu_win);

    // MENU CONTENT
    menu_content = newwin(height-2*padding, width-2*padding, starty+padding, startx+padding); 
    keypad(menu_content, true);
  

    int selected_item = 0;
    int ch;
    string selected_tag = "";
    int min = 0;
    int max = height - 2*padding;
    while (ch != ' ') {
        print_items(menu_content, min, max, selected_item, selected_tag);
        ch = wgetch(menu_content); // implicit refresh
        
        switch (ch) {
            case KEY_DOWN:
                selected_item++;
                if (selected_item == tagdir_pairs.size()) { 
                    selected_item = 0;
                    min = 0;
                    max = height - 2*padding;
                }
                
                break;
            case KEY_UP:
                selected_item--;
                if (selected_item == -1) { 
                    selected_item = tagdir_pairs.size()-1; 
                    min = tagdir_pairs.size()-max-1;
                    max = tagdir_pairs.size()-1;
                }

                break;
            case 10: // ENTER
                ch = ' ';
                write_command(selected_tag.c_str());
                break;
            case ' ':
                selected_tag = "";
                break;
        }    
        
        wclear(menu_content);
    }
 
    delwin(menu_win);
    delwin(menu_content);
    endwin();
    
    if (!selected_tag.empty()) write_command(selected_tag.c_str());
}

void print_items(WINDOW *win, int &min, int &max, int selected_item, string &selected_tag) {
    int start_row = 0;
    
    if (selected_item > max-1) {
        min++;
        max++;
    } else if (selected_item < min) {
        min--;
        max--;
    }
     
    for(auto itr = tagdir_pairs.begin(); itr != tagdir_pairs.end() && start_row < max-min; itr++) {
        int index = distance(tagdir_pairs.begin(), itr);
    
        if (index < min) {
            continue;
        }

        string item = itr->first + " > " + itr->second;
        if (index == selected_item) {
            wattron(win, COLOR_PAIR(1) | A_BOLD); 
            mvwprintw(win, start_row, 0, item.c_str());
            wattroff(win, COLOR_PAIR(1) | A_BOLD); 
            selected_tag = itr->first;
        } else {
            mvwprintw(win, start_row, 0, item.c_str());
        }

        start_row++;
    }       
}

void print_centered_text(WINDOW *win, int start_row, string text) {
    int win_center = win->_maxx / 2;
    int text_half_length = text.length() / 2;
    int adjusted = win_center - text_half_length;

    mvwprintw(win, start_row, 2, text.c_str());
}
