#include "utils.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <future>
#include <ctime>
#include <thread>
#include <unordered_set>
#include <iostream>

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

void run_all_tests(StringMatcher& matcher,
                   const std::string& text_path,
                   const std::string& pattern_path,
                   const std::string& results_path) {
    std::vector<std::string> texts = load_entries_from_file(text_path, "---TEXT");
    std::vector<std::string> patterns = load_entries_from_file(pattern_path, "---PATTERN");

    int total = texts.size() * patterns.size();
    int num_batches = total / 10000;
    std::vector<std::string> results(total);

    std::vector<std::pair<int, int>> indices;
    indices.reserve(total);
    for (int i = 0; i < texts.size(); ++i)
        for (int j = 0; j < patterns.size(); ++j)
            indices.emplace_back(i, j);

    int batch_size = (total + num_batches - 1) / num_batches;

    for (int b = 0; b < num_batches; ++b) {
        int start = b * batch_size;
        int end = std::min(start + batch_size, total);

        int num_threads = std::thread::hardware_concurrency();
        if (num_threads == 0) num_threads = 4;

        int batch_len = end - start;
        int chunk_size = (batch_len + num_threads - 1) / num_threads;

        std::vector<std::thread> threads;

        for (int t = 0; t < num_threads; ++t) {
            int chunk_start = start + t * chunk_size;
            int chunk_end = std::min(start + (t + 1) * chunk_size, end);

            threads.emplace_back([=, &texts, &patterns, &indices, &results, &matcher]() {
                for (int k = chunk_start; k < chunk_end; ++k) {
                    int text_idx = indices[k].first;
                    int pattern_idx = indices[k].second;
                    int index = text_idx * patterns.size() + pattern_idx;

                    const std::string& text = texts[text_idx];
                    const std::string& pattern = patterns[pattern_idx];

                    std::clock_t start_t = std::clock();
                    std::vector<int> matches = matcher.search(text, pattern);
                    std::clock_t end_t = std::clock();

                    double duration = 1000000.0 * (end_t - start_t) / CLOCKS_PER_SEC;
                    double ratio = static_cast<double>(pattern.length()) / text.length();
                    double match_density = static_cast<double>(matches.size()) / text.length();
                    std::unordered_set<char> pattern_chars(pattern.begin(), pattern.end());
                    std::unordered_set<char> text_chars(text.begin(), text.end());
                    double uniqueness = static_cast<double>(pattern_chars.size()) / pattern.length();

                    results[index] =
                        std::to_string(pattern.length()) + "," +
                        std::to_string(text.length()) + "," +
                        std::to_string(matches.size()) + "," +
                        std::to_string(duration) + "," +
                        std::to_string(ratio) + "," +
                        std::to_string(match_density) + "," +
                        std::to_string(text_chars.size()) + "," +
                        std::to_string(pattern_chars.size()) + "," +
                        std::to_string(uniqueness) + "\n";
                }
            });
        }

        for (auto& thread : threads)
            thread.join();

        std::cerr << "Finished batch " << (b + 1) << " / " << num_batches << "\n";
    }

    std::ofstream out(results_path);
    out << "pattern_length,text_length,match_count,time_micro,ratio,"
           "match_density,text_alphabet_size,pattern_alphabet_size,uniqueness\n";
    for (const auto& line : results)
        out << line;
    out.close();
}