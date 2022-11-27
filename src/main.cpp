#include <iostream>
#include "set.h"

using namespace std;

int main() {
    tp::set<char> s;
    // cout << s;
    // char a = 'a';
    s.insert('a');
    s.insert('b');
    s.insert('c');
    s.insert('d');
    s.insert('e');
    s.insert('h');
    s.insert('f');
    s.insert('g');

    cout << s;
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
