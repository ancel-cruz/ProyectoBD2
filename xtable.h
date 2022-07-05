//
// Created by Alain Cruz on 4/07/22.
//

#ifndef PROYECTOBD2_XTABLE_H
#define PROYECTOBD2_XTABLE_H
#include <vector>

using namespace::std;

enum types {type_int, type_float, type_double, type_bool, type_pchar};

struct node{
    types type;
    void* vp;
};

struct table{
    //string name_table;
    vector<node*>elements;
};

#endif //PROYECTOBD2_XTABLE_H
