#ifndef PROYECTOBD2_BTREE_H
#define PROYECTOBD2_BTREE_H
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include "bnode.h"
using namespace::std;

enum types{type_int=0, type_float=1, type_double=2, type_bool=3, type_pchar=4, type_str=5};

class btree {
    int t; 
    //bnode* root;
    types* type_data;
    int size_col;
public:
    bnode* root;
    btree();
    void traverse();
    void insertion(int k, idata* &);
    void deletion(int k);
    void get_info_btree();
    void get_set_types(int);
    void set_types(types*,int);
    void read_file(string);
    void show_types();
};

#endif //PROYECTOBD2_BTREE_H
