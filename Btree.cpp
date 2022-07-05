#include<iostream>
#include"tabla.cpp"

using namespace std;
 
// A BTree node
class BTreeNode
{
    pair<int,Tabla>* keys;  // Arreglo de keys
    int t;      // define el rango de numero de llaves
    BTreeNode **C; // nodos hijos
    int n;     // numero actual de llaves
    bool leaf; // verdadero si es nodo hoja, false si no lo es

public:
    BTreeNode(int _t, bool _leaf);   // Constructor

    Tabla& get_Tabla(int k){
        return keys[k].second;
    }
    void insertNonFull(int k, string nombre);
    void splitChild(int i, BTreeNode *y);
    void traverse();
    BTreeNode *search(int k);
    int findKey(int k);
    void remove(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    pair<int,Tabla> getPred(int idx);
    pair<int,Tabla> getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);

    pair<int,Tabla>*& get_Keys(){
        return keys;
    }

    pair<int,Tabla>& findTable(int k){
        int idx=0;
        while (idx < n && keys[idx].first < k)
            ++idx;
        return keys[idx];
    }
 
friend class BTree;
};
 
// A BTree
class BTree
{
    BTreeNode *root; // nodo raiz
    int t;  // rango minimo
public:
    BTree(int _t)
    {  root = NULL;  t = _t; }
 
    void traverse()
    {  if (root != NULL) root->traverse(); }
 
    BTreeNode* search(int k)
    {  return (root == NULL)? NULL : root->search(k); }
 
    void insert(int k, string nombre);
    void remove(int k);
};
 
BTreeNode::BTreeNode(int t1, bool leaf1){
    t = t1;
    leaf = leaf1;
    keys = new pair<int,Tabla>[2*t-1];
    C = new BTreeNode *[2*t];
    n = 0;
}
 
void BTreeNode::traverse(){
    int i;
    for (i = 0; i < n; i++){
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i].first;
    }
 
    if (leaf == false)
        C[i]->traverse();
}
 
BTreeNode *BTreeNode::search(int k){
    int i = 0;
    while (i < n && k > keys[i].first)
        i++;
 
    if (keys[i].first == k)
        return this;
 
    if (leaf == true)
        return NULL;

    return C[i]->search(k);
}

int BTreeNode::findKey(int k)
{
    int idx=0;
    while (idx < n && keys[idx].first < k)
        ++idx;
    return idx;
}

void BTreeNode::remove(int k){
    int idx = findKey(k);
    if (idx < n && keys[idx].first == k){
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else{
        if (leaf){
            cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }

        bool flag = ( (idx==n)? true : false );

        if (C[idx]->n < t)
            fill(idx);

        if (flag && idx > n)
            C[idx-1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}

void BTreeNode::removeFromLeaf (int idx){
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];

    keys[n-1].first = 0;
    keys[n-2].second.~Tabla();
    n--;
    
    return;
}

void BTreeNode::removeFromNonLeaf(int idx){
    int k = keys[idx].first;

    if (C[idx]->n >= t){
        pair<int,Tabla> pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred.first);
    }

    else if  (C[idx+1]->n >= t){
        pair<int,Tabla> succ = getSucc(idx);
        keys[idx] = succ;
        C[idx+1]->remove(succ.first);
    }

    else{
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}

pair<int,Tabla> BTreeNode::getPred(int idx){
    BTreeNode *cur=C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    return cur->keys[cur->n-1];
}

pair<int,Tabla> BTreeNode::getSucc(int idx){
    BTreeNode *cur = C[idx+1];
    while (!cur->leaf)
        cur = cur->C[0];

    return cur->keys[0];
}

void BTreeNode::fill(int idx){
    if (idx!=0 && C[idx-1]->n>=t)
        borrowFromPrev(idx);

    else if (idx!=n && C[idx+1]->n>=t)
        borrowFromNext(idx);

    else{
        if (idx != n)
            merge(idx);
        else
            merge(idx-1);
    }
    return;
}

void BTreeNode::borrowFromPrev(int idx){
    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx-1];

    for (int i=child->n-1; i>=0; --i)
        child->keys[i+1] = child->keys[i];

    if (!child->leaf)
    {
        for(int i=child->n; i>=0; --i)
            child->C[i+1] = child->C[i];
    }

    child->keys[0] = keys[idx-1];

    if(!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    keys[idx-1] = sibling->keys[sibling->n-1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

void BTreeNode::borrowFromNext(int idx){

    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx+1];

    child->keys[(child->n)] = keys[idx];

    if (!(child->leaf))
        child->C[(child->n)+1] = sibling->C[0];

    keys[idx] = sibling->keys[0];

    for (int i=1; i<sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];

    if (!sibling->leaf)
    {
        for(int i=1; i<=sibling->n; ++i)
            sibling->C[i-1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;
    
    return;
}

void BTreeNode::merge(int idx){
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx+1];
    child->keys[t-1] = keys[idx];

    for (int i=0; i<sibling->n; ++i)
        child->keys[i+t] = sibling->keys[i];

    if (!child->leaf){
        for(int i=0; i<=sibling->n; ++i)
            child->C[i+t] = sibling->C[i];
    }

    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];

    for (int i=idx+2; i<=n; ++i)
        C[i-1] = C[i];

    child->n += sibling->n+1;

    keys[n-1].first = 0;
    keys[n-2].second.~Tabla();

    n--;

    delete(sibling);
    return;
}


void BTree::insert(int k, string nombre){
    if (root == NULL){
        root = new BTreeNode(t, true);
        root->keys[0].first = k;  
        root->n = 1;  
        root->keys[0].second.rename(nombre);
    }
    else {
        if (root->n == 2*t-1){
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
 
            s->splitChild(0, root);
 
            int i = 0;
            if (s->keys[0].first < k)
                i++;
            s->C[i]->insertNonFull(k, nombre);
            root = s;
        }
        else
            root->insertNonFull(k, nombre);
    }
}
 
void BTreeNode::insertNonFull(int k, string nombre){
    int i = n-1;
 
    if (leaf == true){
        while (i >= 0 && keys[i].first > k)
        {
            keys[i+1] = keys[i];
            i--;
        }
 
        keys[i+1].first = k;
        keys[i+1].second.rename(nombre);
        n = n+1;
    }
    else{
        while (i >= 0 && keys[i].first > k)
            i--;
 
        if (C[i+1]->n == 2*t-1){
            splitChild(i+1, C[i+1]);
 
            if (keys[i+1].first < k)
                i++;
        }
        C[i+1]->insertNonFull(k, nombre);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y){
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
 
    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];
 
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }
 
    y->n = t - 1;
 
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];
 
    C[i+1] = z;

    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
 
    keys[i] = y->keys[t-1];
 
    n = n + 1;
}



void BTree::remove(int k){
    if (!root){
        cout << "No hay tablas\n";
        return;
    }

    root->remove(k);

    if (root->n==0){
        BTreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];

        delete tmp;
    }
    return;
}
 
int main(){
    BTree t(3); // A B-Tree rango 3

    t.insert(1, "Tabla 10");
    t.insert(2, "Tabla 20");
    t.insert(3, "Tabla 30");
    t.insert(4, "Tabla 40");
    t.insert(5, "Tabla 50");
    t.insert(6, "Tabla 60");
    t.insert(7, "Tabla 70");
    t.insert(8, "Tabla 80");
    t.insert(9, "Tabla 90");
    t.traverse();
    cout<<endl;


    BTreeNode* test = t.search(1);

    t.remove(6);
    cout << "Traversal of tree after removing 6\n";
    t.traverse();
    cout << endl;

    t.remove(3);
    cout << "Traversal of tree after removing 3\n";
    t.traverse();
    cout << endl;

    t.remove(7);
    cout << "Traversal of tree after removing 7\n";
    t.traverse();
    cout << endl;

    t.remove(4);
    cout << "Traversal of tree after removing 4\n";
    t.traverse();
    cout << endl;


    BTreeNode* test2 = t.search(6);
    cout<<test2->get_Keys()[0].first;
    cout<<test2->get_Keys()[0].second.nombre<<endl;
    //int test;
    //string tests;
    //test2->get_Keys()[0].second.insertar_columna("id","Int");
    //test2->get_Keys()[0].second.insertar_columna("nombre","String");
    return 0;
}