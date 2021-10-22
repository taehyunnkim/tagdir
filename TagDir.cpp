#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>
#include "TagDir.hpp"

using namespace std;

string data_path = "";

int main(int argc, char *argv[]) {
    try {
        init();

        switch(argc) {
            case 1:
                display_ui();
                break;
            case 2:
                print_directory(argv[1]);
                break;
            case 3:
                tag_directory(argv[1], argv[2]);
                break;
            default:
                throw invalid_argument("supplied too many arguments");
        } 
    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }

    return 0;
}

void init() {
    const char *home = getenv("HOME");
    if (home) {
        ostringstream oss;
        oss << home << "/" << DATA_FILE_NAME;
        data_path = oss.str();

        const filesystem::path p(data_path);
        if (!filesystem::exists(p)) ofstream { oss.str() };
    } else {
        throw runtime_error("the home directory is not defined");
    }
}

void tag_directory(const char *tag, const char *dir) {
    string directory = get_directory(dir);
    
    ofstream fstr;
    fstr.open(data_path, ios::app);
    string line;
    
    tuple<int, string> result = get_directory_with_tag(tag);

    if (get<0>(result) != -1) {
        cout << "pair already exists" << endl;
    } else {
        ostringstream oss;
        oss << tag << "=" << directory;
        fstr << oss.str() << endl;
        cout << tag << " has been linked to " << directory << endl;  
    }

    fstr.close();
}

string get_directory(const char *arg) {
    const filesystem::path p(arg);
    if (filesystem::exists(p) && filesystem::is_directory(p)) {
        if (*arg == '.') return filesystem::current_path(); 
        else return p;
    } else {
        throw invalid_argument("no such directory");
    } 
}

tuple<int, string> get_directory_with_tag(const char *tag) {
    string queriedTag = tag;
    ifstream ifstr;
    ifstr.open(data_path);

    string line;
    int line_number = -1;
    string directory = "";
    
    while(ifstr >> line) {
        line_number++;
        int split_index = line.find('=');
        string tag_in_line = line.substr(0, split_index);

        for (auto itr = tag_in_line.begin(), tagItr = queriedTag.begin(); itr != tag_in_line.end(); itr++, tagItr++) { 
            if (tagItr == queriedTag.end() || *itr != *tagItr) {
                line_number = -1;
                break;
            }
        }

        if (line_number != 1) directory = line.substr(split_index+1);
    }

    return make_tuple(line_number, directory);
}

void print_directory(const char *tag) {
    tuple<int, string> result = get_directory_with_tag(tag);
    if (get<0>(result) != -1) {
        cout << get<1>(result) << endl;
    } else {
        cout << "could not find a tag-directory pair" << endl;
    }
}
