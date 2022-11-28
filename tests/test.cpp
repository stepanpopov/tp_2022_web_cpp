#include <iostream>

#include "gtest/gtest.h"

#include "set.hpp"

TEST(TestSet, correct_empty_iterators) {
    tp::Set<int> s;
    for(int i = 1; i < 10; ++i) {
        s.insert(i);
    }

    for(int i = 1; i < 10; ++i) {
        s.erase(i);
    }
    ASSERT_TRUE(s.begin() == s.end());
}

TEST(TestSet, correct_empty_lower_bound) {
    tp::Set<int> s;
    for(int i = 1; i < 10; ++i) {
    s.insert(i);
    }

    for(int i = 1; i < 10; ++i) {
    s.erase(i);
    }
    ASSERT_EQ(s.lower_bound(13), s.begin());
}


