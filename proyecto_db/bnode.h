#ifndef PROYECTOBD2_BNODE_H
#define PROYECTOBD2_BNODE_H

#include <iostream>
#include <vector>
#include "idata.hpp"
using namespace::std;

class bnode {
    pair<int*,idata*>keys;
    int t, n;
    bnode **C;
    bool leaf;
public:
    bnode(int _t, bool _leaf);
    void traverse();
    int findKey(int k);
    void insertNonFull(int k);
    void splitChild(int i, bnode *y);
    void deletion(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPredecessor(int idx);
    int getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    void getInfo();
    friend class btree;
};

#endif //PROYECTOBD2_BNODE_H
