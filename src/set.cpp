#include "set.h"

namespace tp {
template<class T>
set<T>::set() {

}

template<class T>
void set<T>::insert(cont T& key) {
    node_insert(root, key);
}

template<class T>
void set<T>::erase(cont T& key) {

}

template<class T>
size_t set<T>::get_size() const {
    return size;
}

template<class T>
bool set<T>::empty() const {
    return (size == 0);
}

template<class T>
void set<T>::node_insert(node<T>* n, cont T& key) {
    if( n == nullptr ) {
        n = new node<T>(key);
        return;
    }
    if( n->key > key )
        node_insert(n->left, key);
    else
        node_insert(n->right, key );
}

node<T>* set<T>::node_remove(node<T>* p, cont T& key) {
    if (!p) return nullptr;
    if (key < p->key)
        p->left = node_remove(p->left, key);
    else if (key > p->key)
        p->right = node_remove(p->right, key);
}

bool set<T>::node_remove(node<T>* n, cont T& key) {
    if( n == nullptr )
        return false;
    if( n->key == key ) {
        node_remove_helper(n);
        return true;
    }
    return node_remove( n->key > key ? n->left : n->right,
                        key );
}

void node_remove_helper(node<T>* n)
{
    if( n->Left == 0 ) {
        node<T>* right_node = n->right;
        delete n;
        n = right_node;
    } else if( node->right == 0 ) {
        CNode* left = node->Left;
        delete node;
        node = left;
    } else {
        CNode* minParent = node;
        CNode* min = node->Right;
        while( min->Left != 0 ) {
            minParent = min;
            min = min->Left;
        }
        node->Data = min->Data;
        (minParent->Left == min ? minParent->Left : minParent->Right)
                = min->Right;
        delete min;
    }
}



}  // namespace tp
