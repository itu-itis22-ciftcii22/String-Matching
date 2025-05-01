#ifndef NAIVE_MATCHER_H
#define NAIVE_MATCHER_H

#include "string_matcher.h"

class NaiveMatcher : public StringMatcher {
private:
    std::string pattern;

public:
    void preprocess(const std::string& pattern) override;
    std::vector<int> search(const std::string& text) override;
};

#endif //NAIVE_MATCHER_H
