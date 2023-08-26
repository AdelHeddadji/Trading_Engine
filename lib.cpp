#include "lib.h"
#include <string>
#include <vector>
#include <cstring>

std::vector<std::string> split(const std::string& str, const std::string& delim) {
    std::vector<std::string> result;

    // Create a copy of the string to tokenize
    char* tempStr = strdup(str.c_str());
    char* token = strtok(tempStr, delim.c_str());

    while (token != NULL) {
        result.push_back(std::string(token));
        token = strtok(NULL, delim.c_str());
    }

    free(tempStr); // Free the allocated memory
    return result;
}
