#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include "TagDir.hpp"

using namespace std;

string data_path = "";
string script_path = "";
string temp_path = "";

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
                update_tagdir(argv[1], argv[2]);
                break;
            case 4:
                update_tagdir(argv[1], argv[2], argv[3]);
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

        oss.str("");

        oss << home << "/" << SCRIPT_FILE_NAME;
        script_path = oss.str();

        oss.str("");

        oss << home << "/" << TEMP_FILE_NAME;
        temp_path = oss.str();

        filesystem::path p(data_path);
        if (!filesystem::exists(p)) ofstream { data_path };
        p = filesystem::path(script_path);
        if (!filesystem::exists(p)) ofstream { script_path };
    } else {
        throw runtime_error("the home directory is not defined");
    }
}

void update_tagdir(const char *action, const char *argx) {
    string option(action);
    
    if (option == "del") {
        delete_tag(argx);
    } else {
        throw invalid_argument("unknown argument was supplied");
    }

}

void update_tagdir(const char *action, const char *argx, const char *argy) {
    string option(action);
    
    if (option == "add") {
        tag_directory(argx, argy); 
    } else {
        throw invalid_argument("unknown argument was supplied");
    }
}

void delete_tag(const char *tag) {
    ifstream ifstr;
    ofstream ofstr;

    ifstr.open(data_path);
    ofstr.open(temp_path, ios::app);
    
    string queriedTag(tag);
    string line;
    while(ifstr >> line) {
        int split_index = line.find('=');
        string tag_in_line = line.substr(0, split_index);
        
        if (tag != tag_in_line) {
            ofstr << line << endl;
        }
    }

    ifstr.close();
    ofstr.close();

    remove(data_path.c_str());
    rename(temp_path.c_str(), data_path.c_str());

    cout << tag << " removed" << endl;
}

void tag_directory(const char *tag, const char *dir) {
    string directory = get_directory(dir);
    
    ofstream fstr;
    fstr.open(data_path, ios::app);
    string line;
    
    tuple<bool, string> result = get_directory_with_tag(tag);

    if (get<0>(result)) {
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
        return filesystem::canonical(p);
    } else {
        throw invalid_argument("no such directory");
    } 
}

tuple<bool, string> get_directory_with_tag(const char *tag) {
    string queriedTag(tag);
    ifstream ifstr;
    ifstr.open(data_path);

    string line;
    bool tag_exists = false;
    string directory = "";
    
    while(ifstr >> line) {
        int split_index = line.find('=');
        string tag_in_line = line.substr(0, split_index);
        
        if (tag == tag_in_line) {
            tag_exists = true;
            directory = line.substr(split_index+1);
            break;
        }
    }

    return make_tuple(tag_exists, directory);
}

void print_directory(const char *tag) {
    tuple<bool, string> result = get_directory_with_tag(tag);
    if (get<0>(result)) {
        ofstream fstr;
        fstr.open(script_path, ios::app);
        fstr << "cd " << get<1>(result) << endl;
        fstr.close();
    } else {
        cout << "could not find a tag-directory pair" << endl;
    }
}
