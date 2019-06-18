//
// Created by kei98 on 17/06/19.
//

#ifndef DATASTRUCTURE_BTREE_H
#define DATASTRUCTURE_BTREE_H

#include "BTreeNode.h"
#include <iostream>
#include <clocale>

using namespace std;

/**
 * Árbol B de enteros
 */

class BTree {
    BTreeNode *root; // Pointer al nodo raíz
    int t;  // Grado del árbol
public:
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void traverse() {
        if (root != nullptr) root->traverse();
    }

    BTreeNode *search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    void insert(int k);

    void remove(int k);
};

#endif //DATASTRUCTURE_BTREE_H
