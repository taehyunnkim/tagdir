#include <iostream>
#include <filesystem>
#include <stdexcept>
#include "TagDir.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    try {
        switch(argc) {
            case 1:
                cout << "No argument was supplied." << endl;
                break;
            case 2:
                switchDirectory(argv[1]);
                break;
            default:
                break;
        } 
    } catch (invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }


    getEnvHome();
    return 0;
}

void getEnvHome() {
    if(const char *env_home = getenv("HOME")) {
        cout << "User's Home Directory: " << env_home << endl;
    }
}

void switchDirectory(const char *arg) {
    const filesystem::path p(arg);
    if (filesystem::exists(p) && filesystem::is_directory(p)) {
        cout << p << " is a directory." << endl; 
    } else {
        throw invalid_argument("no such directory");
    }
}
