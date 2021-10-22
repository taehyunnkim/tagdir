#ifndef TAGDIR_HPP
#define TAGDIR_HPP
#include <ncurses.h>

inline const std::string DATA_FILE_NAME = ".tagdir/tagdir_data";
inline const std::string SCRIPT_FILE_NAME = ".tagdir/tagdir_cd";
inline const std::string TEMP_FILE_NAME = ".tagdir/tagdir_temp";
extern std::string data_path;

void init();
void update_tagdir(const char*, const char *);
void update_tagdir(const char*, const char *, const char *);
void tag_directory(const char *, const char *);
void delete_tag(const char *);
void print_directory(const char *);
std::tuple<bool, std::string> get_directory_with_tag(const char *);
std::string get_directory(const char *);

void display_ui();
void print_centered(WINDOW *, int, std::string);
#endif
