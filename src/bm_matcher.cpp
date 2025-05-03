#include "bm_matcher.h"

#include <vector>
#include <string>
#include <algorithm>

std::vector<int> BMMatcher::search(const std::string& text, const std::string& pattern) {
    int m = pattern.size();
    int n = text.size();
    std::vector<int> positions;

    if (m == 0 || n == 0 || m > n)
        return positions;


    int NO_OF_CHARS = 256;
    std::vector<int> badchar(NO_OF_CHARS, -1);

    // Lambda for computing the bad character heuristic
    auto badCharHeuristic = [&](const std::string& str, int size) {
        for (int i = 0; i < size; i++)
            badchar[(unsigned char)str[i]] = i;
    };

    badCharHeuristic(pattern, m);

    int s = 0; // shift of the pattern with respect to text
    while (s <= (n - m)) {
        int j = m - 1;

        // Move backward while characters match
        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            positions.push_back(s); // Match found
            s += (s + m < n) ? m - badchar[(unsigned char)text[s + m]] : 1;
        } else {
            s += std::max(1, j - badchar[(unsigned char)text[s + j]]);
        }
    }

    return positions;
}