#include <iostream>
#include <fstream>
#include <string>

bool isJsonFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    char c;
    bool isJson = true;
    bool isFirstChar = true;

    while (file.get(c)) {
        if (isFirstChar) {
            if (c != '{' && c != '[') {
                isJson = false;
                break;
            }
            isFirstChar = false;
        }
    }

    if (!isJson) {
        std::cerr << "File is not a Json file: " << filename << std::endl;
    }

    return isJson;
}

int main(const int argc, const char **argv) {
    if (argc < 2) {
        std::cerr << "Please provide a Json file\n for questions -h or --help\n";
        return 1;
    }

    if (!isJsonFile(argv[1])) {
        return 1;
    }

    // Your code to process the Json file

    return 0;
}