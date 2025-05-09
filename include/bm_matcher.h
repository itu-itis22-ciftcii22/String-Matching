#ifndef BM_MATCHER_H
#define BM_MATCHER_H

#include "string_matcher.h"

class BMMatcher : public StringMatcher {
public:
    std::vector<int> search(const std::string& text, const std::string& pattern) override;
};

#endif //BM_MATCHER_H
