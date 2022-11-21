#include "set.h"

namespace tp {
template<class T>
set<T>::set() {

}

template<class T>
void set<T>::insert(cont T& key) {

}

template<class T>
void set<T>::erase(cont T& key) {

}

template<class T>
size_t set<T>::get_size() const {
    return size;
}

template<class T>
bool empty() const {
    return (size == 0);
}

template<class T>
node<T>* node_insert(node<T>* p, cont T& key) {
    if( !p ) return new node(key);
    if( key <p->key )
        p->left = node_insert(p->left,key);
    else
        p->right = node_insert(p->right,key);
}

node<T>* node_remove(node<T>* p, cont T& key) {
    if (!p) return nullptr;
    if (key < p->key)
        p->left = node_remove(p->left, key);
    else if (key > p->key)
        p->right = node_remove(p->right, key);
}

}  // namespace tp
