#ifndef TAGDIR_HPP
#define TAGDIR_HPP
#include <ncurses.h>
#include <map>

inline const std::string DATA_FILE_NAME = ".tagdir/tagdir_data";
inline const std::string SCRIPT_FILE_NAME = ".tagdir/tagdir_cd";
inline const std::string TEMP_FILE_NAME = ".tagdir/tagdir_temp";

extern std::string data_path;
extern std::map<std::string, std::string> tagdirPairs;

void init();
void update_tagdir(const char*, const char *);
void update_tagdir(const char*, const char *, const char *);
void tag_directory(const char *, const char *);
void delete_tag(const char *);
void write_command(const char *);
std::string get_directory(const char *);

void display_ui();
void print_items(WINDOW *, int, int, std::string &);
void print_centered_text(WINDOW *, int, std::string);
#endif
