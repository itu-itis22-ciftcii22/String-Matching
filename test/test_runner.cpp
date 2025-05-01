#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include "naive_matcher.h"
// Include other matchers when implemented
#include "utils.h"

void run_all_tests(const std::string& text_path, const std::string& pattern_path) {
    std::vector<std::string> texts = load_entries_from_file(text_path, "---TEXT");
    std::vector<std::string> patterns = load_entries_from_file(pattern_path, "---PATTERN");

    for (const auto& text : texts) {
        for (const auto& pattern : patterns) {
            NaiveMatcher matcher;  // Swap with other matchers as needed
            matcher.preprocess(pattern);

            auto start = std::chrono::high_resolution_clock::now();
            std::vector<int> matches = matcher.search(text);
            auto end = std::chrono::high_resolution_clock::now();

            double duration = std::chrono::duration<double, std::milli>(end - start).count();

            std::cout << "Pattern length: " << pattern.length()
                      << ", Text length: " << text.length()
                      << ", Matches: " << matches.size()
                      << ", Time: " << duration << " ms" << std::endl;
        }
    }
}

int main() {
    run_all_tests("data/sample_texts.txt", "data/test_patterns.txt");
    return 0;
}