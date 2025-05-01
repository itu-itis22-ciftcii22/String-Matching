#include "utils.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::string> load_entries_from_file(const std::string& filename, const std::string& delimiter) {
    std::ifstream file(filename);
    std::vector<std::string> entries;
    std::string line, buffer;
    bool reading = false;

    while (std::getline(file, line)) {
        if (line.find(delimiter) != std::string::npos) {
            if (!buffer.empty()) {
                entries.push_back(buffer);
                buffer.clear();
            }
            reading = true;
            continue;
        }
        if (reading) buffer += line;
    }
    if (!buffer.empty()) entries.push_back(buffer);
    return entries;
}