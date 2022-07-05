#include"columna.cpp"
#include<string>

class Tabla{
    vector<Columna> columnas;
    void guardar();
    int ncols;

    public:
        string nombre;
        Tabla();
        Tabla(int);
        Tabla(string nombre);
        void eliminar(int key);
        void insertar_registro(vector<void*> r);
        void insertar_columna(string nombre, string tipo);
        vector<void*> buscar(int key);
        void rename(string);
        vector<Columna>& get_data();
        ~Tabla();

};

