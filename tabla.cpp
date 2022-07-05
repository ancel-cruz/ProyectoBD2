#include"tabla.h"

Tabla::Tabla(){
}

Tabla::Tabla(string nombre) {
    this->nombre=nombre;
    ncols = 0;
}

Tabla::Tabla(int n) {
    ncols = n;
}

void Tabla::rename(string nombre){
    this->nombre=nombre;
}

void Tabla::insertar_registro(vector<void*> r){
    if(ncols==0)
        cout<<"No hay columnas"<<endl;

    for (int i = 0; i < ncols; i++){
        columnas[i].insertar(r[i]);
    }
}

void Tabla::insertar_columna(string nombre, string tipo){
    Columna c1(nombre, tipo);
    columnas.push_back(c1);
}

vector<Columna>& Tabla::get_data(){
    return columnas;
}

Tabla::~Tabla(){
    columnas.clear();
}