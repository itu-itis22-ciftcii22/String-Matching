#ifndef RABIN_KARP_MATCHER_H
#define RABIN_KARP_MATCHER_H

#include "string_matcher.h"

class RKMatcher : public StringMatcher {
public:
    std::vector<int> search(const std::string& text, const std::string& pattern) override;
};

#endif //RABIN_KARP_MATCHER_H
