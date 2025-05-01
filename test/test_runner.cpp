#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include "naive_matcher.h"
#include <kmp_matcher.h>

#include "utils.h"
#include "config.h"
std::string source_path = std::string(SOURCE_DIR);


void run_all_tests(StringMatcher& matcher,
                   const std::string& text_path,
                   const std::string& pattern_path,
                   const std::string& results_path) {
    std::vector<std::string> texts = load_entries_from_file(text_path, "---TEXT");
    std::vector<std::string> patterns = load_entries_from_file(pattern_path, "---PATTERN");

    std::ofstream out(results_path);
    out << "pattern_length,text_length,match_count,time_ms\n";

    for (const auto& text : texts) {
        for (const auto& pattern : patterns) {
            matcher.preprocess(pattern);

            auto start = std::chrono::high_resolution_clock::now();
            std::vector<int> matches = matcher.search(text);
            auto end = std::chrono::high_resolution_clock::now();

            double duration = std::chrono::duration<double, std::milli>(end - start).count();

            out << pattern.length() << ","
                << text.length() << ","
                << matches.size() << ","
                << duration << "\n";
        }
    }

    out.close();
}


int main() {
    std::string text_path{source_path + "/data/sample_texts.txt"};
    std::string pattern_path{ source_path + "/data/test_patterns.txt"};
    NaiveMatcher naive_matcher;
    run_all_tests(naive_matcher, text_path, pattern_path, source_path +  + "/results/naive_results.csv");
    KMPMatcher kmp_matcher;
    run_all_tests(kmp_matcher, text_path, pattern_path, source_path +  + "/results/kmp_results.csv");
    return 0;
}