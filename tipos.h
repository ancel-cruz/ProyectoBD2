#include<iostream>

using namespace std;

class Tipo_INT;
class Tipo_STRING;
class Tipo_FLOAT;

class Tipo{
    void* tipo;
    public:
        virtual void* get_tipo(){
            return tipo;
        };
        friend Tipo_INT;
        friend Tipo_STRING;
        friend Tipo_FLOAT;
};

class Tipo_INT:public Tipo{
    int tipo_int;

    public: 
        Tipo_INT(int n){
            tipo_int = n;
            tipo = &tipo_int;
        }
        void* get_tipo(){
            return &tipo_int;
        }

        int get_data(){
            return tipo_int;
        }
};

class Tipo_STRING:public Tipo{
    string str;
    
    public: 
        Tipo_STRING(string s){
            str = s;
            tipo = &str;
        }
        void* get_tipo(){
            return &str;
        }
};

class Tipo_FLOAT:public Tipo{
    float flt;
    
    public: 
        Tipo_FLOAT(float f){
            flt = f;
            tipo = &flt;
        }
        void* get_tipo(){
            return &flt;
        }
};
/*
int main(){
    Tipo_INT i1(10);
    Tipo_STRING s1("aea");
    Tipo_INT i2(20);
    Tipo_STRING s2("aea2");
    Tipo t_Array[4];

    t_Array[0] = i1;
    t_Array[1] = s1;
    t_Array[2] = i2;
    t_Array[3] = s2;

    cout<<*(int*)(t_Array[0].get_tipo())<<endl;
    cout<<*(string*)(t_Array[1].get_tipo())<<endl;
    
}*/

