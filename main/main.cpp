#include <iostream>
#include <chrono>
#include "naive_matcher.h"

void runTest(StringMatcher& matcher, const std::string& pattern, const std::string& text) {

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = matcher.search(text, pattern);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Match positions: ";
    for (int pos : result) std::cout << pos << " ";
    std::cout << "\nTime: " << duration.count() << " seconds\n";
}

int main() {
    std::string pattern = "test";
    std::string text = "this is a test text for test cases";

    NaiveMatcher naive;
    runTest(naive, pattern, text);

    return 0;
}
