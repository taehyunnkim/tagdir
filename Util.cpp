#include <cctype>
#include <string>

bool is_alnum(std::string& str) {
    for (auto itr = str.begin(); itr != str.end(); itr++) {
        if (std::isalnum(*itr) == 0) {
            return false;
        }
    }

    return true;
}
