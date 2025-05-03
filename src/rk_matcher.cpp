#include "rk_matcher.h"

std::vector<int> RKMatcher::search(const std::string& text, const std::string& pattern) {
    std::vector<int> positions;
    int M = pattern.size();
    int N = text.size();
    int p = 0; // hash value for pattern
    int t = 0; // hash value for text window
    int h = 1;
    const int d = 256; // size of input alphabet (e.g., extended ASCII)
    const int q = 1000003;

    if (M == 0 || N < M) return positions;

    // Calculate h = pow(d, M-1) % q
    for (int i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate initial hash values for pattern and first window of text
    for (int i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over the text
    for (int i = 0; i <= N - M; i++) {
        // If hash values match, check characters
        if (p == t) {
            int j = 0;
            while (j < M && text[i + j] == pattern[j])
                ++j;

            if (j == M)
                positions.push_back(i); // Match found
        }

        // Compute hash for next window
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;
            if (t < 0)
                t += q;
        }
    }

    return positions;
}