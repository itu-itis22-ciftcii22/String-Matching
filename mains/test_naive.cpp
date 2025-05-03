#include <string>

#include "naive_matcher.h"
#include "utils.h"
#include "config.h"

int main() {
    std::string source_path = std::string(SOURCE_DIR);
    std::string text_path{source_path + "/data/sample_texts.txt"};
    std::string pattern_path{ source_path + "/data/test_patterns.txt"};
    NaiveMatcher naive_matcher;
    run_all_tests(naive_matcher, text_path, pattern_path, source_path +  + "/results/naive_results.csv");
    return 0;
}