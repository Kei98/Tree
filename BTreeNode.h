//
// Created by kei98 on 17/06/19.
//

#ifndef DATASTRUCTURE_BTREENODE_H
#define DATASTRUCTURE_BTREENODE_H

using namespace std;

class BTreeNode {
    int *keys;  //Array que debe ser cambiado a chars
    int t;      // Mínimo grado
    BTreeNode **C; // Pointers a otros nodos
    int keysN;     // Número actual de llaves
    bool leaf;
public:

    BTreeNode(int _t, bool _leaf);

    void traverse();

    BTreeNode *search(int k);

    int findKey(int k);

    void insertNonFull(int k);

    void splitChild(int i, BTreeNode *y);

    void remove(int k);

    void removeFromLeaf(int idx);

    void removeFromNonLeaf(int idx);

    int getPred(int idx);

    int getSucc(int idx);

    void fill(int idx);

    void borrowFromPrev(int idx);

    void borrowFromNext(int idx);

    void merge(int idx);

    friend class BTree;
};

#endif //DATASTRUCTURE_BTREENODE_H
