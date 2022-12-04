#include <iostream>

#include "gtest/gtest.h"
#include "set.hpp"

#include <set>
#include <vector>

TEST(TestSet, correct_empty_iterators) {
    tp::Set<int> s;
    for (int i = 1; i < 10; ++i) {
        s.insert(i);
    }

    for (int i = 1; i < 10; ++i) {
        s.erase(i);
    }
    ASSERT_TRUE(s.begin() == s.end());
}

TEST(TestSet, correct_empty_lower_bound) {
    tp::Set<int> s;
    for (int i = 1; i < 10; ++i) {
        s.insert(i);
    }

    for (int i = 1; i < 10; ++i) {
        s.erase(i);
    }
    ASSERT_EQ(s.lower_bound(13), s.begin());
}

TEST(TestSet, lower_bound_check_for_existed_value) {
    tp::Set<char> s;
    s.insert('a');
    s.insert('c');
    s.insert('b');
    s.insert('f');
    s.insert('i');
    s.insert('j');
    s.insert('u');

    ASSERT_EQ(s.lower_bound('c'), ++(++s.begin()));
}

class TestComparingWithStl : public ::testing::Test {
public:
    void SetUp() override {
        for (size_t i = 0; i < START_SIZE; ++i) {
            init_elements.push_back(rand() % 1000);
            my_set.insert(init_elements[i]);
            stl_set.insert(init_elements[i]);
        }
    }

    void TearDown() override {

    }

    tp::Set<int> my_set;
    std::set<int> stl_set;

    std::vector<int> init_elements;

    static const size_t START_SIZE = 1000000;
};

TEST_F(TestComparingWithStl, erase_test) {
    for (size_t i = 0; i < START_SIZE; ++i) {
        my_set.erase(init_elements[i]);
        stl_set.erase(init_elements[i]);
    }

    auto it1 = my_set.begin();
    auto it2 = stl_set.begin();
    for (; it1 != my_set.end() && it2 != stl_set.end();
           ++it1, ++it2) {
        ASSERT_EQ(*it1, *it2);
    }
}

TEST_F(TestComparingWithStl, find_test) {
    for (size_t i = 0; i < START_SIZE; ++i) {

        auto it1_found = my_set.find(init_elements[i]);
        auto it2_found = stl_set.find(init_elements[i]);

        ASSERT_TRUE((it1_found == my_set.end() && it2_found == stl_set.end()) ||
                    (*it1_found == *it2_found));
    }
}
