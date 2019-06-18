//
// Created by kei98 on 17/06/19.
//

#include "BTree.h"

void BTree::remove(int k) {
    if (root == nullptr) {
        cout << "El árbol está vacío" << endl;
        return;
    }

    root->remove(k);

    /**
     * Si la raíz del nodo tiene 0 llaves y si tiene algún hijo convierte el primer hijo en la nueva raíz
     * por el contrario, si no tiene alguno, se hace la raíz nula
     *
     */
    if (root->keysN == 0) {
        BTreeNode *tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->C[0];
        delete tmp;
    }
    return;
}

void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->keysN = 1;
    } else {
        // Si el array 'root' está lleno
        if (root->keysN == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}
