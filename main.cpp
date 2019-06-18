#include <iostream>
#include "BTree.h"

using namespace std;
int main() {
    BTree *bTree = new BTree(4);
    srand(1);
    for(int i = 0; i < 40; i++){
        bTree->insert(rand()%500 + rand()%500);
    }
    bTree->traverse();
    printf("\n");

    bTree->remove(570);
    bTree->remove(321);
    bTree->traverse();
    printf("\n");
    bTree->search(570);
    printf("\n");
    bTree->search(628);
    printf("\n");

    return 0;
}