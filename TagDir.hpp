#ifndef TAGDIR_HPP
#define TAGDIR_HPP

inline const std::string DATA_FILE_NAME = ".tagdir";
extern std::string data_path;

void init();
void display_ui();
void tag_directory(const char *tag, const char *dir);
void print_directory(const char *tag);
std::tuple<int, std::string> get_directory_with_tag(const char *tag);
std::string get_directory(const char *arg);

#endif
