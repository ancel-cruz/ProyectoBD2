#include<vector>
#include<string>
#include"tipos.h"

using namespace::std;

class Columna{
    private:
        int n_elems;
        string tipo;
        string nombre;
        vector<void*> registro;
    public:
        Columna(string nombre, string tipo);
        vector<void*> get_data();
        string get_type(){return tipo;}
        string get_nombre(){return nombre;}
        void insertar(void* inp);
};