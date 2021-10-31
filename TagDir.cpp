#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include "TagDir.hpp"

using namespace std;

string data_path = "";
string script_path = "";
string temp_path = "";
map<string, string> tagdir_pairs;

int main(int argc, char *argv[]) {
    try {
        init();

        switch(argc) {
            case 1:
                display_ui();
                break;
            case 2:
                write_command(argv[1]);
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
        oss << home << "/" << TAGDIR_HOME << "/" <<  DATA_FILE_NAME;
        data_path = oss.str();

        oss.str("");

        oss << home << "/" << TAGDIR_HOME << "/" << SCRIPT_FILE_NAME;
        script_path = oss.str();

        oss.str("");

        oss << home << "/"  << TAGDIR_HOME << "/" << TEMP_FILE_NAME;
        temp_path = oss.str();

        filesystem::path p(data_path);
        if (!filesystem::exists(p)) ofstream { data_path };
        p = filesystem::path(script_path);
        if (!filesystem::exists(p)) ofstream { script_path };


        ifstream ifstr;
        ifstr.open(data_path);
        string line;

        while(ifstr >> line) {
            int split_index = line.find('=');
            string tag = line.substr(0, split_index);
            string directory = line.substr(split_index+1);

            tagdir_pairs.insert(pair<string, string>(tag, directory));
        }

        ifstr.close();
    } else {
        throw runtime_error("the home directory is not defined");
    }
}

void update_tagdir(const char *action, const char *argx) {
    string option(action);
    
    if (option == "del" || option == "delete") {
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
    string queried_tag = tag;
 
    if (tagdir_pairs.find(queried_tag) == tagdir_pairs.end()) {
        throw invalid_argument("the given tag does not exist");
    } else {
        ofstream ofstr;
        ofstr.open(temp_path, ios::app);
        
        for (const auto& item : tagdir_pairs) {
            if (item.first != string(tag)) {
                ofstr << item.first << "=" << item.second << endl;
            }
        }

        ofstr.close();
        remove(data_path.c_str());
        rename(temp_path.c_str(), data_path.c_str());

        cout << tag << " removed" << endl; 
    }    
}

void tag_directory(const char *tag, const char *dir) {
    string queried_tag(tag);
    if (!is_alnum(queried_tag)) throw invalid_argument("tag must be alphanumeric!");

    string directory = get_directory(dir);

    ofstream fstr;
    fstr.open(data_path, ios::app);
    
    if (tagdir_pairs.find(queried_tag) != tagdir_pairs.end()) {
        cout << "pair already exists" << endl;
    } else {
        fstr << queried_tag << "=" << directory << endl;
        
        tagdir_pairs.insert(pair<string, string>(queried_tag, directory));
       
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

void write_command(const char *tag) {
    auto itr = tagdir_pairs.find(string(tag));
    if (itr != tagdir_pairs.end()) {
        ofstream fstr;
        fstr.open(script_path, ios::app);
        fstr << "cd " << itr->second << endl;
        fstr.close();
    } else {
        throw runtime_error("tag does not exist");
    }
}
