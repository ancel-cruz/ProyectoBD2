#include "bnode.h"

// B tree node
bnode::bnode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;
    keys.first = new int[2 * t - 1];
    C = new bnode*[2 * t];
    n = 0;
}

// Find the key
int bnode::findKey(int k) {
    int idx = 0;
    while (idx < n && keys.first[idx] < k)
        ++idx;
    return idx;
}

// Deletion operation
void bnode::deletion(int k) {
    int idx = findKey(k);

    if (idx < n && keys.first[idx] == k) {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        if (leaf) {
            cout << "The key " << k << " is does not exist in the tree\n";
            return;
        }
        bool flag = ((idx == n) ? true : false);

        if (C[idx]->n < t)
            fill(idx);

        if (flag && idx > n)
            C[idx - 1]->deletion(k);
        else
            C[idx]->deletion(k);
    }
    return;
}

// Remove from the leaf
void bnode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; ++i)
        keys.first[i - 1] = keys.first[i];

    n--;

    return;
}

// Delete from non leaf node
void bnode::removeFromNonLeaf(int idx) {
    int k = keys.first[idx];

    if (C[idx]->n >= t) {
        int pred = getPredecessor(idx);
        keys.first[idx] = pred;
        C[idx]->deletion(pred);
    }

    else if (C[idx + 1]->n >= t) {
        int succ = getSuccessor(idx);
        keys.first[idx] = succ;
        C[idx + 1]->deletion(succ);
    }

    else {
        merge(idx);
        C[idx]->deletion(k);
    }
    return;
}

int bnode::getPredecessor(int idx) {
    bnode *cur = C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    return cur->keys.first[cur->n - 1];
}

int bnode::getSuccessor(int idx) {
    bnode *cur = C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];

    return cur->keys.first[0];
}

void bnode::fill(int idx) {
    if (idx != 0 && C[idx - 1]->n >= t)
        borrowFromPrev(idx);

    else if (idx != n && C[idx + 1]->n >= t)
        borrowFromNext(idx);

    else {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
    return;
}

// Borrow from previous
void bnode::borrowFromPrev(int idx) {
    bnode *child = C[idx];
    bnode *sibling = C[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->keys.first[i + 1] = child->keys.first[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    child->keys.first[0] = keys.first[idx - 1];

    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    keys.first[idx - 1] = sibling->keys.first[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

// Borrow from the next
void bnode::borrowFromNext(int idx) {
    bnode *child = C[idx];
    bnode *sibling = C[idx + 1];

    child->keys.first[(child->n)] = keys.first[idx];

    if (!(child->leaf))
        child->C[(child->n) + 1] = sibling->C[0];

    keys.first[idx] = sibling->keys.first[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->keys.first[i - 1] = sibling->keys.first[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;

    return;
}

// Merge
void bnode::merge(int idx) {
    bnode *child = C[idx];
    bnode *sibling = C[idx + 1];

    child->keys.first[t - 1] = keys.first[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->keys.first[i + t] = sibling->keys.first[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

    for (int i = idx + 1; i < n; ++i)
        keys.first[i - 1] = keys.first[i];

    for (int i = idx + 2; i <= n; ++i)
        C[i - 1] = C[i];

    child->n += sibling->n + 1;
    n--;

    delete (sibling);
    return;
}

// Insertion non full
void bnode::insertNonFull(int k) {
    int i = n - 1;

    if (leaf == true) {
        while (i >= 0 && keys.first[i] > k) {
            keys.first[i + 1] = keys.first[i];
            i--;
        }

        keys.first[i + 1] = k;
        n = n + 1;
    } else {
        while (i >= 0 && keys.first[i] > k)
            i--;

        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);

            if (keys.first[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

// Split child
void bnode::splitChild(int i, bnode *y) {
    bnode *z = new bnode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys.first[j] = y->keys.first[j + t];

    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys.first[j + 1] = keys.first[j];

    keys.first[i] = y->keys.first[t - 1];

    n = n + 1;
}

// Traverse
void bnode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys.first[i];
        cout << " xdx: "<<keys.first<<endl;
    }

    if (leaf == false)
        C[i]->traverse();
}

// Information
void bnode::getInfo(){
    cout<<"Root: "<<*(this->keys.first)<<endl;
    cout<<"Data: "<<(this->keys.second)<<endl;
}
