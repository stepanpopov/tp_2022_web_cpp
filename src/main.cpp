#include <iostream>
#include "set.hpp"

int main() {
    tp::Set<int> s;
    for (int i = 1; i < 10; ++i) {
        s.insert(i);
    }
    for (int i = 1; i < 10; ++i) {
        s.erase(i);
    }

    std::cout << s;
    std::cout << *(s.lower_bound(13)) << std::endl;
    std::cout << bool(s.begin() == s.end()) << std::endl;


    return 0;
}
