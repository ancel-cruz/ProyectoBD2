//
// Created by Alain Cruz on 4/07/22.
//

#ifndef PROYECTOBD2_BNODE_H
#define PROYECTOBD2_BNODE_H


int grade = 3;

struct bnode{
    pair<int*, node*> key;
    bnode** child;
};

void print(bnode* t){
    if(t==nullptr) return;
    for(int i=0;i<2*grade;i++){
        print(t->child[i]);
        if(t->key.first[i]!=-1){
            cout<<t->key.first[i]<<" ";
        }
    }
    print(t->child[2*grade]);
}

bool check_leaf(bnode* T){
    int flag=0;
    for(int i=0;i<2*grade+1;i++)
        if(T->child[i]!=nullptr)
            flag=1;
    if(flag==0)
        return (1);
    else
        return (0);
}

void add_to_node(bnode* old_node,int k,bnode* &new_node,int pos){
    int i,j;
    for(i=0;i<2*grade and old_node->key.first[i]!=-1;i++);
    for(j=i-1;j>=pos and old_node->key.first[j]>k;j--){
        old_node->key.first[j+1]=old_node->key.first[j];
        old_node->child[j+2]=old_node->child[j+1];
    }
    old_node->key.first[pos]=k;
    old_node->child[pos+1]=new_node;
}

void create_newnode(bnode* &T){
    int i;
    T=new bnode;
    T->key.first=new int[2*grade];
    T->child=new bnode*[2*grade+1];
    for(i=0;i<2*grade;i++) T->key.first[i]=-1;
    for(i=0;i<2*grade+1;i++) T->child[i]=nullptr;
}

void nodesplit(bnode* old_node,bnode* &new_node,int &k,int pos){
    bnode* N=nullptr;
    create_newnode(N);
    if(pos<=grade){
        for(int i=grade;i<2*grade;i++){
            N->key.first[i-grade]=old_node->key.first[i];
            N->child[i-grade+1]=old_node->child[i+1];
            old_node->key.first[i]=-1;
            old_node->child[i+1]=nullptr;
        }
        N->child[0]=old_node->child[grade];
        add_to_node(old_node,k,new_node,pos);
    }else{
        for(int i=grade+1;i<2*grade;i++){
            N->key.first[i-(grade+1)]=old_node->key.first[i];
            N->child[i-grade]=old_node->child[i+1];
            old_node->key.first[i]=-1;
            old_node->child[i+1]=nullptr;
        }
        N->child[0]=old_node->child[grade+1];
        old_node->child[grade+1]=nullptr;
        add_to_node(N,k,new_node,pos-(grade+1));
    }
    k=old_node->key.first[grade];
    old_node->key.first[grade]=-1;
    new_node=N;
}

int setflag(bnode* T,int &k,bnode* &new_node){
    int pos;
    if(T==nullptr){
        return (1);
    }
    for(pos=0;pos<2*grade and T->key.first[pos]!=-1;pos++){
        if(k<T->key.first[pos]) break;
    }
    if(check_leaf(T)){
        if(T->key.first[2*grade-1]==-1){
            add_to_node(T,k,new_node,pos);
            return (0);
        }else{
            nodesplit(T,new_node,k,pos);
            return (1);
        }
    }else{
        int flag=setflag(T->child[pos],k,new_node);
        if(flag==1){
            if(T->key.first[2*grade-1]==-1){
                add_to_node(T,k,new_node,pos);
                return (0);
            }else{
                nodesplit(T,new_node,k,pos);
                return (1);
            }
        }
    }
    return 0;
}

bnode* create_root(bnode* T,bnode* new_node,int k){
    bnode* root = nullptr;
    create_newnode(root);
    root->key.first[0]=k;
    root->child[0]=T;
    root->child[1]=new_node;
    return (root);
}

void insert(bnode* &T, int k, bnode* new_node){
    //bnode* root = nullptr;
    int flag = setflag(T,k,new_node);
    if(flag){
        T = create_root(T,new_node,k);
    }
}

#endif //PROYECTOBD2_BNODE_H
