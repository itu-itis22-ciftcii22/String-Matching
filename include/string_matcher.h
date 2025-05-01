#ifndef STRING_MATCHER_H
#define STRING_MATCHER_H

#include <string>
#include <vector>

class StringMatcher {
public:
    virtual std::vector<int> search(const std::string& text, const std::string& pattern) = 0;

    virtual ~StringMatcher() = default;
};


#endif //STRING_MATCHER_H
