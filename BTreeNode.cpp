//
// Created by kei98 on 17/06/19.
//

#include <iostream>
#include "BTreeNode.h"

BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys = new int[2 * t - 1];
    C = new BTreeNode *[2 * t];

    keysN = 0;
}

/**
 * Función que retorna el índice de la primera llave que sea mayor o igual que k
 * @param k
 * @return
 */
int BTreeNode::findKey(int k) {
    int idx = 0;
    while (idx < keysN && keys[idx] < k){
        ++idx;
    }
    return idx;
}

/**
 * Función que busca y elimina la llave k del sub-árbol
 * @param k
 */
void BTreeNode::remove(int k) {
    int idx = findKey(k);

    // ¿La llave buscada está presente en este nodo?
    if (idx < keysN && keys[idx] == k) {

        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        // Si el nodo es una hoja, la llave no está presente en el árbol
        if (leaf) {
            cout << "La llave buscada no se encuentra en este árbol " << endl;
            return;
        }

        //Señala si la llave que se desea eliminar se encuentra en algún sub-árbol
        bool flag = ((idx == keysN) ? true : false);

        if (C[idx]-> keysN < t)
            fill(idx);

        if (flag && idx > keysN)
            C[idx - 1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}

/**
 * Función para eliminar un nodo que es una hoja
 * @param idx
 */
void BTreeNode::removeFromLeaf(int idx) {

    for (int i = idx + 1; i < keysN; ++i)
        keys[i - 1] = keys[i];

    keysN--;

    return;
}
/**
 * Función para eliminar un nodo que no es una hoja
 * @param idx
 */
void BTreeNode::removeFromNonLeaf(int idx) {

    int k = keys[idx];

    if (C[idx]-> keysN >= t) {
        int pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    }

    else if (C[idx + 1]-> keysN >= t) {
        int succ = getSucc(idx);
        keys[idx] = succ;
        C[idx + 1]->remove(succ);
    }

    else {
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}

/**
 * Función para encontrar el predecesor de keys[idx]
 * @param idx
 * @return
 */
int BTreeNode::getPred(int idx) {
    BTreeNode *cur = C[idx];
    while (!cur->leaf)
        cur = cur->C[cur-> keysN];

    return cur->keys[cur->keysN - 1];
}

int BTreeNode::getSucc(int idx) {
    BTreeNode *cur = C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];

    return cur->keys[0];
}

/**
 * Función para rellenar el nodo hijo C[idx] que tiene menos de t-1 llaves
 * @param idx
 */
void BTreeNode::fill(int idx) {

    if (idx != 0 && C[idx - 1]->keysN >= t)
        borrowFromPrev(idx);

    else if (idx != keysN && C[idx + 1]->keysN >= t)
        borrowFromNext(idx);

    else {
        if (idx != keysN)
            merge(idx);
        else
            merge(idx - 1);
    }
    return;
}

/**
 * Función que toma una llave de C[idx-1] y la inserta en C[idx]
 * @param idx
 */
void BTreeNode::borrowFromPrev(int idx) {

    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx - 1];

    for (int i = child->keysN - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->keysN; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    child->keys[0] = keys[idx - 1];

    if (!leaf)
        child->C[0] = sibling->C[sibling->keysN];

    keys[idx - 1] = sibling->keys[sibling->keysN - 1];

    child->keysN += 1;
    sibling->keysN -= 1;

    return;
}

/**
 * Función que toma una llave de C[idx+1] y la coloca C[idx]
 * @param idx
 */
void BTreeNode::borrowFromNext(int idx) {

    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx + 1];

    child->keys[(child->keysN)] = keys[idx];

    if (!(child->leaf))
        child->C[(child->keysN) + 1] = sibling->C[0];

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->keysN; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->keysN; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->keysN += 1;
    sibling->keysN -= 1;

    return;
}

/**
 * Función que mezcla C[idx] con C[idx+1] y libera a C[idx +1]
 * @param idx
 */
void BTreeNode::merge(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx + 1];

    child->keys[t - 1] = keys[idx];

    for (int i = 0; i < sibling->keysN; ++i)
        child->keys[i + t] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->keysN; ++i)
            child->C[i + t] = sibling->C[i];
    }

    for (int i = idx + 1; i < keysN; ++i)
        keys[i - 1] = keys[i];

    for (int i = idx + 2; i <= keysN; ++i)
        C[i - 1] = C[i];

    child->keysN += sibling->keysN + 1;
    keysN--;

    delete (sibling);
    return;
}

/**
 * Función para insertar un elemento k en un nodo
 * que no está completamente lleno
 * @param k
 */
void BTreeNode::insertNonFull(int k) {
    int i = keysN - 1;

    if (leaf == true) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        keysN = keysN + 1;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (C[i + 1]->keysN == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);

            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

/**
 * Función que divide el hijo 'y'
 * Se utiliza cuando 'y' esté completamente lleno
 * @param i, y
 */
void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->keysN = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->keysN = t - 1;

    for (int j = keysN; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = keysN - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];

    keysN = keysN + 1;
}

/**
 * Función que recorre todos los nodos del sub-árbol sobre el que es llamado
 * e imprime sus valores
 */
void BTreeNode::traverse() {
    if(this != NULL){
        int i;
        for (i = 0; i < keysN; i++) {
            if (leaf == false)
                C[i]->traverse();
            cout << " " << keys[i];
        }

        if (leaf == false)
            C[i]->traverse();
    }else{
        cout << "The element doesn't exist" << endl;
    }

}

/**
 * Función para buscar la llave k en el sub-árbol
 * @param k
 * @return
 */
BTreeNode *BTreeNode::search(int k) {
    int i = 0;
    while (i < keysN && k > keys[i])
        i++;

    if (keys[i] == k) {
        cout << "Found it!" << endl;
        return this;
    }
    if (leaf == true) {
        cout << "The element does not exist in this tree" << endl;
        return nullptr;
    }
    return C[i]->search(k);
}