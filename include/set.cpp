#include "set.hpp"

namespace tp {
template<class T>
Set<T>::Set() : root_(nullptr),
                end_(new Node <T>),
                size_(0) {
    begin_ = end_;
}

template<class T>
Set<T>::Set(const std::initializer_list<T> &init_list) : Set() {
    for (typename std::initializer_list<T>::const_iterator it =
            init_list.begin(); it != init_list.end(); ++it) {
        insert(*it);
    }
}

template<class T>
template<class InputIterator>
constexpr Set<T>::Set(const InputIterator it_first, const InputIterator it_last) : Set() {
    for (InputIterator it = it_first; it != it_last; std::advance(it, 1)) {
        insert(*it);
    }
}

template<class T>
Set<T>::Set(const Set <T> &s) : Set() {
    node_visit_and_copy(root_, s.root_);
    tie_linked_list();
    size_ = s.size_;
}

template<class T>
Set <T> &Set<T>::operator=(const Set <T> &s) {
    if (this == &s) {
        return *this;
    }

    node_visit_and_delete(root_);
    root_ = nullptr;
    end_->prev = nullptr;
    begin_ = end_;

    node_visit_and_copy(root_, s.root_);
    tie_linked_list();
    size_ = s.size_;

    return *this;
}

template<class T>
Set<T>::~Set() {
    delete end_;
    node_visit_and_delete(root_);
}

// SET METHODS
template<class T>
void Set<T>::insert(const T &key) {
    if (!node_find(root_, key)) {
        root_ = node_insert(root_, key);
        size_++;
        tie_linked_list();
    }
}

template<class T>
void Set<T>::erase(const T &key) {
    if (node_find(root_, key)) {
        root_ = node_remove(root_, key);
        size_--;
        tie_linked_list();
    }
}

template<class T>
typename Set<T>::iterator Set<T>::find(const T &key) const {
    Node<T> *node_element = node_find(root_, key);
    if (node_element) {
        return iterator(node_element);
    } else {
        return end();
    }
}

template<class T>
typename Set<T>::iterator Set<T>::lower_bound(const T &key) const {
    if (empty()) {
        return end();
    }

    Node<T> *node_element = node_lower_bound(root_, key);
    if (node_element->key < key) {
        return iterator(node_element->next);
    } else {
        return iterator(node_element);
    }
}

template<class T>
size_t Set<T>::size() const {
    return size_;
}

template<class T>
bool Set<T>::empty() const {
    return (size_ == 0);
}

template<class T>
void Set<T>::tie_linked_list() {
    if (empty()) {
        begin_ = end_;
    } else {
        Node<T> *node_prev = nullptr;
        linked_list_tier(root_, node_prev);
    }
}

template<class T>
void Set<T>::linked_list_tier(Node <T> *n,
                              Node <T> *&node_prev) {
    if (n == nullptr) {
        return;
    }
    linked_list_tier(n->left, node_prev);

    if (node_prev == nullptr) {
        begin_ = n;
        n->prev = nullptr;
    } else {
        node_prev->next = n;
        n->prev = node_prev;
    }
    n->next = end_;  // end ties here
    end_->prev = n;
    node_prev = n;

    linked_list_tier(n->right, node_prev);
}


// AVL TREE

template<class T>
void Set<T>::node_visit_and_delete(Node <T> *n) {
    if (n == nullptr) {
        return;
    }
    node_visit_and_delete(n->left);
    node_visit_and_delete(n->right);

    delete n;
}

template<class T>
void Set<T>::node_visit_and_copy(Node <T> *&n, Node <T> *copy_node) {
    if (copy_node == nullptr) {
        return;
    }
    n = new Node<T>(copy_node->key);

    node_visit_and_copy(n->left, copy_node->left);
    node_visit_and_copy(n->right, copy_node->right);
}

template<class T>
Node <T> *Set<T>::node_lower_bound(Node <T> *n, const T &key) {
    if (n == nullptr) {
        return nullptr;
    }

    if (key < n->key) {
        if (n->left == nullptr) {
            return n;
        }
        return node_lower_bound(n->left, key);
    } else if (n->key < key) {
        if (n->right == nullptr) {
            return n;
        }
        return node_lower_bound(n->right, key);
    } else {
        return n;
    }
}

template<class T>
Node <T> *Set<T>::node_find(Node <T> *n, const T &key) {
    if (n == nullptr) {
        return nullptr;
    }

    if (key < n->key) {
        return node_find(n->left, key);
    } else if (n->key < key) {
        return node_find(n->right, key);
    } else {
        return n;
    }
}

template<class T>
Node <T> *Set<T>::node_insert(Node <T> *n, const T &key) {
    if (n == nullptr) {
        return new Node<T>(key);
    }

    if (key < n->key) {
        n->left = node_insert(n->left, key);
    } else if (n->key < key) {
        n->right = node_insert(n->right, key);
    }

    return node_balance(n);
}

template<class T>
Node <T> *Set<T>::node_find_min(Node <T> *n) {  // node_remove helper
    if (n->left == nullptr) {
        return n;
    }
    return node_find_min(n->left);
}

template<class T>
Node <T> *Set<T>::node_without_min(Node <T> *n) {  // node_remove helper
    if (n->left == nullptr) {
        return n->right;
    }
    n->left = node_without_min(n->left);
    return node_balance(n);
}

template<class T>
Node <T> *Set<T>::node_remove(Node <T> *n, const T &key) {
    if (n == nullptr) {
        return nullptr;
    }
    if (key < n->key) {
        n->left = node_remove(n->left, key);
    } else if (n->key < key) {
        n->right = node_remove(n->right, key);
    } else {
        Node<T> *node_left = n->left;
        Node<T> *node_right = n->right;
        delete n;

        if (node_right == nullptr) {
            return node_left;
        }

        Node<T> *node_min = node_find_min(node_right);
        node_min->right = node_without_min(node_right);
        node_min->left = node_left;

        return node_balance(node_min);
    }

    return node_balance(n);
}

// AVL TREE BALANCE

template<class T>
size_t Set<T>::node_height(Node <T> *n) {
    if (n != nullptr) {
        return n->height;
    } else {
        return 0;
    }
}

template<class T>
int Set<T>::node_balance_factor(Node <T> *n) {
    return node_height(n->right) - node_height(n->left);
}

template<class T>
void Set<T>::node_fix_height(Node <T> *n) {
    size_t height_left = node_height(n->left);
    size_t height_right = node_height(n->right);

    n->height = std::max(height_left, height_right) + 1;
}

template<class T>
Node <T> *Set<T>::node_rotate_right(Node <T> *n) {
    Node<T> *q = n->left;
    n->left = q->right;
    q->right = n;
    node_fix_height(n);
    node_fix_height(q);
    return q;
}

template<class T>
Node <T> *Set<T>::node_rotate_left(Node <T> *n) {
    Node<T> *p = n->right;
    n->right = p->left;
    p->left = n;
    node_fix_height(n);
    node_fix_height(p);
    return p;
}

template<class T>
Node <T> *Set<T>::node_balance(Node <T> *n) {
    node_fix_height(n);
    if (node_balance_factor(n) == 2 && node_balance_factor(n->right) < 0) {
        n->right = node_rotate_right(n->right);
        return node_rotate_left(n);
    } else if (node_balance_factor(n) == 2 && node_balance_factor(n->right) >= 0) {
        return node_rotate_left(n);
    } else if (node_balance_factor(n) == -2 && node_balance_factor(n->left) > 0) {
        n->left = node_rotate_left(n->left);
        return node_rotate_right(n);
    } else if (node_balance_factor(n) == -2 && node_balance_factor(n->left) <= 0) {
        return node_rotate_right(n);
    }
    return n;
}

}  // namespace tp
