#include<iostream>
#include <vector>
#include <typeinfo>
#include <sstream>
#include "btree.h"
using namespace std;

void example_btree_run(){
    //Create Tabla..
    btree tabla1;
    
    //Types Datas..
    int total = 4;
    types* t_tabla1 = new types[4]{type_int,type_pchar,type_pchar,type_int};
    tabla1.set_types(t_tabla1,4);
    
    //Read File..
    string url = "../demo.csv";
    tabla1.read_file(url);
    
    //Print data..
    tabla1.traverse();
    tabla1.root->getInfo();
    
    cout<<endl;
    cout<<"FIN"<<endl;
    cout<<endl;
    
    //Create Tabla..
    btree tabla2;
    
    //Types Datas..
    int total2 = 8;
    types* t_tabla2 = new types[8]{type_int,type_str,type_int,type_str,type_str,type_str,type_str,type_int};
    tabla2.set_types(t_tabla2,8);
    //Read File..
    string url2 = "../data4.csv";
    tabla2.read_file(url2);
    //Print data..
    tabla2.traverse();
    tabla2.deletion(36);
    tabla2.traverse();
}

int main(int argc, const char * argv[]) {

    
    
    
    return (0);
}
