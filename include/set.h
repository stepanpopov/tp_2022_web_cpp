#pragma once // NOLINT

#include <functional>
#include <limits>
#include <vector>
#include <initializer_list>
#include <iomanip>
#include <iostream>

namespace tp {

    template<class T>
    struct node {
        node() : key(T()) {}

        node(const T &key) : key(key) {}

        T key;
        size_t height = 1;
        node *parent = nullptr;
        node *right = nullptr;
        node *left = nullptr;
        // node* _next = nullptr;
        // node* _prev = nullptr;
    };

    template<class T>
    class set {
    public:
        set();

        set(const set<T> &s);

        set<T> &operator=(const set<T> &s);

        ~set();

        void insert(const T &key);

        void erase(const T &key);

        size_t get_size() const;

        bool empty() const;

    private:
        node<T> *node_insert(node<T> *n, const T &key);

        node<T> *node_find_min(node<T> *n);

        node<T> *node_without_min(node<T> *n);

        node<T> *node_remove(node<T> *n, const T &key);

        size_t node_balance_factor(node<T> *n);

        void node_fix_height(node<T> *n);

        size_t node_height(node<T> *n);

        node<T> *node_rotate_right(node<T> *n);

        node<T> *node_rotate_left(node<T> *n);

        node<T> *node_balance(node<T> *n);


        node<T> *root = nullptr;
        node<T> *begin = nullptr;
        node<T> *last = nullptr;

        size_t size = 0;
    };

    // std::ostream &operator<<(std::ostream &os, const set<T> &s);
}  // namespace tp

#include "set.impl"
