#ifndef NAIVE_MATCHER_H
#define NAIVE_MATCHER_H

#include "string_matcher.h"

class NaiveMatcher : public StringMatcher {
public:
    std::vector<int> search(const std::string& text, const std::string& pattern) override;
};

#endif //NAIVE_MATCHER_H
