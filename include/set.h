#pragma once // NOLINT

#include <vector>  // out
#include <iostream>

namespace tp {

    template<class T>
    struct node {
        node() : key(T()) {}

        node(const T &key) : key(key) {}

        /*bool operator<(const node &n) {  // TODO operators for iterator
            return key < n.key;
        }*/

        T key;
        size_t height = 1;
        // node *parent = nullptr;
        node *right = nullptr;  // FOR AVL TREE
        node *left = nullptr;

        node *next = nullptr;  // FOR LINKED LIST
        node *prev = nullptr;
    };

    template<class T>
    class set {
    public:
        set();

        template<class Input_iterator>
        constexpr set(const Input_iterator it_first, const Input_iterator it_last);

        set(const std::initializer_list<T> &init_list);

        set(const set<T> &s);

        set<T> &operator=(const set<T> &s);

        ~set();

        void insert(const T &key);

        void erase(const T &key);

        class iterator;

        iterator find(const T &key) const {
            T t = key;
            return iterator(end_);
        }

        iterator lower_bound(const T &key) const {
            T t = key;
            return iterator(begin_);
        }

        void tie_linked_list();

        void linked_list_tier(node<T> *n,
                              node<T> *&node_prev);

        size_t size() const;

        bool empty() const;

        friend
        std::ostream &operator<<(std::ostream &out, const set<T> &s) {
            out << "size : " << s.size_ << std::endl;
            out << "end->key : ";
            if (s.end_ == nullptr) out << "null" << std::endl;
            else out << (s.end_)->key << std::endl;

            node<T> *it = s.begin_;
            while (it->next != nullptr) {
                out << it->key << " ";
                it = it->next;
            }
            /*if (s.root != nullptr)
                out << "root_key : " << s.root->key << std::endl;
            std::vector<T> vec;
            s.vector_from_set_dfs_preorder(s.root, vec);
            for (auto it: vec) {
                out << it << " ";
            }*/
            out << std::endl;
            return out;
        }

        class iterator {
        public:
            using difference_type = ptrdiff_t;
            using value_type = T;
            using pointer = const T *;
            using reference = const T &;
            using iterator_category = std::bidirectional_iterator_tag;

            iterator(node<T> *n) : cur(n) {};

            iterator() : cur(nullptr) {};

            iterator(const iterator &other) = default;

            iterator &operator=(const iterator &other) = default;

            const T &operator*() const { return cur->key; }

            const T *operator->() const { return &(cur->key); }

            bool operator==(const iterator &other) const {
                return (cur == other.cur);
            }

            bool operator!=(const iterator &other) const {
                return (cur != other.cur);
            }

            iterator &operator++() {cur = cur->next; return *this;}

            iterator operator++(int) {
                node<T> *temp = cur;
                cur = cur->next;
                return temp;
            }

            iterator &operator--() {cur = cur->prev; return *this; }

            iterator operator--(int) {
                node<T> *temp = cur;
                cur = cur->prev;
                return temp;
            }

        private:
            node<T> *cur;
        };
        // friend iterator;

        iterator begin() const { return iterator(begin_); }

        iterator end() const { return iterator(end_); }

    private:
        /*void vector_from_set_dfs_preorder(node<T> *n, std::vector<T> &v) const {
            if (n == nullptr) {
                return;
            }
            vector_from_set_dfs_preorder(n->left, v);
            v.push_back(n->key);
            vector_from_set_dfs_preorder(n->right, v);
        }*/

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


        node<T> *root_;  // = nullptr;
        node<T> *begin_;  // = nullptr;
        node<T> *end_;  // = nullptr;

        size_t size_ = 0;
    };
}  // namespace tp

#include "set.impl"
