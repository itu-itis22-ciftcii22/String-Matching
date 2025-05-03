#include <string>

#include "rk_matcher.h"
#include "utils.h"
#include "config.h"

int main() {
    std::string source_path = std::string(SOURCE_DIR);
    std::string text_path{source_path + "/data/sample_texts.txt"};
    std::string pattern_path{ source_path + "/data/test_patterns.txt"};
    RKMatcher kmp_matcher;
    run_all_tests(kmp_matcher, text_path, pattern_path, source_path +  + "/results/rk_results.csv");
    return 0;
}