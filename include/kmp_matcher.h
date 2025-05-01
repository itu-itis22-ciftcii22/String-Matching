#ifndef KMP_MATCHER_H
#define KMP_MATCHER_H

#include "string_matcher.h"

class KMPMatcher : public StringMatcher {
private:
    std::string pattern;

public:
    void preprocess(const std::string& pattern) override;
    std::vector<int> search(const std::string& text) override;
};

#endif //KMP_MATCHER_H
