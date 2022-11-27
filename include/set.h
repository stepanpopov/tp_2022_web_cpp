#pragma once // NOLINT

// #include <functional>
// #include <limits>
#include <vector>  // out
// #include <initializer_list>
// #include <iomanip>
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

    friend
    std::ostream &operator<<(std::ostream &out, const set<T> &s) {
        out << "size : " << s.size << std::endl;
        if (s.root != nullptr)
            out << "root_key : " << s.root->key << std::endl;
        std::vector<T> vec;
        s.vector_from_set_dfs_preorder(s.root, vec);
        for (auto it: vec) {
            out << it << " ";
        }
        out << std::endl;
        return out;
    }

private:
    void vector_from_set_dfs_preorder(node<T> *n, std::vector<T> &v) const {
        if (n == nullptr) {
            return;
        }
        v.push_back(n->key);
        vector_from_set_dfs_preorder(n->left, v);
        vector_from_set_dfs_preorder(n->right, v);
    }

    void node_visit_and_delete(node<T> *n);

    void node_visit_and_copy(node<T> *&n, node<T> *copy_node);

    bool node_find(node<T> *n, const T &key) const;

    node<T> *node_insert(node<T> *n, const T &key);

    node<T> *node_find_min(node<T> *n) const;

    node<T> *node_without_min(node<T> *n);

    node<T> *node_remove(node<T> *n, const T &key);

    int node_balance_factor(node<T> *n) const;

    void node_fix_height(node<T> *n);

    size_t node_height(node<T> *n) const;

    node<T> *node_rotate_right(node<T> *n);

    node<T> *node_rotate_left(node<T> *n);

    node<T> *node_balance(node<T> *n);


    node<T> *root = nullptr;
    node<T> *begin = nullptr;
    node<T> *last = nullptr;

    size_t size = 0;
};
}  // namespace tp

#include "set.impl"
