#include"columna.h"

Columna::Columna(string nombre, string tipo){
    this->nombre = nombre;
    this->tipo = tipo;
}

vector<void*> Columna::get_data(){
}

void Columna::insertar(void* inp){
    registro.push_back(inp);
    n_elems++;
}