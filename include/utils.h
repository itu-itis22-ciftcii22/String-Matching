#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

#include "string_matcher.h"

std::vector<std::pair<int, std::string>> load_entries_with_id(const std::string& filename, const std::string& delimiter);

void run_all_tests(StringMatcher& matcher,
                   const std::string& text_path,
                   const std::string& pattern_path,
                   const std::string& results_path);

#endif //UTILS_H
