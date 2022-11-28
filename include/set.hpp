#pragma once // NOLINT

#include <iostream>

namespace tp {

    template<class T>
    struct Node {
        Node() : key(T()) {}

        Node(const T &key) : key(key) {}

        T key;
        size_t height = 1;
        Node *right = nullptr;  // FOR AVL TREE
        Node *left = nullptr;

        Node *next = nullptr;  // FOR LINKED LIST
        Node *prev = nullptr;
    };

    template<class T>
    class Set {
    public:
        Set();

        template<class InputIterator>
        constexpr Set(const InputIterator it_first, const InputIterator it_last);

        Set(const std::initializer_list<T> &init_list);

        Set(const Set<T> &s);

        Set<T> &operator=(const Set<T> &s);

        ~Set();

        void insert(const T &key);

        void erase(const T &key);

        class iterator;  // implemented lower

        iterator find(const T &key) const;

        iterator lower_bound(const T &key) const;

        size_t size() const;

        bool empty() const;

        friend
        std::ostream &operator<<(std::ostream &out, const Set<T> &s) {
            out << "size : " << s.size_ << std::endl;
            out << "end->key : ";
            if (s.end_ == nullptr) out << "null" << std::endl;
            else out << (s.end_)->key << std::endl;
            out << "root : ";
            if (s.root_ == nullptr) out << "null" << std::endl;
            else out << (s.root_)->key << std::endl;

            Node<T> *it = s.begin_;
            while (it->next != nullptr) {
                out << it->key << " ";
                it = it->next;
            }

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

            iterator(Node<T> *n) : cur(n) {};

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

            iterator &operator++() {
                cur = cur->next;
                return *this;
            }

            iterator operator++(int) {
                Node<T> *temp = cur;
                cur = cur->next;
                return temp;
            }

            iterator &operator--() {
                cur = cur->prev;
                return *this;
            }

            iterator operator--(int) {
                Node<T> *temp = cur;
                cur = cur->prev;
                return temp;
            }

        private:
            Node<T> *cur;
        };

        iterator begin() const { return iterator(begin_); }

        iterator end() const { return iterator(end_); }

    private:
        void tie_linked_list();

        void linked_list_tier(Node<T> *n,
                              Node<T> *&node_prev);

        void node_visit_and_delete(Node<T> *n);

        void node_visit_and_copy(Node<T> *&n, Node<T> *copy_node);

        Node<T> *node_lower_bound(Node<T> *n, const T &key) const;

        Node<T> *node_find(Node<T> *n, const T &key) const;

        Node<T> *node_insert(Node<T> *n, const T &key);

        Node<T> *node_find_min(Node<T> *n) const;

        Node<T> *node_without_min(Node<T> *n);

        Node<T> *node_remove(Node<T> *n, const T &key);

        int node_balance_factor(Node<T> *n) const;

        void node_fix_height(Node<T> *n);

        size_t node_height(Node<T> *n) const;

        Node<T> *node_rotate_right(Node<T> *n);

        Node<T> *node_rotate_left(Node<T> *n);

        Node<T> *node_balance(Node<T> *n);


        Node<T> *root_ = nullptr;
        Node<T> *begin_ = nullptr;
        Node<T> *end_ = nullptr;

        size_t size_ = 0;
    };
}  // namespace tp

#include "set.cpp"
