#include <iostream>
#include <vector>
#include "set.h"

// using namespace std;

int main() {
    // std::vector<int> v{1, 2, 3, 4, 5};
    // tp::set<int> s(v.begin(), v.end());

    // tp::set<int> s(v.begin(), v.end());
    //v[0] = 1000;
    // tp::set<int> s(&v[0], &v[0] + 4);
    // cout << s;
    // char a = 'a';
    tp::set<char> s;
    s.insert('a');
    s.insert('b');
    s.insert('c');
    s.insert('d');
    s.insert('e');
    s.insert('h');
    s.insert('f');
    s.insert('g');

    std::cout << s;
    /*for(int i = 1; i < 6; ++i) {
        s.insert(i);
    }
    s.insert(3);
    // size 5
    *//*s.erase(4);
    s.erase(1);
    s.erase(3);
    s.erase(2);
    s.erase(5);
    s.erase(5);*//*
    auto s1(s);
    cout << s1;
    s1.insert(10);
    s1.erase(4);
    s1.erase(1);
    s1.erase(3);
    s1.erase(2);
    s1.erase(5);
    s1.erase(10);
    cout << endl;
    cout << s1;*/

    return 0;
}
