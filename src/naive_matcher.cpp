#include "naive_matcher.h"

std::vector<int> NaiveMatcher::search(const std::string& text, const std::string& pattern) {
    std::vector<int> positions;
    int M = pattern.size();
    int N = text.size();

    // A loop to slide pat[] one by one
    for (int i = 0; i <= N - M; i++) {
        int j;

        // For current index i, check for pattern match
        for (j = 0; j < M; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }

        // If pattern matches at index i
        if (j == M) {
            positions.push_back(i);
        }
    }
    return positions;
}
