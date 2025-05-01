#ifndef KMP_MATCHER_H
#define KMP_MATCHER_H

#include "string_matcher.h"

class KMPMatcher : public StringMatcher {
public:
    std::vector<int> search(const std::string& text, const std::string& pattern) override;
};

#endif //KMP_MATCHER_H
