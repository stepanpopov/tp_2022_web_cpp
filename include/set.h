#pragma once // NOLINT

#include <functional>
#include <limits>
#include <vector>
#include <initializer_list>
#include <iomanip>
#include <iostream>

namespace tp {

template <class T>
struct node {
    node() : key(T()) {}
    node(cont T& key) : key(key) {}

    T key;
    Node* parent = nullptr;
    Node* right = nullptr;
    Node* left = nullptr;
    // Node* _next = nullptr;
    // Node* _prev = nullptr;
};

template <class T>
    class set {
    public:
        set();


        void insert(cont T& key);
        void erase(cont T& key);
        void get_size() const;
        bool empty() const;
    private:
        node* node_insert(node* p, int k);

        node<T>* root = nullptr;
        Node* begin = nullptr;
        Node* last = nullptr;

        size_t size = 0;
    };

    std::ostream &operator<<(std::ostream &os, const set<T> &s);
}  // namespace tp
